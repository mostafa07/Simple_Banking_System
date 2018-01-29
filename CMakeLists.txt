cmake_minimum_required(VERSION 3.7)
project(DS_Project_Banking_System)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Account.cpp Account.h Employee.cpp Employee.h LinkedList.h)
add_executable(DS_Project_Banking_System ${SOURCE_FILES})