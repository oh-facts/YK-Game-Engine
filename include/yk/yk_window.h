#ifndef YK_WINDOW_H
#define YK_WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <yk/math/yk_math_types.h>
#include <yk/yk_core_types.h>
#include <yk/yk_key_codes.h>



#define WIDTH 720
#define HEIGHT 720

#define WIN_TOP_LEFT_X 0
#define WIN_TOP_LEFT_Y 30


#define TITLE "yk"

/*
    A window
*/
typedef struct YK_Window
{
    GLFWwindow *win_ptr;
    int width;
    int height;

} YK_Window;

/*
    Initializes a window
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