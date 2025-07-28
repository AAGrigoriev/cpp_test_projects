cmake_minimum_required(VERSION 3.10)

if($ENV{GITHUB_RUN_NUMBER})
  set(VERSION 0.0.$ENV{GITHUB_RUN_NUMBER})
else()
  set(VERSION 0.0.0)
endif()


project(command_parser VERSION ${VERSION})

set(CMAKE_CXX_STANDARD 17)
SET(COMMAND_PATH "command")
SET(CORE_PATH "core")
SET(OBSERVER_PATH "observer")

add_executable(command_parser
main.cpp 
${COMMAND_PATH}/simpleCommand.cpp 
${CORE_PATH}/console_writer.cpp
${CORE_PATH}/file_writer.cpp
${CORE_PATH}/reader.cpp
)

target_include_directories(command_parser PRIVATE
${COMMAND_PATH}
${CORE_PATH}
${OBSERVER_PATH}
)

find_package(GTest REQUIRED)
include(GoogleTest)

add_executable(command_test
tests/test.cpp
${COMMAND_PATH}/simpleCommand.cpp
${CORE_PATH}/console_writer.cpp
${CORE_PATH}/file_writer.cpp
${CORE_PATH}/reader.cpp)

target_include_directories(command_test PRIVATE
${COMMAND_PATH}
${CORE_PATH}
${OBSERVER_PATH}
)

target_link_libraries(command_test PRIVATE pthread GTest::gtest_main)
enable_testing()
add_test(command_test command_test)


install(TARGETS command_parser RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)
