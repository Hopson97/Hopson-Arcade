
function(setup_target_compile target)
    #Set C++17
    target_compile_features(${target} PUBLIC cxx_std_17)
    set_target_properties(${target} PROPERTIES CXX_EXTENSIONS OFF)

    #Set flags
    if(MSVC)
        target_compile_options(${target} PRIVATE 
            /W4 /WX)
    else()
        target_compile_options(${target} PRIVATE 
            -Wall -Wextra -pedantic -Werror)		#Warning flags
    endif()
endfunction()