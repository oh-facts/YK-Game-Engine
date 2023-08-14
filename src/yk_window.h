#ifndef YK_WINDOW_H
#define YK_WINDOW_H

#include <glad/glad.h>

#include <GLFW/glfw3.h>

#define WIDTH 720
#define HEIGHT 720
#define TITLE "yk"

typedef struct YK_Window
{
    GLFWwindow *win_ptr;
    int width;
    int height;

} YK_Window;

YK_Window yk_window_create();

#endif