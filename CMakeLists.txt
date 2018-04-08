cmake_minimum_required(VERSION 2.8)

project(SpaceInvaders)

include_directories(include)

file(GLOB_RECURSE SRC "Source/*.cpp" "Source/*.h")

add_executable(${PROJECT_NAME} ${SRC})

include_directories(deps/SFML/include)

add_definitions(-DSFML_STATIC)

enable_testing()

set(SFML_BUILD_DOC OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(CMAKE_BUILD_TYPE Debug)
add_subdirectory(deps/SFML-2.4.2)

file(COPY res/ DESTINATION Debug/res/)

target_link_libraries(${PROJECT_NAME} sfml-network sfml-graphics sfml-window sfml-system sfml-audio)

if (NOT UNIX)
	set_target_properties(${PROJECT_NAME} PROPERTIES
	    CXX_STANDARD 14
	    CXX_STANDARD_REQUIRED ON
	    CXX_EXTENSIONS OFF
	)
else()
	add_definitions(-std=c++14)
endif()
