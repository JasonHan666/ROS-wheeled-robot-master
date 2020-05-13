cmake_minimum_required(VERSION 2.8.3)
project(sound_control)

find_package(catkin REQUIRED COMPONENTS
    roscpp
    std_msgs
)

catkin_package(
    # INCLUDE_DIRS include
#   LIBRARIES sound_control
#   CATKIN_DEPENDS roscpp rospy std_msgs
#   DEPENDS system_lib
)

# include_directories(include ${catkin_INCLUDE_DIRS})
include_directories(include ${catkin_INCLUDE_DIRS} ${PCL_INCLUDE_DIRS})
# add_library(msp_cmn
#             include/msp_cmn.h)
# target_link_libraries(msp_cmn ${catkin_LIBRARIES})
# add_dependencies(msp_cmn ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

# add_library(msp_errors
#             include/msp_errors.h)
# target_link_libraries(msp_errors ${catkin_LIBRARIES})
# add_dependencies(msp_errors ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

# add_library(qisr
#             include/qisr.h)
# target_link_libraries(qisr ${catkin_LIBRARIES})
# add_dependencies(qisr ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

add_executable(iat_publisher
               src/iat_publisher.cpp
               src/speech_recognizer.c
               src/linuxrec.c)

target_link_libraries(iat_publisher
                      ${catkin_LIBRARIES}
                      libmsc.so -ldl -lpthread -lm -lrt -lasound)
