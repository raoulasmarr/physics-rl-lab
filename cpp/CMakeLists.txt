cmake_minimum_required(VERSION 3.21)

project(ai_runner LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(MUJOCO_ROOT 
    "C:/Users/raoul/libraries/mujoco-3.13.0-windows-X86_64"
    CACHE PATH "Path to MuJoCo SDK")

add_library(mujoco_sdk SHARED IMPORTED GLOBAL)

set_target_properties(mujoco_sdk PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${MUJOCO_ROOT}/include"
    IMPORTED_IMPLIB "${MUJOCO_ROOT}/lib/mujoco.lib"
    IMPORTED_LOCATION "${MUJOCO_ROOT}/bin/mujoco.dll"
)

add_executable(ai_runner
               src/main.cpp
               src/environment.cpp
               src/humanoid_environment.cpp)

target_include_directories(ai_runner PRIVATE include)
target_compile_definitions(ai_runner PRIVATE AI_RUNNER_ASSET_DIR="${CMAKE_CURRENT_SOURCE_DIR}/assets")

target_link_libraries(ai_runner PRIVATE mujoco_sdk)

add_custom_command(TARGET ai_runner POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${MUJOCO_ROOT}/bin/mujoco.dll"
        "$<TARGET_FILE_DIR:ai_runner>"
)