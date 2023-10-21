#ifndef YK_WINDOW_H
#define YK_WINDOW_H

#include <yk/math/yk_math_types.h>
#include <yk/yk_core_types.h>
#include <yk/yk_key_codes.h>



#define WIDTH 720
#define HEIGHT 720

#define WIN_TOP_LEFT_X 0
#define WIN_TOP_LEFT_Y 30


#define TITLE "yk"

/*
    Forward declaration
*/
typedef struct YK_Window YK_Window;

/*
    Create a widnow handle
*/
YK_Window* yk_window_create();

/*
    Initializes a window. Don't use this function for now. Use create window.
*/

void yk_window_innit(YK_Window *out);

/*
    Must be called every frame for windowing and input to run correctly
*/
void yk_window_run(YK_Window *out);

/*
    Destroys window
*/
void yk_window_destroy(YK_Window *out);

/*
    Resizes window
*/
void yk_window_resize(YK_Window *win, int x, int y);

/*
    Set vsync.
*/
void yk_window_set_vsync(YK_Window *win, b1 flag);

/*
    Sets window position. You need to account for window titlebar heigh (30 units)
*/
void yk_window_set_pos(YK_Window *win, int x, int y);

/*
true to disable
false to enable
*/
void yk_window_disable_cursor(YK_Window *win, b1 flag);

/*
    returns true if window is active
*/
b1 yk_window_is_running(YK_Window *win);

/*
    returns window size
*/
v2i yk_window_size(YK_Window* win);

/*
    returns window aspect ratio
*/
f4 yk_window_aspect_ratio(YK_Window *win);

/*
    returns glfwgettime
*/
f4 yk_get_time();

typedef struct YK_Key_states
{
    b1 current[NUM_KEYS];
    b1 before[NUM_KEYS];
} YK_Key_states;

extern YK_Key_states yk_key_states;
extern v2f yk_input_mouse_pos;
extern v2f yk_input_mouse_pos_old;
extern v2f yk_input_mouse_pos_mv;
extern f4 yk_input_mouse_scroll;
extern i4 yk_last_key;

#endif