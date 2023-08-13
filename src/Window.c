#include <Window.h>
#include <stdio.h>
#include <stdlib.h>

#define WIDTH 960
#define HEIGHT 540

void framebuffer_size_callback(GLFWwindow *window, int newWidth, int newHeight)
{
    Window *win = (Window *)glfwGetWindowUserPointer(window);
    if (win)
    {
        win->width = newWidth;
        win->height = newHeight;
        glViewport(0, 0, win->width, win->height);
    }
}

Window create_window()
{
    Window out;

    if (!glfwInit())
    {
        fprintf(stderr, "Failed to initialize GLFW\n");
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    out.win_ptr = glfwCreateWindow(WIDTH, HEIGHT, "ae", NULL, NULL);

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

    glViewport(0, 0, WIDTH, HEIGHT);
    glfwSetFramebufferSizeCallback(out.win_ptr, framebuffer_size_callback);

    return out;
}
