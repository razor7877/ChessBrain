cmake_minimum_required(VERSION 3.28)
project(ChessBrain)

#add_subdirectory(abseil)
#add_subdirectory(protobuf)

# Recursively find all source files
file(GLOB_RECURSE sources src/*(.c|.cpp) include/*(.h|.hpp))

find_package(OpenGL REQUIRED)

# Add sources to target
add_executable(ChessBrain ${sources})
# Require C++ 17 standard for structured bindings
set_property(TARGET ChessBrain PROPERTY CXX_STANDARD 17)

# Add header files
#include_directories(probotuf/src)
#include_directories(abseil/)
#target_include_directories(ChessBrain PUBLIC tensorflow/
#C:/Users/kylia/Desktop/GitHub/ChessBrain/tensorflow/external/ml_dtypes/_virtual_includes/int4
#C:/Users/kylia/Desktop/GitHub/ChessBrain/tensorflow/external/ml_dtypes/_virtual_includes/float8)
#target_include_directories(ChessBrain PUBLIC models/)
target_include_directories(ChessBrain PUBLIC include/)

#target_include_directories(ChessBrain PUBLIC C:/Users/kylia/Desktop/GitHub/tensorflow-2.15.0/bazel-bin/tensorflow/include)

# Link GLFW and OpenGL
target_link_libraries(ChessBrain PUBLIC
	${ChessBrain_SOURCE_DIR}/libs/glfw3.lib
	${ChessBrain_SOURCE_DIR}/libs/libcurl_imp.lib
	OpenGL::GL ${libs})
#target_link_libraries(ChessBrain PUBLIC ${ChessBrain_SOURCE_DIR}/libs/tensorflow.lib)