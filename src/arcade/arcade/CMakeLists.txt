
add_library(arcade
    util/animation.cpp
    util/file_util.cpp
    util/toggle_key.cpp
    util/fps_counter.cpp
    input/keyboard.cpp
    game.cpp
    resources/resource_holder.cpp
    state/state_base.cpp
    gui/button.cpp
    gui/textbox.cpp
    gui/widget.cpp
    gui/stack_menu.cpp
)

setup_target_compile(arcade)