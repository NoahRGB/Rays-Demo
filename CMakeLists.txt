cmake_minimum_required(VERSION 3.16)
project(rays)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

add_subdirectory(vendored/SDL EXCLUDE_FROM_ALL)

add_executable(rays 
    main.cpp
    application.h
    application.cpp
    vec2.h
    vec2.cpp
    circle.h
    circle.cpp
    ray.h
    ray.cpp
)

target_link_libraries(rays PRIVATE SDL3::SDL3)

add_custom_target(run
    COMMAND rays
    DEPENDS rays
    WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
)