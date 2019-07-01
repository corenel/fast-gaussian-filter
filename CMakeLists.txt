cmake_minimum_required(VERSION 3.10)
project(fast_gaussian_filter)

set(CMAKE_CXX_STANDARD 14)
add_definitions(-Wall -O2)

# OpenCV
find_package(OpenCV REQUIRED)
message("Using OpenCV: ${OpenCV_INCLUDE_DIRS}")

include_directories(
    include
    ${OpenCV_INCLUDE_DIRS}
)

add_executable(${PROJECT_NAME}
    src/base.cpp
    src/cv_gaussian_blur.cpp
    src/main.cpp
    )

target_link_libraries(
    ${PROJECT_NAME}
    ${OpenCV_LIBS}
)
