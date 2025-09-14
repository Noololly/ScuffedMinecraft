cmake_minimum_required(VERSION 3.20)
project(ScuffedMinecraft LANGUAGES CXX C)
set(CMAKE_GENERATOR_PLATFORM x64)

# Set C++ Standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Create the executable
add_executable(ScuffedMinecraft 
    src/main.cpp 
    src/CrosshairMaterial.cpp
    src/BlockOutlineMaterial.cpp
    WillowVoxEngine/src/WillowVoxStubs.cpp  # Minimal stub implementations
)

# Set output directories
set_target_properties(ScuffedMinecraft PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Include directories
target_include_directories(ScuffedMinecraft PRIVATE
    include                     # Game-specific includes
    WillowVoxEngine/include     # WillowVox headers
    WillowVoxEngine/thirdparty  # WillowVox dependencies
    WillowVoxEngine/thirdparty/GLFW  # GLFW headers
)

# Add imgui subdirectory to build it from source
add_subdirectory(WillowVoxEngine/thirdparty/imgui)

# Find required system packages
find_package(PkgConfig REQUIRED)
pkg_check_modules(GLFW3 REQUIRED glfw3)
find_package(OpenGL REQUIRED)

# Link dependencies
target_link_libraries(ScuffedMinecraft PRIVATE 
    imgui
    ${GLFW3_LIBRARIES}
    ${OPENGL_LIBRARIES}
)

# Copy assets to the output directory
add_custom_target(copy_assets ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets
    ${CMAKE_BINARY_DIR}/bin/assets
    COMMENT "Copying assets"
)

# Add platform-specific preprocessor definitions
if(WIN32)
    target_compile_definitions(ScuffedMinecraft PUBLIC PLATFORM_WINDOWS)
elseif(APPLE)
    target_compile_definitions(ScuffedMinecraft PUBLIC PLATFORM_MACOS)
elseif(UNIX)
    target_compile_definitions(ScuffedMinecraft PUBLIC PLATFORM_LINUX)
else()
    message(FATAL_ERROR "Unknown platform!")
endif()