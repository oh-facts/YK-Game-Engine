#ifndef WINDOW_H
#define WINDOW_H

#include <glad/glad.h>

#include <GLFW/glfw3.h>

typedef struct Window
{
    GLFWwindow *win_ptr;
    int width;
    int height;
   
} Window;

 Window create_window();

#endif