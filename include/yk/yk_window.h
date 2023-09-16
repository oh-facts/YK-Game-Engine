#ifndef YK_WINDOW_H
#define YK_WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <yk/math/yk_math_types.h>
#include <yk/yk_core_types.h>
#include <yk/yk_key_codes.h>



#define WIDTH 720
#define HEIGHT 720

#define WIN_POSX 0
#define WIN_POSY 30


#define TITLE "yk"

typedef struct YK_Window
{
    GLFWwindow *win_ptr;
    int width;
    int height;

} YK_Window;

void yk_window_innit(YK_Window *out);
void yk_window_run(YK_Window *out);
void yk_window_destroy(YK_Window *out);
void yk_window_resize(YK_Window *win, int x, int y);
void yk_window_set_vsync(YK_Window *win, b1 flag);
void yk_window_set_pos(YK_Window *win, int x, int y);

/*
true to disable
false to enable
*/
void yk_window_disable_cursor(YK_Window *win, b1 flag);

b1 yk_window_is_running(YK_Window *win);

typedef struct YK_Key_states
{
    b1 current[NUM_KEYS];
    b1 before[NUM_KEYS];
} YK_Key_states;

extern YK_Key_states yk_key_states;
extern YK_Vec2f yk_input_mouse_pos;
extern YK_Vec2f yk_input_mouse_pos_old;
extern YK_Vec2f yk_input_mouse_pos_mv;
extern f4 yk_input_mouse_scroll;
extern i4 yk_last_key;

#endif