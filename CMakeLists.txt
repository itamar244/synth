cmake_minimum_required(VERSION 3.5)

project(Synth)

set(CMAKE_CXX_COMPILER "clang++-6.0")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(PROJECT_SOURCE_DIR src)

# links sfml object files by adding link flags to compiler
set(CMAKE_CXX_LINK_FLAGS
	${CMAKE_CXX_LINK_FLAGS} "-lsfml-graphics -lsfml-window -lsfml-system")

file(GLOB_RECURSE Synth_SRC
  "src/*.cc"
)

add_executable(${PROJECT_NAME} ${Synth_SRC})
