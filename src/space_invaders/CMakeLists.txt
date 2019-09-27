
add_library(space_invaders
    animation_renderer.cpp
    collidable.cpp
    invader_manager.cpp
    starry_background.cpp
    world.cpp
    entity/explosion.cpp
    entity/invader.cpp
    entity/player.cpp
    entity/projectile.cpp
    entity/shield.cpp
    entity/ufo.cpp
    states/state_highscores.cpp
    states/state_main_menu.cpp
    states/state_playing.cpp
)

target_include_directories(space_invaders PRIVATE ../arcade)