cmake_minimum_required(VERSION 3.5)
project(fasterSimIdDictionary)
add_library(fasterSimIdDictionary SHARED
	src/Source.cpp
	src/RedoBlHooks.cpp
	src/Torque.cpp
)
set_target_properties(fasterSimIdDictionary PROPERTIES PREFIX "")
target_link_libraries(
	fasterSimIdDictionary
	psapi
)
