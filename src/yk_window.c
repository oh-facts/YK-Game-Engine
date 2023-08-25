#include <yk/yk_window.h>
#include <stdio.h>
#include <stdlib.h>
#include <yk/yk_input.h>

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
    yk_input_mouse_position.x = (float)xposIn;
    yk_input_mouse_position.y = (float)yposIn;
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
    yk_input_mouse_scroll = (float)yoffset;
    //printf("%f",yk_input_mouse_scroll);
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (key >= 0 && key <= GLFW_KEY_LAST)
    {
        if (action == GLFW_PRESS)
        {
            yk_key_states.current[key] = true;
        }
        else if (action == GLFW_RELEASE)
        {
            yk_key_states.current[key] = false;
        }

        if (action == GLFW_PRESS || action == GLFW_RELEASE)
        {
            yk_key_states.before[key] = yk_key_states.current[key];
        }
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
    glfwSetWindowPos(out->win_ptr, 1200, 40);

    if (out->win_ptr == NULL)
    {
        fprintf(stderr, "Failed to create GLFW window\n");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(out->win_ptr);
    glfwSetWindowUserPointer(out->win_ptr, out);

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
}
