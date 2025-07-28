cmake_minimum_required(VERSION 3.28)

project(test)

find_package(GTest REQUIRED)
find_package(Threads)

add_executable(g_test_print_ip main.cpp print_ip_test.cpp)

target_link_libraries(g_test_print_ip 
                                    PRIVATE 
                                    ${GTEST_LIBRARIES} 
                                    ${GTEST_MAIN_LIBRARIES} 
                                    pthread)

target_include_directories(g_test_print_ip PRIVATE ${CMAKE_SOURCE_DIR}/helper)


add_test(g_test_print_ip g_test_print_ip)
