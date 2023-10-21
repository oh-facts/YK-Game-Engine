#include <yk/yk_window.h>
#include <stdio.h>
#include <stdlib.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <yk/yk_input.h>
#include <yk/math/yk_math.h>

/*
    A window
*/
struct YK_Window
{
    GLFWwindow *win_ptr;
    int width;
    int height;
};

/*
  Stores the last key pressed. Read only. I will kill
  you if you set it to something.
*/
i4 yk_last_key;

YK_Key_states yk_key_states;

/*
  Stores cursor position. Set internally. Treat as read-only.
  Don't make me make getters so you don't accidentally set it to
  something. Don't tell me you have skill issue
*/
v2f yk_input_mouse_pos;

/*

*/
v2f yk_input_mouse_pos_old;

v2f yk_input_mouse_pos_mv;

/*
  Stores mouse scroll. Set internally. Treat as read-only
*/
f4 yk_input_mouse_scroll;

void _keys_innit()
{

    for (int i = 0; i < YK_KEY_LAST; i++)
    {
        yk_key_states.before[i] = 0;
        yk_key_states.current[i] = 0;
    }
    yk_last_key = YK_KEY_UNKNOWN;
    yk_input_mouse_scroll = 0;
    yk_input_mouse_pos.x = WIDTH / 2;
    yk_input_mouse_pos.y = HEIGHT / 2;
    yk_input_mouse_pos_old.x = WIDTH / 2;
    yk_input_mouse_pos_old.y = HEIGHT / 2;
}

void framebuffer_size_callback(GLFWwindow *window, int newWidth, int newHeight)
{
    YK_Window *win = (YK_Window *)glfwGetWindowUserPointer(window);
    if (win)
    {
        win->width = newWidth;
        win->height = newHeight;
        glViewport(0, 0, win->width, win->height);
    }
}

void mouse_callback(GLFWwindow *window, double xposIn, double yposIn)
{
    yk_input_mouse_pos.x = (float)xposIn;
    yk_input_mouse_pos.y = (float)yposIn;
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
    yk_input_mouse_scroll = (float)yoffset;
    // printf("%f",yk_input_mouse_scroll);
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (key >= 0 && key <= GLFW_KEY_LAST)
    {

        // printf("%d %d \n", yk_key_states.before[key], yk_key_states.current[key]);
        if (action == GLFW_PRESS)
        {
            yk_key_states.current[key] = true;
            // yk_last_key = key;
        }

        else if (action == GLFW_RELEASE)
        {
            // yk_key_states.before[key] = true;
            yk_key_states.current[key] = false;
        }
        yk_last_key = key;
        // printf("%d %d \n", yk_key_states.before[key], yk_key_states.current[key]);
    }
}

void yk_window_innit(YK_Window *out)
{

    if (!glfwInit())
    {
        fprintf(stderr, "Failed to initialize GLFW\n");
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    out->win_ptr = glfwCreateWindow(WIDTH, HEIGHT, TITLE, NULL, NULL);
    out->width = WIDTH;
    out->height = HEIGHT;
    glfwSetWindowPos(out->win_ptr, WIN_TOP_LEFT_X, WIN_TOP_LEFT_Y);

    if (out->win_ptr == NULL)
    {
        fprintf(stderr, "Failed to create GLFW window\n");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(out->win_ptr);
    glfwSetWindowUserPointer(out->win_ptr, out);
    glfwSetCursorPos(out->win_ptr, WIDTH / 2, HEIGHT / 2);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        fprintf(stderr, "Failed to initialize GLAD\n");
        glfwDestroyWindow(out->win_ptr);
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, WIDTH, HEIGHT);

    glfwSetFramebufferSizeCallback(out->win_ptr, framebuffer_size_callback);
    glfwSetCursorPosCallback(out->win_ptr, mouse_callback);
    glfwSetScrollCallback(out->win_ptr, scroll_callback);
    glfwSetKeyCallback(out->win_ptr, key_callback);

    if (glfwRawMouseMotionSupported())
    {
        glfwSetInputMode(out->win_ptr, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
    }
    else
    {
        printf("Raw Input not supported");
    }
    _keys_innit();
}

b1 full_screen_toggle = true;

void yk_window_run(YK_Window *out)
{
    if (yk_input_is_key_tapped(YK_KEY_ESCAPE))
    {
        glfwSetWindowShouldClose(out->win_ptr, true);
    }

    if (yk_input_is_key_held(YK_KEY_LEFT_ALT) && yk_input_is_key_tapped(YK_KEY_ENTER))
    {
        if (full_screen_toggle)
        {
            full_screen_toggle = false;
            yk_window_set_pos(out, WIN_TOP_LEFT_X, WIN_TOP_LEFT_Y);
            yk_window_resize(out, 1920, 1080);
        }
        else
        {
            full_screen_toggle = true;
            yk_window_resize(out, WIDTH, HEIGHT);
        }
    }

    yk_input_mouse_scroll = 0;

    // glfwSetCursorPos(out->win_ptr, out->width / 2, out->height / 2);

    for (int i = 0; i < YK_KEY_LAST; i++)
    {
        yk_key_states.before[i] = yk_key_states.current[i];
    }

    // yk_input_mouse_pos_mv = yk_math_vec2f_sub(&yk_input_mouse_pos, &yk_input_mouse_pos_old);
    yk_input_mouse_pos_old.x = yk_input_mouse_pos.x;
    yk_input_mouse_pos_old.y = yk_input_mouse_pos.y;

    glfwSwapBuffers(out->win_ptr);
    glfwPollEvents();

    // printf("%f\n",yk_input_mouse_position.x);
}
void yk_window_destroy(YK_Window *out)
{
    glfwDestroyWindow(out->win_ptr);
    free(out);
    glfwTerminate();
}

void yk_window_resize(YK_Window *win, int x, int y)
{
    glfwSetWindowSize(win->win_ptr, x, y);
}

b1 yk_window_is_running(YK_Window *win)
{
    return !glfwWindowShouldClose(win->win_ptr);
}

void yk_window_set_vsync(YK_Window *win, b1 flag)
{
    glfwMakeContextCurrent(win->win_ptr);
    glfwSwapInterval(flag);
}

void yk_window_set_pos(YK_Window *win, int x, int y)
{
    glfwSetWindowPos(win->win_ptr, x, y);
}

void yk_window_disable_cursor(YK_Window *win, b1 flag)
{
    if (flag)
    {
        glfwSetInputMode(win->win_ptr, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        return;
    }
    glfwSetInputMode(win->win_ptr, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

YK_Window *yk_window_create()
{
    YK_Window *out = malloc(sizeof(YK_Window));
    yk_window_innit(out);
    return out;
}

v2i yk_window_size(YK_Window *win)
{
    return (v2i){win->width, win->height};
}

f4 yk_window_aspect_ratio(YK_Window *win)
{
    return (f4)win->width / win->height;
}

/*
    returns glfwgettime
*/
f4 yk_get_time()
{
    return glfwGetTime();
}