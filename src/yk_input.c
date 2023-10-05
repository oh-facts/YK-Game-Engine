#include <yk/yk_input.h>
#include <yk/yk_window.h>
#include <stdio.h>
#include <yk/math/yk_math.h>

b1 yk_input_is_key_held(u4 key)
{
    return yk_key_states.current[key];
}
b1 yk_input_is_key_tapped(u4 key)
{
    return yk_key_states.current[key] && !yk_key_states.before[key];
}
b1 yk_input_is_key_released(u4 key)
{
    return !yk_key_states.current[key] && yk_key_states.before[key];
}

f4 yk_input_get_mouse_scroll()
{
    return yk_input_mouse_scroll;
}
YK_Vec2f yk_input_get_mouse_pos()
{
    return yk_input_mouse_pos;
}
YK_Vec2f yk_input_get_mouse_movement()
{
    return yk_math_vec2f_sub(&yk_input_mouse_pos_old, &yk_input_mouse_pos);
}