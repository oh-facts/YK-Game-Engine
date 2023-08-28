#ifndef YK_INPUT_H
#define YK_INPUT_H

#include <yk/math/yk_math_types.h>

b1 yk_input_is_key_held(u4 key);
b1 yk_input_is_key_tapped(u4 key);
b1 yk_input_is_key_released(u4 key);

f4 yk_input_get_mouse_scroll();
YK_Vec2f yk_input_get_mouse_pos();
YK_Vec2f yk_input_get_mouse_movement();



/*
https://www.glfw.org/docs/latest/group__keys.html
*/


#endif