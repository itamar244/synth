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
	"-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio"
)

file(GLOB_RECURSE Synth_SRC ${PROJECT_SOURCE_DIR}/*.cc)

add_subdirectory(${PROJECT_LIB_DIR}/melolang)
add_subdirectory(${PROJECT_LIB_DIR}/atic)

add_executable(${PROJECT_NAME} ${Synth_SRC})

find_package(Boost COMPONENTS system filesystem REQUIRED)

target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR})

# link libraries
target_link_libraries(${PROJECT_NAME}
  PRIVATE ${Boost_FILESYSTEM_LIBRARY}
  PRIVATE ${Boost_SYSTEM_LIBRARY}
	PRIVATE Atic
	PRIVATE MeloLang
)
