#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/int64.hpp"

class MyNode : public rclcpp::Node
{
    public:
    MyNode() : Node("number_publisher"), count(0)
    {
        RCLCPP_INFO(this->get_logger(), "Number publisher started.");
        _timer = create_wall_timer(std::chrono::seconds(1), std::bind(&MyNode::timerCallBack, this));
        publisher_ = this->create_publisher<example_interfaces::msg::Int64>("number", 10);
    }

    private:
    rclcpp::TimerBase::SharedPtr _timer;
    rclcpp::Publisher<example_interfaces::msg::Int64>::SharedPtr publisher_;
    int count;
    void timerCallBack()
    {
        count++;
        auto msg = example_interfaces::msg::Int64();
        msg.data = count;
        publisher_->publish(msg);
    }
};

int main(int arg, char **argv)
{
    rclcpp::init(arg, argv);
    auto node = std::make_shared<MyNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}