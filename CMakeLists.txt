cmake_minimum_required(VERSION 3.27)
project(AnotherExperimentalRepoWithSockets)

set(CMAKE_CXX_STANDARD 26)

add_executable(SERVER server.hpp server.cpp)
add_executable(CLIENT client.hpp client.cpp)