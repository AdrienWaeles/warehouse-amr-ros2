cmake_minimum_required(VERSION 3.16)
project(amr VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(amr_core STATIC src/version.cpp)
target_include_directories(amr_core PUBLIC include)

add_executable(amr_robot src/main.cpp)
target_link_libraries(amr_robot PRIVATE amr_core)
