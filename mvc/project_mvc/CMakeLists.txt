cmake_minimum_required(VERSION 3.10)

project (project_mvc)

set(CORE_PATH "core")
set(OBJ_PATH  "objects")

SET(SOURCE_CORE  
${CORE_PATH}/controller.cpp
${CORE_PATH}/model.cpp
${CORE_PATH}/view.cpp
${CORE_PATH}/view.cpp
${OBJ_PATH}/baseShape.cpp
${OBJ_PATH}/circle.cpp
${OBJ_PATH}/dot.cpp
main.cpp
)

add_executable(main ${SOURCE_CORE})

target_include_directories(main PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
