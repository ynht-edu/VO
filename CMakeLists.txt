cmake_minimum_required(VERSION 3.8)
project(visual_odometry)

find_package(OpenCV REQUIRED)
find_package(Eigen3 REQUIRED)


add_library(feature_methods src/feature_method.cpp)
target_include_directories(feature_methods PRIVATE include) 
target_link_libraries(feature_methods PRIVATE ${OpenCV_LIBS} Eigen3::Eigen)

add_library(camera_motion src/camera_motion.cpp)
target_include_directories(camera_motion PRIVATE include) 
target_link_libraries(camera_motion PRIVATE ${OpenCV_LIBS} Eigen3::Eigen)

add_executable(feature_method_main src/feature_method_main.cpp)
target_include_directories(feature_method_main PRIVATE include) 
target_link_libraries(feature_method_main feature_methods ${OpenCV_LIBS})
