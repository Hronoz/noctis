cmake_minimum_required(VERSION 3.27)
project(testbed)

set(CMAKE_CXX_STANDARD 20)

add_executable(testbed src/main.cpp)
target_link_libraries(testbed PRIVATE engine)
get_target_property(ENGINE_SOURCE_DIR engine SOURCE_DIR)
target_include_directories(testbed PUBLIC ${ENGINE_SOURCE_DIR}/src)
# install(TARGETS testbed RUNTIME DESTINATION bin)