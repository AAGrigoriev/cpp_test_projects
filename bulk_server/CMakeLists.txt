cmake_minimum_required(VERSION 3.20)


if(DEFINED ENV{GITHUB_RUN_NUMBER})
    project(bulk_server VERSION 0.0.$ENV{GITHUB_RUN_NUMBER})
else()
    project(bulk_server VERSION 0.0.1)
endif()

find_package(Boost COMPONENTS COMPONENTS program_options system REQUIRED)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(NETWORK
    network/session.cpp
    network/session.hpp
    network/data_handler.cpp
    network/data_handler.hpp
    network/server.cpp
    network/server.hpp)

set(UTILS
    utils/command_parser.cpp
    utils/command_parser.hpp
    utils/thread_pool.cpp
    utils/thread_pool.hpp)

set(LOGIC
    logic/controller.cpp
    logic/controller.hpp
    logic/global_context.cpp
    logic/global_context.hpp
    logic/post_controller.cpp
    logic/post_controller.hpp
    logic/command.cpp
    logic/command.hpp
    logic/command_buffer.cpp
    logic/command_buffer.hpp
    logic/i_writer.hpp
    logic/i_writer.cpp
    logic/file_writer.cpp
    logic/file_writer.hpp
    logic/console_writer.cpp
    logic/console_writer.hpp)

include_directories(logic)
include_directories(network)
include_directories(utils)

add_executable(bulk_server main.cpp ${NETWORK} ${UTILS} ${LOGIC})
target_link_libraries(bulk_server ${Boost_LIBRARIES})

install(TARGETS bulk_server DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT grigormaklaud@gmail.com)

include(CPack)
