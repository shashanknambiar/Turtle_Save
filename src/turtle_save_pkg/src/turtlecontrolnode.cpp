#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "turtlesim/msg/pose.hpp"
#include "std_msgs/msg/string.hpp"
#include "custom_interfaces/srv/target_turtle_info.hpp"
#include <cmath>
#define PI 3.1415926535897

class TurtleControl : public rclcpp::Node
{
    public:
    TurtleControl() : Node("TurtleControl"), count(0)
    {
        RCLCPP_INFO(this->get_logger(), "Starting Turtle Control");
        _timer = create_wall_timer(std::chrono::milliseconds(10), std::bind(&TurtleControl::timerCallBack, this));
        
        turtleControl = this->create_publisher<geometry_msgs::msg::Twist>("turtle1/cmd_vel", 10);
        turtlePos = this->create_subscription<turtlesim::msg::Pose>("turtle1/pose", 10, 
            std::bind(&TurtleControl::UpdateTurtlePos, this, std::placeholders::_1));


        getNextTurtleClient = this->create_client<custom_interfaces::srv::TargetTurtleInfo>("/GetNextTurtle");
        removeTurtle = this->create_publisher<std_msgs::msg::String>("/RemoveTurtle", 10);
        removeTurtleAck = this->create_subscription<std_msgs::msg::String>("/TurtleRemoveComplete", 10, 
                                        std::bind(&TurtleControl::TurtleSaveAck, this, std::placeholders::_1));
    }

    private:

    void timerCallBack()
    {
        switch(CurrentActionStatus)
        {
            case GetTarget:
            {
                GetNextTarget();
                break;
            }
            case Run:
            {
                float x;
                float theta;
                CalculateVelocities(&x, &theta, CurrentTurtlePos.x, CurrentTurtlePos.y, CurrentTurtlePos.theta,TargetTurtlePos.x, TargetTurtlePos.y);
                ApplyTurtleVelocities(x, theta);
                break;
            }
            case Wait:
            default:
            {
                break;
            }


        }
        //Check target reached -> Get Target (Wait)
        //Calculate velocities(Run) -> Apply velocities        
    }

    void ApplyTurtleVelocities(float x, float theta)
    {
        auto msg = geometry_msgs::msg::Twist();
        msg.linear.x = x;
        msg.angular.z = theta;
        turtleControl->publish(msg);
    }

    void CalculateVelocities(float *x,float* theta, float current_x, float current_y, float current_theta, float target_x, float target_y)
    {

        RCLCPP_INFO(this->get_logger(), "Target at x: %f y:%f", target_x, target_y);
        //RCLCPP_INFO(this->get_logger(), "Current at x: %f y:%f", current_x, current_y);
        float linear_gain = 1.5; //1 to 2
        float angular_gain = 4.5; //4 to 6

        //Calculate distance
        float dx = target_x - current_x;
        float dy = target_y - current_y;
        float distance = sqrt(dx*dx + dy*dy);

        if(distance < 0.1)
        {
            *x = 0; 
            *theta = 0;
            PublishTurtleSaved();
            return; //target reached
        }

        //Calculate heading
        float t = std::atan2(dy, dx);
        float t_error = t - current_theta; 
        t = std::atan2(sin(t_error), cos(t_error)); //normalizing heading: -pi to +pi 

             
        //Apply gains
        t = angular_gain * t;
        distance = linear_gain * distance;

        //velocity clamping
        float x_max = 2;
        float t_max = 2;
        
        *x = std::clamp(distance, -x_max, x_max);
        *theta = std::clamp(t, -t_max, t_max);//(theta * 2 * PI) / 360;
        RCLCPP_INFO(this->get_logger(), "Applying at x: %f theta:%f", *x, *theta);
    }

    void UpdateTurtlePos(const turtlesim::msg::Pose::SharedPtr p)
    {
        CurrentTurtlePos.x = p->x;
        CurrentTurtlePos.y = p->y;
        CurrentTurtlePos.theta = p->theta;
        //RCLCPP_INFO(this->get_logger(), "POS: %.2f %.2f %.2f", CurrentTurtlePos.x, CurrentTurtlePos.y, CurrentTurtlePos.theta);
    }

