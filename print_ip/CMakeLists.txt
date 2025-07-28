cmake_minimum_required(VERSION 3.28)

project(project VERSION 0.0.$ENV{GITHUB_RUN_NUMBER})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(project main.cpp)

add_subdirectory(helper)
add_subdirectory(test)

link_libraries(INTERFACE helper)



install(TARGETS project RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)


enable_testing()
