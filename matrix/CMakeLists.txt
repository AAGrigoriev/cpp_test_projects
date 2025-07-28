cmake_minimum_required(VERSION 3.28)

project(matrix VERSION 0.0.$ENV{GITHUB_RUN_NUMBER})

SET(SOURCES src)
SET(HEADERS inc)
SET(TEST_WAY test)

add_executable(matrix ${SOURCES}/main.cpp ${HEADERS}/hashFunction.hpp ${HEADERS}/matrix.hpp)

set (CMAKE_CXX_STANDARD 17)

target_include_directories(matrix PRIVATE 
                                  inc)                

find_package(GTest REQUIRED)
find_package(Threads)

add_executable(g_test_matrix ${TEST_WAY}/main.cpp)

target_link_libraries(g_test_matrix 
                      PRIVATE
                      ${GTEST_LIBRARIES}
                      ${GTEST_MAIN_LIBRARIES}
                      pthread)

target_include_directories(g_test_matrix 
                           PRIVATE
                           ${GTEST_INCLUDE_DIRS}
                           inc)

install(TARGETS matrix RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)

add_test(g_test_matrix g_test_matrix)