    void PublishTurtleSaved()
    {
        RCLCPP_INFO(this->get_logger(), "Publishing turtle saved");
        SetTurtleToWait();
        auto msg = std_msgs::msg::String();
        msg.data = TargetTurtleName;
        removeTurtle->publish(msg);
        
    }

    void TurtleSaveAck(const std_msgs::msg::String::SharedPtr /*turtleName*/)
    {
        RCLCPP_INFO(this->get_logger(), "Turtle Save Ack recieved");
        GetNextTarget();
    }

    void GetNextTarget()
    {   
        int targetInfoTimeOut = 0;
        SetTurtleToWait(); //Wait for target details
        RCLCPP_INFO(this->get_logger(), "Getting next target detials");
        while(!getNextTurtleClient->wait_for_service(std::chrono::seconds(1)))
        {
            targetInfoTimeOut++;
            if(targetInfoTimeOut > 5)
            {
                RCLCPP_WARN(this->get_logger(), "Timed out: NextTarget service not found.");
            }
                
        }
        //create request
        auto request = std::make_shared<custom_interfaces::srv::TargetTurtleInfo::Request>();
        //send request
        getNextTurtleClient -> async_send_request(request, std::bind(&TurtleControl::NextTargetRecieved, this,  std::placeholders::_1));
        RCLCPP_INFO(this->get_logger(), "Next target Request done");
    }
    
    void NextTargetRecieved(rclcpp::Client<custom_interfaces::srv::TargetTurtleInfo>::SharedFuture targetInfoFuture)
    {
        RCLCPP_INFO(this->get_logger(), "Target info recieved");
        TargetTurtlePos.x = targetInfoFuture.get()->x;
        TargetTurtlePos.y = targetInfoFuture.get()->y;
        TargetTurtlePos.theta = targetInfoFuture.get()->theta;
        TargetTurtleName = targetInfoFuture.get()->name;
        RCLCPP_INFO(this->get_logger(), "Target at x: %f y: %f theta: %f name: %s", TargetTurtlePos.x, TargetTurtlePos.y, TargetTurtlePos.theta, TargetTurtleName.c_str());
        if(TargetTurtleName == "")
        {
            RCLCPP_INFO(this->get_logger(), "No valid turtle target recieved");
            SetTurtleToWait();
            StartTargetMaintainer();
        }
        else 
            SetTurtleToRun();
         
    }

    void SetTurtleToGetTarget()
    {
        CurrentActionStatus = GetTarget;
    }
    
    void SetTurtleToWait()
    {
        ApplyTurtleVelocities(0,0);
        CurrentActionStatus = Wait;
        RCLCPP_INFO(this->get_logger(), "Turtle set to Wait");
    }

    void SetTurtleToRun()
    {
        CurrentActionStatus = Run;
        RCLCPP_INFO(this->get_logger(), "Turtle set to Run");
    }

    void StartTargetMaintainer()
    {
        RCLCPP_INFO(this->get_logger(), "Waiting for other turtles to spawn");
        _targetMaintainer = create_wall_timer(std::chrono::seconds(30), std::bind(&TurtleControl::StopTargetMaintainer, this));
    }

    void StopTargetMaintainer()
    {
        RCLCPP_INFO(this->get_logger(), "Checking for targets");
        if (_targetMaintainer && _targetMaintainer->is_steady()) {
            _targetMaintainer->cancel();
            RCLCPP_INFO(this->get_logger(), "Maintainer timer stopped!");
        }
        SetTurtleToGetTarget();
    }

    enum TurtleStatus 
    {
        Wait,
        Run,
        GetTarget
    };

    rclcpp::TimerBase::SharedPtr _timer;
    rclcpp::TimerBase::SharedPtr _targetMaintainer;
    int count;
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr turtleControl;
    rclcpp::Subscription<turtlesim::msg::Pose>::SharedPtr turtlePos;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr removeTurtle;
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr removeTurtleAck;
    rclcpp::Client<custom_interfaces::srv::TargetTurtleInfo>::SharedPtr getNextTurtleClient;
    turtlesim::msg::Pose CurrentTurtlePos; 
    turtlesim::msg::Pose TargetTurtlePos;
    std::string TargetTurtleName;
    enum TurtleStatus CurrentActionStatus = GetTarget;
};

int main(int arg, char **argv)
{
    rclcpp::init(arg, argv);
    auto node = std::make_shared<TurtleControl>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}