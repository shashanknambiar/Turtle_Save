#include "rclcpp/rclcpp.hpp"

class MyNode : public rclcpp::Node
{
    public:
    MyNode() : Node("cpp_test"), count(0)
    {
        RCLCPP_INFO(this->get_logger(), "Hello World 3");
        _timer = create_wall_timer(std::chrono::seconds(1), std::bind(&MyNode::timerCallBack, this));
    }

    private:
    rclcpp::TimerBase::SharedPtr _timer;
    int count;
    void timerCallBack()
    {
        RCLCPP_INFO(this->get_logger(), "Timer %d", count);
        count++;
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