// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from custom_interfaces:srv/TargetTurtleInfo.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "custom_interfaces/srv/target_turtle_info.h"


#ifndef CUSTOM_INTERFACES__SRV__DETAIL__TARGET_TURTLE_INFO__STRUCT_H_
#define CUSTOM_INTERFACES__SRV__DETAIL__TARGET_TURTLE_INFO__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in srv/TargetTurtleInfo in the package custom_interfaces.
typedef struct custom_interfaces__srv__TargetTurtleInfo_Request
{
  uint8_t structure_needs_at_least_one_member;
} custom_interfaces__srv__TargetTurtleInfo_Request;

// Struct for a sequence of custom_interfaces__srv__TargetTurtleInfo_Request.
typedef struct custom_interfaces__srv__TargetTurtleInfo_Request__Sequence
{
  custom_interfaces__srv__TargetTurtleInfo_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} custom_interfaces__srv__TargetTurtleInfo_Request__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'name'
#include "rosidl_runtime_c/string.h"

/// Struct defined in srv/TargetTurtleInfo in the package custom_interfaces.
typedef struct custom_interfaces__srv__TargetTurtleInfo_Response
{
  float x;
  float y;
  float theta;
  rosidl_runtime_c__String name;
} custom_interfaces__srv__TargetTurtleInfo_Response;

// Struct for a sequence of custom_interfaces__srv__TargetTurtleInfo_Response.
typedef struct custom_interfaces__srv__TargetTurtleInfo_Response__Sequence
{
  custom_interfaces__srv__TargetTurtleInfo_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} custom_interfaces__srv__TargetTurtleInfo_Response__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'info'
#include "service_msgs/msg/detail/service_event_info__struct.h"

// constants for array fields with an upper bound
// request
enum
{
  custom_interfaces__srv__TargetTurtleInfo_Event__request__MAX_SIZE = 1
};
// response
enum
{
  custom_interfaces__srv__TargetTurtleInfo_Event__response__MAX_SIZE = 1
};

/// Struct defined in srv/TargetTurtleInfo in the package custom_interfaces.
typedef struct custom_interfaces__srv__TargetTurtleInfo_Event
{
  service_msgs__msg__ServiceEventInfo info;
  custom_interfaces__srv__TargetTurtleInfo_Request__Sequence request;
  custom_interfaces__srv__TargetTurtleInfo_Response__Sequence response;
} custom_interfaces__srv__TargetTurtleInfo_Event;

// Struct for a sequence of custom_interfaces__srv__TargetTurtleInfo_Event.
typedef struct custom_interfaces__srv__TargetTurtleInfo_Event__Sequence
{
  custom_interfaces__srv__TargetTurtleInfo_Event * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} custom_interfaces__srv__TargetTurtleInfo_Event__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // CUSTOM_INTERFACES__SRV__DETAIL__TARGET_TURTLE_INFO__STRUCT_H_
