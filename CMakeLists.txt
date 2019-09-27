cmake_minimum_required(VERSION 3.10)

#Set up project
project(hopson-arcade VERSION 1.0)

#Set executable
add_executable(${PROJECT_NAME}
    src/main.cpp
    # Source/Game.cpp
    # Source/SpaceInvaders/AnimationRenderer.cpp
    # Source/SpaceInvaders/StarryBackground.cpp
    # Source/SpaceInvaders/InvaderManager.cpp
    # Source/SpaceInvaders/World.cpp
    # Source/SpaceInvaders/Collidable.cpp
    # Source/SpaceInvaders/States/StateMainMenu.cpp
    # Source/SpaceInvaders/States/StateHighscores.cpp
    # Source/SpaceInvaders/States/StatePlaying.cpp
    # Source/SpaceInvaders/Entity/Shield.cpp
    # Source/SpaceInvaders/Entity/Invader.cpp
    # Source/SpaceInvaders/Entity/Player.cpp
    # Source/SpaceInvaders/Entity/Explosion.cpp
    # Source/SpaceInvaders/Entity/Projectile.cpp
    # Source/SpaceInvaders/Entity/UFO.cpp
    # Source/Framework/Util/FileUtil.cpp
    # Source/Framework/Util/FPSCounter.cpp
    # Source/Framework/Util/Maths.cpp
    # Source/Framework/Util/ToggleKey.cpp
    # Source/Framework/Util/Animation.cpp
    # Source/Framework/GUI/StackMenu.cpp
    # Source/Framework/GUI/Button.cpp
    # Source/Framework/GUI/Textbox.cpp
    # Source/Framework/GUI/Widget.cpp
    # Source/Framework/ResourceManager/ResourceHolder.cpp
    # Source/Framework/States/StateBase.cpp
)

add_subdirectory(src)

#Set C++17
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_EXTENSIONS OFF)

#Set flags
if(MSVC)
  	target_compile_options(${PROJECT_NAME} PRIVATE 
    	/W4 /WX)
else()
  	target_compile_options(${PROJECT_NAME} PRIVATE 
		-Wall -Wextra -pedantic -Werror)		#Warning flags
endif()

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
