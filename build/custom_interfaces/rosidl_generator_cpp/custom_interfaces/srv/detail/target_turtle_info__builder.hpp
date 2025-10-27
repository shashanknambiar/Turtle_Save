// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from custom_interfaces:srv/TargetTurtleInfo.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "custom_interfaces/srv/target_turtle_info.hpp"


#ifndef CUSTOM_INTERFACES__SRV__DETAIL__TARGET_TURTLE_INFO__BUILDER_HPP_
#define CUSTOM_INTERFACES__SRV__DETAIL__TARGET_TURTLE_INFO__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "custom_interfaces/srv/detail/target_turtle_info__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace custom_interfaces
{

namespace srv
{


}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::custom_interfaces::srv::TargetTurtleInfo_Request>()
{
  return ::custom_interfaces::srv::TargetTurtleInfo_Request(rosidl_runtime_cpp::MessageInitialization::ZERO);
}

}  // namespace custom_interfaces


namespace custom_interfaces
{

namespace srv
{

namespace builder
{

class Init_TargetTurtleInfo_Response_name
{
public:
  explicit Init_TargetTurtleInfo_Response_name(::custom_interfaces::srv::TargetTurtleInfo_Response & msg)
  : msg_(msg)
  {}
  ::custom_interfaces::srv::TargetTurtleInfo_Response name(::custom_interfaces::srv::TargetTurtleInfo_Response::_name_type arg)
  {
    msg_.name = std::move(arg);
    return std::move(msg_);
  }

private:
  ::custom_interfaces::srv::TargetTurtleInfo_Response msg_;
};

class Init_TargetTurtleInfo_Response_theta
{
public:
  explicit Init_TargetTurtleInfo_Response_theta(::custom_interfaces::srv::TargetTurtleInfo_Response & msg)
  : msg_(msg)
  {}
  Init_TargetTurtleInfo_Response_name theta(::custom_interfaces::srv::TargetTurtleInfo_Response::_theta_type arg)
  {
    msg_.theta = std::move(arg);
    return Init_TargetTurtleInfo_Response_name(msg_);
  }

private:
  ::custom_interfaces::srv::TargetTurtleInfo_Response msg_;
};

class Init_TargetTurtleInfo_Response_y
{
public:
  explicit Init_TargetTurtleInfo_Response_y(::custom_interfaces::srv::TargetTurtleInfo_Response & msg)
  : msg_(msg)
  {}
  Init_TargetTurtleInfo_Response_theta y(::custom_interfaces::srv::TargetTurtleInfo_Response::_y_type arg)
  {
    msg_.y = std::move(arg);
    return Init_TargetTurtleInfo_Response_theta(msg_);
  }

private:
  ::custom_interfaces::srv::TargetTurtleInfo_Response msg_;
};

class Init_TargetTurtleInfo_Response_x
{
public:
  Init_TargetTurtleInfo_Response_x()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_TargetTurtleInfo_Response_y x(::custom_interfaces::srv::TargetTurtleInfo_Response::_x_type arg)
  {
    msg_.x = std::move(arg);
    return Init_TargetTurtleInfo_Response_y(msg_);
  }

private:
  ::custom_interfaces::srv::TargetTurtleInfo_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::custom_interfaces::srv::TargetTurtleInfo_Response>()
{
  return custom_interfaces::srv::builder::Init_TargetTurtleInfo_Response_x();
}

}  // namespace custom_interfaces


namespace custom_interfaces
{

namespace srv
{

namespace builder
{

class Init_TargetTurtleInfo_Event_response
{
public:
  explicit Init_TargetTurtleInfo_Event_response(::custom_interfaces::srv::TargetTurtleInfo_Event & msg)
  : msg_(msg)
  {}
  ::custom_interfaces::srv::TargetTurtleInfo_Event response(::custom_interfaces::srv::TargetTurtleInfo_Event::_response_type arg)
  {
    msg_.response = std::move(arg);
    return std::move(msg_);
  }

private:
  ::custom_interfaces::srv::TargetTurtleInfo_Event msg_;
};

class Init_TargetTurtleInfo_Event_request
{
public:
  explicit Init_TargetTurtleInfo_Event_request(::custom_interfaces::srv::TargetTurtleInfo_Event & msg)
  : msg_(msg)
  {}
  Init_TargetTurtleInfo_Event_response request(::custom_interfaces::srv::TargetTurtleInfo_Event::_request_type arg)
  {
    msg_.request = std::move(arg);
    return Init_TargetTurtleInfo_Event_response(msg_);
  }

private:
  ::custom_interfaces::srv::TargetTurtleInfo_Event msg_;
};

class Init_TargetTurtleInfo_Event_info
{
public:
  Init_TargetTurtleInfo_Event_info()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_TargetTurtleInfo_Event_request info(::custom_interfaces::srv::TargetTurtleInfo_Event::_info_type arg)
  {
    msg_.info = std::move(arg);
    return Init_TargetTurtleInfo_Event_request(msg_);
  }

private:
  ::custom_interfaces::srv::TargetTurtleInfo_Event msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::custom_interfaces::srv::TargetTurtleInfo_Event>()
{
  return custom_interfaces::srv::builder::Init_TargetTurtleInfo_Event_info();
}

}  // namespace custom_interfaces

#endif  // CUSTOM_INTERFACES__SRV__DETAIL__TARGET_TURTLE_INFO__BUILDER_HPP_
