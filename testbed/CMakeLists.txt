cmake_minimum_required(VERSION 3.27)
project(testbed)

set(CMAKE_CXX_STANDARD 20)

add_executable(testbed src/main.cpp)
target_link_libraries(testbed PRIVATE engine)
target_include_directories(testbed PUBLIC ${PROJECT_SOURCE_DIR}/engine/include)
# install(TARGETS testbed RUNTIME DESTINATION bin)