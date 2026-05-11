cmake_minimum_required(VERSION 3.10)
project(W3D_Compiler)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Основной исполняемый файл
add_executable(w3d_compiler
    src/main.cpp
    src/compiler.cpp
    src/lexer.cpp
    src/parser.cpp
)

# Включаемые директории
target_include_directories(w3d_compiler PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Флаги компиляции
if(MSVC)
    target_compile_options(w3d_compiler PRIVATE /W4)
else()
    target_compile_options(w3d_compiler PRIVATE -Wall -Wextra -Wpedantic)
endif()
