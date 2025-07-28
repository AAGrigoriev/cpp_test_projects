cmake_minimum_required(VERSION 3.5)

if(DEFINED ENV{GITHUB_RUN_NUMBER})
    set(VERSION 0.0.$ENV{GITHUB_RUN_NUMBER})
else()
    set(VERSION 0.0.1)
endif()

project(async_writer VERSION ${VERSION})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost COMPONENTS program_options REQUIRED )
find_package(Threads)
find_package(GTest REQUIRED)

add_library(async STATIC
    main.cpp
    context.hpp
    context.cpp
    processing/parser.hpp
    processing/parser.cpp
    processing/controller.hpp
    processing/controller.cpp
    processing/accumulator.hpp
    processing/accumulator.cpp
    utility/command.hpp
    utility/command.cpp
    utility/utility.hpp
    utility/notify_queue.hpp
    post_processing/postprocessor.hpp
    post_processing/postprocessor.cpp
    post_processing/postprocessor_handler.hpp
    post_processing/output_handler.hpp
    post_processing/output_handler.cpp
    post_processing/logging_handler.hpp
    post_processing/logging_handler.cpp
    post_processing/postprocessor_handler.cpp
    async.hpp
    async.cpp)

include_directories(${GTEST_INCLUDE_DIR})
include_directories(${Boost_INCLUDE_DIR})
include_directories(utility)
include_directories(processing)
include_directories(post_processing)


target_link_libraries(async
        ${Boost_LIBRARIES}
        ${CMAKE_THREAD_LIBS_INIT})


add_executable(main main.cpp)
target_link_libraries(main async)


add_executable(unit_tests
    test/controller_test.cpp
    test/parser_test.cpp
    test/main.cpp)

target_link_libraries(unit_tests
        gtest
        pthread
        async)

enable_testing()

add_test(unit_tests unit_tests)

install(TARGETS main RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT grigormaklaud@gmail.com)

include(CPack)

