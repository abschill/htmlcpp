cmake_minimum_required(VERSION 3.10)

project(HTMLC VERSION 1.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
add_subdirectory(djson)

include_directories(include/)
add_executable(HTMLC lib/htmlc.cc lib/config.cc)
configure_file(include/htmlc.in.hh htmlc.hh)
target_include_directories(HTMLC PUBLIC "${PROJECT_BINARY_DIR}")
target_link_libraries(HTMLC djson::djson)
