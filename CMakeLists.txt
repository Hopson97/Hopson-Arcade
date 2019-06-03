cmake_minimum_required(VERSION 3.1)

project(hopson-arcade)
set (CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML REQUIRED graphics window system)

#Add files
set(SOURCES 
    Source/Main.cpp
    Source/Game.cpp
    Source/SpaceInvaders/AnimationRenderer.cpp
    Source/SpaceInvaders/StarryBackground.cpp
    Source/SpaceInvaders/InvaderManager.cpp
    Source/SpaceInvaders/World.cpp
    Source/SpaceInvaders/Collidable.cpp
    Source/SpaceInvaders/States/StateMainMenu.cpp
    Source/SpaceInvaders/States/StateHighscores.cpp
    Source/SpaceInvaders/States/StatePlaying.cpp
    Source/SpaceInvaders/Entity/Shield.cpp
    Source/SpaceInvaders/Entity/Invader.cpp
    Source/SpaceInvaders/Entity/Player.cpp
    Source/SpaceInvaders/Entity/Explosion.cpp
    Source/SpaceInvaders/Entity/Projectile.cpp
    Source/SpaceInvaders/Entity/UFO.cpp
    Source/Framework/Util/FileUtil.cpp
    Source/Framework/Util/FPSCounter.cpp
    Source/Framework/Util/Maths.cpp
    Source/Framework/Util/ToggleKey.cpp
    Source/Framework/Util/Animation.cpp
    Source/Framework/GUI/StackMenu.cpp
    Source/Framework/GUI/Button.cpp
    Source/Framework/GUI/Textbox.cpp
    Source/Framework/GUI/Widget.cpp
    Source/Framework/ResourceManager/ResourceHolder.cpp
    Source/Framework/States/StateBase.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

#Find the SFML package
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML REQUIRED audio network graphics window system)
find_package(Threads)
target_link_libraries(${PROJECT_NAME} Threads::Threads ${SFML_LIBRARIES} ${SFML_DEPENDENCIES} ${ADDITIONAL_LINK_FLAGS})
find_package(Threads)
target_link_libraries(${PROJECT_NAME} Threads::Threads ${SFML_LIBRARIES} ${SFML_DEPENDENCIES} ${ADDITIONAL_LINK_FLAGS})