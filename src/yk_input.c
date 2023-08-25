#include <yk/yk_input.h>

YK_Key_states yk_key_states;
YK_Vec2f yk_input_mouse_position;
f4 yk_input_mouse_scroll;

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