cmake_minimum_required(VERSION 3.25.1)

add_executable(server
    server.cpp
    main.cpp)

target_include_directories(server PRIVATE
    ${PROJECT_SOURCE_DIR}/server
    ${PROJECT_SOURCE_DIR})

target_precompile_headers(server PRIVATE ${PROJECT_SOURCE_DIR}/precompiled.h)