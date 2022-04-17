cmake_minimum_required(VERSION 3.21)
project(untitled5)

set(CMAKE_CXX_STANDARD 23)
find_package(SFML 2.5 COMPONENTS graphics audio)
add_executable(untitled5 main.cpp Animation.h)
target_link_libraries(untitled5 sfml-graphics sfml-audio)
