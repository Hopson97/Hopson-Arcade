
add_library(arcade 
    arcade/util/animation.cpp
    arcade/util/file_util.cpp
    arcade/util/maths.cpp
    arcade/util/toggle_key.cpp
    arcade/util/fps_counter.cpp
    arcade/input/keyboard.cpp
    arcade/resources/resource_holder.cpp
    arcade/state/state_base.cpp
    arcade/gui/button.cpp
    arcade/gui/textbox.cpp
    arcade/gui/widget.cpp
    arcade/gui/stack_menu.cpp
)

setup_target_compile(${PROJECT_NAME})