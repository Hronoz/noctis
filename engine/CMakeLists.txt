find_package(Vulkan REQUIRED)
find_package(glm REQUIRED)
find_package(glfw3 REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/engine/src)

set(IMGUI_SOURCES
        lib/imgui/imgui.cpp
        lib/imgui/imgui_demo.cpp
        lib/imgui/imgui_draw.cpp
        lib/imgui/imgui_tables.cpp
        lib/imgui/imgui_stdlib.cpp
        lib/imgui/imgui_widgets.cpp
        lib/imgui/imgui_impl_glfw.cpp
        lib/imgui/imgui_impl_vulkan.cpp
)

add_library(engine SHARED src/noctis.cpp
        src/noctis.hpp
        src/noctis/Logger.cpp
        src/noctis/Logger.hpp
        src/noctis/Game.cpp
        src/noctis/Game.hpp
        src/noctis/Renderer.cpp
        src/noctis/Renderer.hpp
        ${IMGUI_SOURCES}
        ${TRACY_SOURCES}
)

target_include_directories(engine PUBLIC ${PROJECT_SOURCE_DIR}/engine)
target_include_directories(engine PRIVATE ${PROJECT_SOURCE_DIR}/engine/lib)

target_link_libraries(engine Vulkan::Vulkan)
target_link_libraries(engine glm::glm)
target_link_libraries(engine glfw)