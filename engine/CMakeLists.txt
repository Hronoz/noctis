find_package(X11 REQUIRED)
link_libraries(${X11_xcb_LIB})
link_libraries(${X11_xcb_ewmh_LIB})
link_libraries(${X11_xcb_xkb_LIB})
link_libraries(${X11_xkbcommon_LIB})
include_directories(${XCB_INCLUDE_DIR})

add_library(engine SHARED src/engine.cpp
        src/core/logger.cpp
        src/platform/platform_linux.cpp
        include/core/resource.hpp
        src/core/resource.cpp)
target_include_directories(engine PUBLIC ${PROJECT_SOURCE_DIR}/engine/include)

# install(TARGETS testbed LIBRARY DESTINATION lib ARCHIVE DESTINATION bin)