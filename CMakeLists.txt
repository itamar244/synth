cmake_minimum_required(VERSION 3.5)

project(Synth VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_COMPILER clang++-6.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(PROJECT_SOURCE_DIR src)
set(PROJECT_LIB_DIR lib)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

# links sfml object files by adding link flags to compiler
set(CMAKE_CXX_LINK_FLAGS ${CMAKE_CXX_LINK_FLAGS}
	"-lboost_system -lboost_filesystem\
	-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio"
)

file(GLOB_RECURSE Synth_SRC ${PROJECT_SOURCE_DIR}/*.cc)

add_executable(${PROJECT_NAME} ${Synth_SRC})

add_subdirectory(${PROJECT_LIB_DIR}/atic)
target_link_libraries(${PROJECT_NAME} PRIVATE Atic)
