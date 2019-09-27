cmake_minimum_required(VERSION 3.10)

include(cmake/CompileFeatures.cmake)

#Set up project
project(hopson-arcade VERSION 1.0)

#Set executable
add_executable(${PROJECT_NAME}
    src/main.cpp
    src/arcade/util/animation.cpp
    src/arcade/util/file_util.cpp
    src/arcade/util/toggle_key.cpp
    src/arcade/util/fps_counter.cpp
    src/arcade/input/keyboard.cpp
    src/arcade/game.cpp
    src/arcade/resources/resource_holder.cpp
    src/arcade/state/state_base.cpp
    src/arcade/gui/button.cpp
    src/arcade/gui/textbox.cpp
    src/arcade/gui/widget.cpp
    src/arcade/gui/stack_menu.cpp
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

setup_target_compile(${PROJECT_NAME})

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
