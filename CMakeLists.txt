cmake_minimum_required(VERSION 3.10)
project(sample_filter)

set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_CXX_FLAGS "-std=c++17")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -Wall -pthread")

set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(PCL REQUIRED)
find_package(Eigen3 REQUIRED)

include_directories(
  include
  ${EIGEN3_INCLUDE_DIRS}
  ${PCL_INCLUDE_DIRS}
)

set(common_lib "")
list(APPEND common_lib ${PCL_LIBRARIES})

add_executable(pcl_rmvoxel test/pcl_rmvoxel_node.cpp)
target_link_libraries(pcl_rmvoxel ${common_lib})

add_executable(pcl_sor test/statistical_outlier_removal_node.cpp src/statistical_outlier_removal.cpp)
target_link_libraries(pcl_sor ${common_lib})

add_executable(ror test/radius_outlier_removal_node.cpp)
target_link_libraries(ror ${common_lib})