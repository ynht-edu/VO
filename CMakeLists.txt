cmake_minimum_required(VERSION 3.8)
project(visual_odometry)

find_package(OpenCV REQUIRED)
find_package(Eigen3 REQUIRED)


add_library(feature_methods src/feature_method.cpp)
target_include_directories(feature_methods PUBLIC include) 
target_link_libraries(feature_methods PUBLIC ${OpenCV_LIBS} Eigen3::Eigen)

add_library(camera_motion src/camera_motion.cpp)
target_include_directories(camera_motion PUBLIC include) 
target_link_libraries(camera_motion PUBLIC ${OpenCV_LIBS} Eigen3::Eigen)

add_executable(feature_method_main src/feature_method_main.cpp)
target_link_libraries(feature_method_main feature_methods)

add_executable(visual_odometry src/main.cpp)
target_link_libraries(visual_odometry feature_methods camera_motion)
