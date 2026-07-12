cmake_minimum_required(VERSION 3.10)
project(SAO_Hook LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Position independent code for DLL
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# ImGui sources
set(IMGUI_SRC
    imgui/imgui.cpp
    imgui/imgui_demo.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_tables.cpp
    imgui/imgui_widgets.cpp
    imgui/backends/imgui_impl_win32.cpp
    imgui/backends/imgui_impl_dx11.cpp
)

# MinHook sources
set(MINHOOK_SRC
    kiero/minhook/src/buffer.c
    kiero/minhook/src/hook.c
    kiero/minhook/src/trampoline.c
    kiero/minhook/src/hde/hde32.c
    kiero/minhook/src/hde/hde64.c
)

# Main sources
set(MAIN_SRC
    src/main.cpp
    src/features.cpp
    src/game.cpp
    src/il2cp.cpp
)

# Kiero source
set(KIERO_SRC
    kiero/kiero.cpp
)

# Create shared library (DLL)
add_library(${PROJECT_NAME} SHARED
    ${MAIN_SRC}
    ${IMGUI_SRC}
    ${MINHOOK_SRC}
    ${KIERO_SRC}
)

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE
    imgui
    imgui/backends
    kiero
    kiero/minhook/include
    src
)

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
    d3d11
    dxgi
    winmm
    imm32
    version
)

# DLL settings
set_target_properties(${PROJECT_NAME} PROPERTIES
    SUFFIX ".dll"
    PREFIX ""
)

# Define _CRT_SECURE_NO_WARNINGS
target_compile_definitions(${PROJECT_NAME} PRIVATE
    _CRT_SECURE_NO_WARNINGS
)
