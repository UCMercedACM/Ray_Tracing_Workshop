cmake_minimum_required(VERSION 3.10)

project(Ray_Tracing_Workshop)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${CMAKE_SOURCE_DIR}/lib/Include)

link_directories(${CMAKE_SOURCE_DIR}/lib/Lib)

file(GLOB_RECURSE SRC_FILES "source/*.cpp" "source/*.c")
file(GLOB_RECURSE HEADER_FILES "source/*.h")
file(GLOB_RECURSE SHADER_FILES "source/Shaders/*.shader")
file(GLOB_RECURSE RES_FILES "source/*.jpg" "source/*.png")

list(FILTER SRC_FILES EXCLUDE REGEX "source/imgui3/*.cpp")
list(FILTER HEADER_FILES EXCLUDE REGEX "source/imgui3/*.h")

add_executable(Ray_Tracing_Workshop ${SRC_FILES} ${HEADER_FILES} ${SHADER_FILES} ${RES_FILES} source/main.cpp)

source_group("Source Files" FILES ${SRC_FILES})
source_group("Header Files" FILES ${HEADER_FILES})
source_group("Shader Files" FILES ${SHADER_FILES})
source_group("Resources" FILES ${RES_FILES})

target_link_libraries(Ray_Tracing_Workshop glfw3.lib)
target_link_libraries(Ray_Tracing_Workshop opengl32.lib)