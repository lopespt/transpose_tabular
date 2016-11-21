cmake_minimum_required (VERSION 2.8)

# projectname is the same as the main-executable
project(transpose_tabular)

add_definitions('-g')
add_definitions('-Wall')
add_definitions('-std=c++11')

#set(CMAKE_EXPORT_COMPILE_COMMANDS on)

add_executable(${PROJECT_NAME} main.cpp)

