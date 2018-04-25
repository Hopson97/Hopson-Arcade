cmake_minimum_required(VERSION 3.1)

project(HopsonArcade)
set (CMAKE_CXX_STANDARD 14)

#Add files
file(GLOB_RECURSE SRC 
    "Source/*.cpp"
    "Source/*.h"
)

file(GLOB_RECURSE SRC_ARCADE 
    "Source/Arcade/*.cpp"
    "Source/Arcade/*.h"
)

file(GLOB_RECURSE SRC_FRAMEWORK
    "Source/Framework/GUI/*.cpp"
    "Source/Framework/GUI/*.h"
    "Source/Framework/ResourceManager/*.cpp"
    "Source/Framework/ResourceManager/*.h"
    "Source/Framework/States/*.cpp"
    "Source/Framework/States/*.h"
    "Source/Framework/Util/*.cpp"
    "Source/Framework/Util/*.h"
)

file(GLOB_RECURSE SRC_SPACE_INVADERS 
    "Source/SpaceInvaders/*.cpp"
    "Source/SpaceInvaders/*.h"
    "Source/SpaceInvaders/Entity/*.cpp"
    "Source/SpaceInvaders/Entity/*.h"
    "Source/SpaceInvaders/States/*.cpp"
    "Source/SpaceInvaders/States/*.h"
)

#Define the executable
add_executable(
    ${PROJECT_NAME} 
    ${SRC} 
)

#Define the filters for IDEs
source_group("Arcade" FILES ${SRC_ARCADE})
source_group("Framework" FILES ${SRC_FRAMEWORK})
source_group("SpaceInvaders" FILES ${SRC_SPACE_INVADERS})

#Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED COMPONENTS network audio graphics window system)

include_directories(${SFML_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})

#Copy resources
file(COPY ${CMAKE_SOURCE_DIR}/res DESTINATION ${CMAKE_BINARY_DIR})

