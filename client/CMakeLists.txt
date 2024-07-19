cmake_minimum_required(VERSION 3.25.1)

add_executable(client
    client.cpp
    main.cpp)

target_include_directories(client PRIVATE
    ${PROJECT_SOURCE_DIR}/client
    ${PROJECT_SOURCE_DIR})

target_precompile_headers(client PRIVATE ${PROJECT_SOURCE_DIR}/precompiled.h)