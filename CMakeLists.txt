cmake_minimum_required(VERSION 3.5)
project(fasterSimIdDictionary VERSION 0.0.1)

add_compile_definitions(PROJECT_NAME="${CMAKE_PROJECT_NAME}")
add_compile_definitions(PROJECT_EXPORT=${CMAKE_PROJECT_NAME})
add_compile_definitions(PROJECT_VERSION="${CMAKE_PROJECT_VERSION}")


add_library(fasterSimIdDictionary SHARED
	src/Source.cpp
	src/RedoBlHooks.cpp
	src/Torque.cpp
)