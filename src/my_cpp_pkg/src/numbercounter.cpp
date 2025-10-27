#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/int64.hpp"
#include "example_interfaces/srv/set_bool.hpp"


class NumberCounterNode : public rclcpp::Node
{
    public:
    NumberCounterNode() : Node("number_counter"), count(0)
    {
        RCLCPP_INFO(this->get_logger(), "Number Counter started.");
        publisher_ = this->create_publisher<example_interfaces::msg::Int64>("number_count", 10);
        subscriber_ = this->create_subscription<example_interfaces::msg::Int64>("number", 10, std::bind(&NumberCounterNode::EventRecievedCallBack, this, std::placeholders::_1));
        service_ = this->create_service<example_interfaces::srv::SetBool>(
            "reset_counter",
            std::bind(&NumberCounterNode::EventResetCounter, this, std::placeholders::_1, std::placeholders::_2));
    }

    private:
    int count;
    rclcpp::Publisher<example_interfaces::msg::Int64>::SharedPtr publisher_;
    rclcpp::Subscription<example_interfaces::msg::Int64>::SharedPtr subscriber_;
    rclcpp::Service<example_interfaces::srv::SetBool>::SharedPtr service_;

    void EventRecievedCallBack(const example_interfaces::msg::Int64::SharedPtr m)
    {
        count ++;
        auto msg = example_interfaces::msg::Int64();
        msg.data = count;
        publisher_->publish(msg);
    }

    void EventResetCounter(const std::shared_ptr<example_interfaces::srv::SetBool::Request> request,
        const std::shared_ptr<example_interfaces::srv::SetBool::Response> response)
    {
         RCLCPP_INFO(this->get_logger(), "Handling reset event");
         if(request->data)
         {
            count = 0;
            RCLCPP_INFO(this->get_logger(), "Resetting counter to 0.");
         }
         else   
            RCLCPP_INFO(this->get_logger(), "No action needed");
        
    }
};

int main(int arg, char **argv)
{
    rclcpp::init(arg, argv);
    auto node = std::make_shared<NumberCounterNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}