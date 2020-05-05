cmake_minimum_required(VERSION 3.15)
project(principles_and_practice_using_cpp 
	VERSION 1.0
	DESCRIPTION "This project contains my implementation of problems from Programming Principles and Practice using C++"
	LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

set(FLTK_DIR "$ENV{FLTK_HOME}")
find_package(FLTK REQUIRED NO_MODULE)

add_subdirectory(part_1_the_basics)
add_subdirectory(part_2_input_and_output)
add_subdirectory(thirdparties/graphics)
