cmake_minimum_required(VERSION 3.0.2)
project(basict)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()


find_package(Qt5 COMPONENTS Core Quick REQUIRED)
find_package(catkin REQUIRED COMPONENTS roscpp geometry_msgs mavros_msgs message_generation )



catkin_package(
  INCLUDE_DIRS include
  LIBRARIES basict
  CATKIN_DEPENDS roscpp stdmsgs
#  DEPENDS system_lib
)

include_directories(
 include
  ${catkin_INCLUDE_DIRS}
)


add_executable(basict
    src/main.cpp
    src/BackEnd.cpp
    src/qml.qrc
    src/BackEnd.h
    #resources.qrc
)

target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Quick ${catkin_LIBRARIES})