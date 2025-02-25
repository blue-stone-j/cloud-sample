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

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/install)
set(BUILD_TEST ON)

set(common_lib "")
list(APPEND common_lib ${PCL_LIBRARIES})

# Set the source folder
set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)

# Get all .cpp files in the source folder
file(GLOB_RECURSE CPP_FILES ${SOURCE_DIR}/*.cpp)

# Initialize an empty list to store filenames without extensions
set(FILES_NO_EXT)

# Extract filenames without extensions and add them to the list
foreach(CPP_FILE ${CPP_FILES})
    # Get the filename without extension
    get_filename_component(FILENAME_NO_EXT ${CPP_FILE} NAME_WE)
    # Append the filename to the list
    # list(APPEND FILES_NO_EXT ${FILENAME_NO_EXT})
    add_library(${FILENAME_NO_EXT} SHARED ${CPP_FILE})
    target_link_libraries(${FILENAME_NO_EXT} ${common_lib})
    install(TARGETS ${FILENAME_NO_EXT} DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
    if(BUILD_TEST)
        add_executable(${FILENAME_NO_EXT}_test test/${FILENAME_NO_EXT}_test.cpp)
        target_link_libraries(${FILENAME_NO_EXT}_test ${common_lib} ${CMAKE_INSTALL_PREFIX}/lib/lib${FILENAME_NO_EXT}.so)
    endif()
endforeach()