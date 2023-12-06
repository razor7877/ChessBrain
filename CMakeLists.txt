cmake_minimum_required(VERSION 3.28)
project(ChessBrain)

find_package(OpenGL REQUIRED)

# Add library subfolders
add_subdirectory(libs/glfw)
add_subdirectory(libs/glm)
add_subdirectory(libs/curl)

# Recursively find all source files
file(GLOB_RECURSE sources src/*(.c|.cpp) include/*(.h|.hpp))

# Add sources to target
add_executable(ChessBrain ${sources})
# Require C++ 17 standard for structured bindings
set_property(TARGET ChessBrain PROPERTY CXX_STANDARD 17)

# Add header files
target_include_directories(ChessBrain PUBLIC
	include
	libs/glfw/include
	libs/glm/
	libs/curl/include)

# Link all required libraries
target_link_libraries(ChessBrain PUBLIC
	glfw
	libcurl_static
	OpenGL::GL ${libs})

# Copy textures and shaders to binary folder
file(COPY images DESTINATION ${ChessBrain_BINARY_DIR}/Debug)
file(COPY src/shaders DESTINATION ${ChessBrain_BINARY_DIR}/Debug)