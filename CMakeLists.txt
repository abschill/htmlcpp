cmake_minimum_required(VERSION 3.10)

project(HTMLC VERSION 1.0)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
add_subdirectory(djson)
add_subdirectory(fmt)
add_executable(HTMLC lib/htmlc.cc)
configure_file(HTMLC.in.h HTMLC.h)
target_link_libraries(HTMLC djson::djson)
target_link_libraries(HTMLC fmt)
target_include_directories(HTMLC PUBLIC 
                            "${PROJECT_BINARY_DIR}")