find_package(X11 REQUIRED)
link_libraries(${X11_LIBRARIES})
include_directories(${XCB_INCLUDE_DIR})

add_library(engine SHARED src/engine.cpp
        src/core/logger.cpp
        src/platform/platform_linux.cpp)
target_include_directories(engine PUBLIC ${PROJECT_SOURCE_DIR}/engine/include)

# install(TARGETS testbed LIBRARY DESTINATION lib ARCHIVE DESTINATION bin)