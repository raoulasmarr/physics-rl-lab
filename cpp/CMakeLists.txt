cmake_minimum_required(VERSION 3.21)

project(ai_runner LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(ai_runner src/main.cpp)