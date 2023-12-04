cmake_minimum_required(VERSION 3.0.0)
project(udp_test VERSION 0.1.0)

add_executable(udp_server server.cpp)
# target_link_libraries(depth_image ${OpenCV_LIBS})

add_executable(udp_client client.cpp)