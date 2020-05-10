# Install script for directory: /home/seedfull/ros_project/ROS-wheeled-robot-master/kinetic/src/four_wheel_urdf

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/seedfull/ros_project/ROS-wheeled-robot-master/kinetic/install")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/seedfull/ros_project/ROS-wheeled-robot-master/kinetic/build/four_wheel_urdf/catkin_generated/installspace/four_wheel_urdf.pc")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/four_wheel_urdf/cmake" TYPE FILE FILES
    "/home/seedfull/ros_project/ROS-wheeled-robot-master/kinetic/build/four_wheel_urdf/catkin_generated/installspace/four_wheel_urdfConfig.cmake"
    "/home/seedfull/ros_project/ROS-wheeled-robot-master/kinetic/build/four_wheel_urdf/catkin_generated/installspace/four_wheel_urdfConfig-version.cmake"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/four_wheel_urdf" TYPE FILE FILES "/home/seedfull/ros_project/ROS-wheeled-robot-master/kinetic/src/four_wheel_urdf/package.xml")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/four_wheel_urdf/config" TYPE DIRECTORY FILES "/home/seedfull/ros_project/ROS-wheeled-robot-master/kinetic/src/four_wheel_urdf/config/")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/four_wheel_urdf/launch" TYPE DIRECTORY FILES "/home/seedfull/ros_project/ROS-wheeled-robot-master/kinetic/src/four_wheel_urdf/launch/")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/four_wheel_urdf/meshes" TYPE DIRECTORY FILES "/home/seedfull/ros_project/ROS-wheeled-robot-master/kinetic/src/four_wheel_urdf/meshes/")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/four_wheel_urdf/urdf" TYPE DIRECTORY FILES "/home/seedfull/ros_project/ROS-wheeled-robot-master/kinetic/src/four_wheel_urdf/urdf/")
endif()

