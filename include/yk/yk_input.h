#ifndef YK_INPUT_H
#define YK_INPUT_H

#include <yk/math/yk_math_types.h>

/*
  Returns true as long as key is held down.
  Meant for continuous actions, like movement
*/
b1 yk_input_is_key_held(u4 key);

/*
  Returns true during the first frame the key is held down.
  Meant for trigger actions, like jump
*/
b1 yk_input_is_key_tapped(u4 key);

/*
  Returns true during the first frame the key is released.
  Simply exists.
*/
b1 yk_input_is_key_released(u4 key);

/*
  Returns +1 or -1 (scroll up, scroll down)
*/
f4 yk_input_get_mouse_scroll();

/*
  Simply exists for now.
*/
v2f yk_input_get_mouse_pos();

/*
  Returns a 2d vector pointing in the direction
  in which the mouse moves, with center (of the screen)
   as origin.
*/
v2f yk_input_get_mouse_movement();

#endif