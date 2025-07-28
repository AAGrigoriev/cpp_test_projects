cmake_minimum_required(VERSION 3.10)

if(DEFINED ENV{GITHUB_RUN_NUMBER})
    set(VERSION 0.0.$ENV{GITHUB_RUN_NUMBER})
else()
    set(VERSION 0.0.1)
endif()

project(bayan VERSION ${VERSION})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SRC_PATH  "src")
set(H_PATH    "include")
set(W_LIB     ${CMAKE_PROJECT_NAME}_lib)
set(EXEC_NAME ${CMAKE_PROJECT_NAME})
set(TEST_NAME gtest_${CMAKE_PROJECT_NAME})
set(TEST_PATH "test/")

find_package(Boost COMPONENTS program_options REQUIRED )
#include_directories( ${Boost_INCLUDE_DIR} )
find_package(Threads)
#find_package(Doxygen COMPONENTS dot)

add_executable(${EXEC_NAME} main.cpp)

# LIBRARY 
add_library(${W_LIB} 
  ${SRC_PATH}/com_parser.cpp
  ${SRC_PATH}/dir_parser.cpp
  ${SRC_PATH}/filter.cpp
  ${SRC_PATH}/mask.cpp
  ${SRC_PATH}/file_dublicate_parser.cpp
  ${H_PATH}/com_parser.hpp
  ${H_PATH}/dir_parser.hpp
  ${H_PATH}/file_comparator.hpp
  ${H_PATH}/file_dublicate_parser.hpp
  ${H_PATH}/file_wrapper.hpp
  ${H_PATH}/filter.hpp
  ${H_PATH}/mask.hpp
  ${H_PATH}/options.hpp
 )

target_link_libraries(${W_LIB}      PRIVATE ${Boost_LIBRARIES})
target_include_directories(${W_LIB} PRIVATE ${Boost_INCLUDE_DIR})
target_include_directories(${W_LIB} PRIVATE ${H_PATH})

# PROJECT 
target_link_libraries(${EXEC_NAME}      PRIVATE ${W_LIB})
target_include_directories(${EXEC_NAME} PRIVATE ${H_PATH})

# Test
find_package(GTest CONFIG REQUIRED)
include(GoogleTest)

add_executable(${TEST_NAME}
  ${TEST_PATH}/main_test.cpp
  ${TEST_PATH}/mask_test.cpp
  ${TEST_PATH}/bayan_test.cpp
)

target_link_libraries(${TEST_NAME} PRIVATE
  pthread
  GTest::gtest
  GTest::gmock
  ${W_LIB})

target_include_directories(${TEST_NAME} PRIVATE ${H_PATH})
enable_testing()
add_test(${TEST_NAME}  ${TEST_NAME})

file(COPY ${CMAKE_SOURCE_DIR}/test/data DESTINATION ${CMAKE_BINARY_DIR})

install(TARGETS ${EXEC_NAME} RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT grigormaklaud@gmail.com)
include(CPack)
