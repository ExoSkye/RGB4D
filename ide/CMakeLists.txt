project(PPEN_IDE LANGUAGES CXX VERSION 1.0.0 )

add_subdirectory(libs/sdl)
add_subdirectory(libs/glew)

find_package(OpenGL 3.0 REQUIRED)

add_subdirectory(libs/nativefiledialog-protobyter)

add_executable(PPEN_IDE main.cpp libs/imgui/imgui.cpp libs/imgui/imgui_draw.cpp libs/imgui/imgui_tables.cpp libs/imgui/imgui_widgets.cpp libs/imgui/backends/imgui_impl_opengl3.cpp libs/imgui/backends/imgui_impl_sdl.cpp)
target_include_directories(PPEN_IDE PUBLIC ../interpreter libs/sdl/include libs/imgui/backends libs/imgui libs/nativefiledialog-protobyter/src/include)
target_link_libraries(PPEN_IDE PUBLIC SDL2 OpenGL libglew_shared nativefiledialog)