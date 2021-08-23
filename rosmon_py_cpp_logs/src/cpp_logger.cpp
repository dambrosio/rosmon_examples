// NOLINT (warning:legal/copyright)

#include <ros/console.h>
#include <ros/init.h>
#include <ros/node_handle.h>

#include <string>

static const ros::Duration CYCLE_PERIOD(2.0);

int main(int argc, char* argv[])
{
  ros::init(argc, argv, "cpp_logger");

  // Initialize time since this node does not use a node handle, this will ensure the call to ros::Duration sleep() will
  // function appropriately
  ros::Time::init();

  std::size_t count = 0;
  while (ros::ok())
  {
    ros::spinOnce();

    const bool is_even = ((count++ % 2) == 0);
    const std::string msg = std::string("Example cpp ") + (is_even ? "info" : "error") + " message for logging "
                                                                                         "purposes";
    ROS_INFO_STREAM_COND(is_even, msg);
    ROS_ERROR_STREAM_COND(!is_even, msg);

    CYCLE_PERIOD.sleep();
  }

  return EXIT_SUCCESS;
}
