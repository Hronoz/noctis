# This file handles building each task as sub-project.
#
# Each task becomes an independent project in which you can experiment.
#
# Tasks are added as separate sub-projects so as compilation errors in
# one task don't affect another task.

cmake_minimum_required(VERSION 3.27)
project(noctis)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory("${PROJECT_SOURCE_DIR}/engine" "${PROJECT_SOURCE_DIR}/engine/bin")
add_subdirectory("${PROJECT_SOURCE_DIR}/testbed" "${PROJECT_SOURCE_DIR}/testbed/bin")