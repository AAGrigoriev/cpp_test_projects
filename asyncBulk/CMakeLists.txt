cmake_minimum_required(VERSION 3.18)

project(bulk_async)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package (Threads)


file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")

add_executable(bulk_exe ${SOURCES})

target_link_libraries (bulk_exe ${CMAKE_THREAD_LIBS_INIT})

target_include_directories(bulk_exe PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/inc)