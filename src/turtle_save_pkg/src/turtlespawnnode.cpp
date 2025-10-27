#include "rclcpp/rclcpp.hpp"
#include "turtlesim/srv/spawn.hpp" 
#include "turtlesim/srv/kill.hpp"
#include <random>
#include <list>
#include <algorithm>
#include "custom_interfaces/srv/target_turtle_info.hpp"
#include "example_interfaces/srv/trigger.hpp"
#include "std_msgs/msg/string.hpp"

class TurtlePosInfo
{
    public:
    TurtlePosInfo(float _x, float _y, float _theta, std::string _name): x(_x), y(_y), theta(_theta), name(_name)
    {

    }
    float x;
    float y;
    float theta;
    std::string name;
};

//Spawns a trutle at a random location every 10 seconds
class TurtleSpawnNode : public rclcpp::Node
{
    public:
    TurtleSpawnNode() : Node("turtle_spawn"), spawnTimeOut(0)
    {
        RCLCPP_INFO(this->get_logger(), "Turtle spawn node started");
        _timer = create_wall_timer(std::chrono::seconds(10), std::bind(&TurtleSpawnNode::CreateRandomTurtle, this));
        
        //Turtle clients 
        spwanClient = this->create_client<turtlesim::srv::Spawn>("/spawn");
        killClient = this->create_client<turtlesim::srv::Kill>("/kill");
        

        getNextTurtleService = this->create_service<custom_interfaces::srv::TargetTurtleInfo>("GetNextTurtle", 
            std::bind(&TurtleSpawnNode::HandleGetNextTurtleService, this, std::placeholders::_1, std::placeholders::_2));
        removeTurtleSubscription = this->create_subscription<std_msgs::msg::String>("RemoveTurtle", 10, 
            std::bind(&TurtleSpawnNode::RemoveTurtle, this, std::placeholders::_1));
        publishRemoveComplete = this->create_publisher<std_msgs::msg::String>("TurtleRemoveComplete", 10);
        
    }

    private:
    rclcpp::TimerBase::SharedPtr _timer;
    int spawnTimeOut;
    std::vector<TurtlePosInfo> turtleQueue;
    int x, y, theta;

    rclcpp::Client<turtlesim::srv::Spawn>::SharedPtr spwanClient;
    rclcpp::Client<turtlesim::srv::Kill>::SharedPtr killClient;
    rclcpp::Service<custom_interfaces::srv::TargetTurtleInfo>::SharedPtr getNextTurtleService; 
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr removeTurtleSubscription; 
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publishRemoveComplete;
    //rclcpp::Publisher
    //Timer call back for creating turtles

    void CreateRandomTurtle()
    {
        RCLCPP_INFO(this->get_logger(), "Creating turtle");
        while(!spwanClient->wait_for_service(std::chrono::seconds(1)))
        {
            spawnTimeOut++;
            if(spawnTimeOut > 5)
            {
                RCLCPP_WARN(this->get_logger(), "Timed out: Spawn service not found.");
            }
                
        }
        //create request
        auto request = std::make_shared<turtlesim::srv::Spawn::Request>();
        request->x = GetRandomCoordinate();
        request->y = GetRandomCoordinate();
        request->theta = 0.0;
        x = request->x;
        y = request->y;
        theta = request->theta;
        //send request
         spwanClient -> async_send_request(request, std::bind(&TurtleSpawnNode::spawnCompleteCallBack, this,  std::placeholders::_1));
        RCLCPP_INFO(this->get_logger(), "Request done");
        
    }

    void spawnCompleteCallBack(rclcpp::Client<turtlesim::srv::Spawn>::SharedFuture future)
    {
            RCLCPP_INFO(this->get_logger(), "Call back start");
            const char* turtle = future.get()->name.c_str();
            RCLCPP_INFO(this->get_logger(), "Spawned at x: %d y: %d theta: %d name: %s", x, y, theta, turtle);
            TurtlePosInfo t(x, y, theta, turtle);
            turtleQueue.push_back(t);
            RCLCPP_INFO(this->get_logger(), "Spawned turtle named: %s", turtle);
    }

    //Callback and future for removing turtles
    void RemoveTurtle(const std_msgs::msg::String::SharedPtr msg)
    {
        const char* turtle = msg->data.c_str();
        RCLCPP_INFO(this->get_logger(), "Removing turtle %s", turtle);
        while(!killClient->wait_for_service(std::chrono::seconds(1)))
        {
            spawnTimeOut++;
            if(spawnTimeOut > 10)
            {
                RCLCPP_WARN(this->get_logger(), "Timed out: Kill service not found.");
            }  
        }

        auto request = std::make_shared<turtlesim::srv::Kill::Request>();
        request->name = turtle;

         //send request
        killClient -> async_send_request(request, std::bind(&TurtleSpawnNode::TurtleKillComplete, this,  std::placeholders::_1));
        RCLCPP_INFO(this->get_logger(), "Kill request done");
    }

    void TurtleKillComplete(rclcpp::Client<turtlesim::srv::Kill>::SharedFuture /*future*/)
    {
        RCLCPP_INFO(this->get_logger(), "Turtle removed successfuly");
        turtleQueue.erase(turtleQueue.begin());
        auto msg = std_msgs::msg::String();
        msg.data = turtleQueue[0].name;
        publishRemoveComplete->publish(msg);
    }

    //random number generator

    int GetRandomCoordinate() //returns a coordinate for turtlesim
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distr(0, 11);
        return distr(gen);
    }

    void HandleGetNextTurtleService(const std::shared_ptr<custom_interfaces::srv::TargetTurtleInfo::Request> /*request*/, 
        std::shared_ptr<custom_interfaces::srv::TargetTurtleInfo::Response> response)
    {
        RCLCPP_INFO(this->get_logger(), "Get Next Turtle called");
        //response->success = true;
        //response->name = turtleQueue.back();
        if(!turtleQueue.empty())
        {
            TurtlePosInfo t = turtleQueue[0];
            response->x = t.x;
            response->y = t.y;
            response->name = t.name;
        }
    }
};

int main(int arg, char **argv)
{
    rclcpp::init(arg, argv);
    auto node = std::make_shared<TurtleSpawnNode>();
    //node->CreateRandomTurtle();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}