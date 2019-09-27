cmake_minimum_required(VERSION 3.10)

include(cmake/CompileFeatures.cmake)

#Set up project
project(hopson-arcade VERSION 1.0)

#Set executable
add_executable(${PROJECT_NAME}
    src/main.cpp
    src/game.cpp
)

setup_target_compile(${PROJECT_NAME})

add_subdirectory(src)

#Set module path
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

#Find libraries
find_package(Threads)
find_package(SFML REQUIRED audio network graphics window system)

#Finally
target_link_libraries(${PROJECT_NAME} 
    Threads::Threads 
    ${SFML_LIBRARIES} 
    ${SFML_DEPENDENCIES}
)
