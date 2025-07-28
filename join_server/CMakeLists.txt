cmake_minimum_required(VERSION 3.20)

project(join_server LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(pegtl REQUIRED)
find_package(Boost COMPONENTS COMPONENTS program_options system REQUIRED)

add_executable(join_server
    main.cpp
    parsing.hpp
    network.hpp
    network.cpp
    table.cpp
    table.hpp
    database_error.cpp
    database_error.hpp
    database.hpp
    database.cpp
)

add_executable(unit_tests
    tests/unit_tests.cpp
    parsing.hpp
    table.hpp
    table.cpp
    database_error.cpp
    database_error.hpp)

target_link_libraries(join_server taocpp::pegtl ${Boost_LIBRARIES})


target_link_libraries(unit_tests
    gtest)

install(TARGETS join_server RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT grigormaklaud@gmail.com)

include(CPack)

enable_testing()

add_test(unit_tests unit_tests)

