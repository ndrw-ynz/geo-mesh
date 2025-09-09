cmake_minimum_required(VERSION 3.14)
project(OpenGLPractice)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# -------------------------------
# GLAD (vendored)
# -------------------------------
add_library(glad STATIC external/glad/src/glad.c)
target_include_directories(glad PUBLIC external/glad/include)

# -------------------------------
# GLFW (vendored source package)
# -------------------------------
set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "OFF")
set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "OFF")
set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "OFF")
set(GLFW_INSTALL OFF CACHE INTERNAL "OFF")
add_subdirectory(external/glfw-3.4)

# -------------------------------
# stb
# -------------------------------
add_library(stb_image STATIC external/stb_image/stb_image.cpp)
target_include_directories(stb_image PUBLIC external/stb_image)

# -------------------------------
# GLM (header-only, target-specific)
# -------------------------------
add_library(glm INTERFACE)
target_include_directories(glm INTERFACE external/glm)

# -------------------------------
# Sources + Executable
# -------------------------------
file(GLOB_RECURSE SRC_FILES src/*.cpp)
add_executable(${PROJECT_NAME} ${SRC_FILES})

# Project’s own includes
target_include_directories(${PROJECT_NAME} PRIVATE src)


# -------------------------------
# Link libraries
# -------------------------------
target_link_libraries(${PROJECT_NAME} PRIVATE
    glad
    glfw
    stb_image
    glm
)

# -------------------------------
# Copy resources (assets)
# -------------------------------
add_custom_target(copy_assets ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/data
    ${CMAKE_BINARY_DIR}/data
)
