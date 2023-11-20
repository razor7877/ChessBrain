cmake_minimum_required(VERSION 3.28)
project(ChessBrain)

# Recursively find all source files
file(GLOB_RECURSE sources src/*(.cpp|.c) include/*.h)

find_package(OpenGL REQUIRED)

# Add sources to project
add_executable(ChessBrain ${sources})
# Add header files
target_include_directories(ChessBrain PUBLIC include/)
target_link_libraries(ChessBrain PUBLIC ${ChessBrain_SOURCE_DIR}/libs/glfw3.lib OpenGL::GL)