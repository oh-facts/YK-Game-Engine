#include <yk_window.h>
#include <stdio.h>
#include <stdlib.h>

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

YK_Window yk_window_create()
{
    YK_Window out;

    if (!glfwInit())
    {
        fprintf(stderr, "Failed to initialize GLFW\n");
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);    
    out.win_ptr = glfwCreateWindow(WIDTH, HEIGHT, TITLE, NULL, NULL);
    glfwSetWindowPos(out.win_ptr, 1200, 40);

    if (out.win_ptr == NULL)
    {
        fprintf(stderr, "Failed to create GLFW window\n");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(out.win_ptr);
    glfwSetWindowUserPointer(out.win_ptr, &out);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        fprintf(stderr, "Failed to initialize GLAD\n");
        glfwDestroyWindow(out.win_ptr);
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    
    glEnable(GL_DEPTH_TEST);  
    glViewport(0, 0, WIDTH, HEIGHT);
    glfwSetFramebufferSizeCallback(out.win_ptr, framebuffer_size_callback);

    return out;
}
