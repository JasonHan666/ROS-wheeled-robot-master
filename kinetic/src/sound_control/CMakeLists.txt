cmake_minimum_required(VERSION 2.8.3)
project(sound_control)

find_package(catkin REQUIRED COMPONENTS
    roscpp
    std_msgs
)

catkin_package(
#   INCLUDE_DIRS include
#   LIBRARIES sound_control
#   CATKIN_DEPENDS roscpp rospy std_msgs
#   DEPENDS system_lib
)

include_directories(include ${catkin_INCLUDE_DIRS} ${PCL_INCLUDE_DIRS})

add_executable(command_publisher
               src/command_publisher.cpp
               src/speech_recognizer.c
               src/linuxrec.c)

target_link_libraries(command_publisher
                      ${catkin_LIBRARIES}
                      libmsc.so -ldl -lpthread -lm -lrt -lasound)

add_executable(command_publisher_test
               src/command_publisher_test.cpp
               src/speech_recognizer.c
               src/linuxrec.c)

target_link_libraries(command_publisher_test
                      ${catkin_LIBRARIES}
                      libmsc.so -ldl -lpthread -lm -lrt -lasound)



add_executable(wakeUp src/wakeUp.cpp)
target_link_libraries(wakeUp ${catkin_LIBRARIES})

# add_executable(command_publisher src/command_publisher.cpp)
# target_link_libraries(command_publisher ${catkin_LIBRARIES})
