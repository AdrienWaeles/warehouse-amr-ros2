cmake_minimum_required(VERSION 3.16)
project(amr VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(amr_warnings -Wall -Wextra -Wpedantic -Wshadow)
option(AMR_ENABLE_SANITIZERS "Build with ASan and UBSan" OFF)

add_library(amr_core STATIC src/version.cpp)
target_compile_options(amr_core PRIVATE ${amr_warnings})
target_include_directories(amr_core PUBLIC include)

if(AMR_ENABLE_SANITIZERS)
    target_compile_options(amr_core PUBLIC -fsanitize=address,undefined -fno-omit-frame-pointer)
    target_link_options(amr_core PUBLIC -fsanitize=address,undefined)
endif()

add_executable(amr_robot src/main.cpp)
target_compile_options(amr_robot PRIVATE ${amr_warnings})
target_link_libraries(amr_robot PRIVATE amr_core)
