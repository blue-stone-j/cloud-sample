cmake_minimum_required(VERSION 3.10)
project(sample_filter)

set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_CXX_FLAGS "-std=c++17")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -Wall -pthread")

# set(CMAKE_CXX_STANDARD 17)

# set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(PCL REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(Ceres REQUIRED)
find_package(Glog REQUIRED)

include_directories(
  include
  ${EIGEN3_INCLUDE_DIRS}
  ${PCL_INCLUDE_DIRS}
  ${CERES_INCLUDE_DIRS}

  ${Glog_INCLUDE_DIRS}
)

add_executable(odom SHARED src/my_icp_base.cpp src/icp_svd.cpp src/icp_GN.cpp)

target_link_libraries(${PROJECT_NAME}_lib
  ${PCL_LIBRARIES}
  ${OpenCV_LIBS}
  ${CERES_LIBRARIES}
  ${Sophus_LIBRARIES}
)