cmake_minimum_required(VERSION 3.25.1)

project(ClientServerExample LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(client)
add_subdirectory(server)