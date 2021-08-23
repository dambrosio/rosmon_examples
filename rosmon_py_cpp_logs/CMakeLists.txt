cmake_minimum_required(VERSION 3.0.2)

project(rosmon_py_cpp_logs)

add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  roslaunch
  roslint
  rospy
)

catkin_package(
  CATKIN_DEPENDS
    roscpp
    rospy
)

include_directories(${catkin_INCLUDE_DIRS})

add_executable(${PROJECT_NAME}_cpp_logger
  src/cpp_logger.cpp
)
add_dependencies(${PROJECT_NAME}_cpp_logger ${catkin_EXPORTED_TARGETS})
target_link_libraries(${PROJECT_NAME}_cpp_logger ${catkin_LIBRARIES})
set_target_properties(${PROJECT_NAME}_cpp_logger
  PROPERTIES OUTPUT_NAME cpp_logger
  PREFIX ""
)

roslint_cpp()
roslint_python(scripts/py_logger)

if (CATKIN_ENABLE_TESTING)

  roslint_add_test()
  roslaunch_add_file_check(launch)

endif()

install(
  TARGETS ${PROJECT_NAME}_cpp_logger
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

catkin_install_python(PROGRAMS scripts/py_logger
  DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

foreach(dir launch)
  install(DIRECTORY ${dir}/
    DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}/${dir})
endforeach()
