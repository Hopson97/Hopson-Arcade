cmake_minimum_required(VERSION 3.10)

include(cmake/CompileFeatures.cmake)

project(hopson-arcade VERSION 2.0
                  DESCRIPTION "Hopson Arcade: Selection of simple arcade-y games"
                  LANGUAGES CXX)

#Set executable
add_executable(${PROJECT_NAME}
    src/main.cpp
    src/space_invaders/world.cpp
    src/space_invaders/collidable.cpp
    src/space_invaders/entity/projectile.cpp
    src/space_invaders/entity/shield.cpp
    src/space_invaders/entity/invader.cpp
    src/space_invaders/entity/player.cpp
    src/space_invaders/entity/explosion.cpp
    src/space_invaders/entity/ufo.cpp
    src/space_invaders/invader_manager.cpp
    src/space_invaders/states/state_main_menu.cpp
    src/space_invaders/states/state_highscores.cpp
    src/space_invaders/states/state_playing.cpp
    src/space_invaders/animation_renderer.cpp
    src/space_invaders/starry_background.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE src/arcade)

setup_target_compile(${PROJECT_NAME})


#Subdirs
add_subdirectory(src/arcade/arcade/)

#Set module path
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

#Find libraries
find_package(Threads)
find_package(SFML REQUIRED audio network graphics window system)

#Finally
target_link_libraries(${PROJECT_NAME} 
    arcade
    Threads::Threads 
    ${SFML_LIBRARIES} 
    ${SFML_DEPENDENCIES}
)
