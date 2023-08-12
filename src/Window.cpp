#include <Window.hpp>
#include <iostream>

namespace AE
{
    void framebuffer_size_callback(GLFWwindow *window, int newWidth, int newHeight)
    {
        Window *win = static_cast<Window *>(glfwGetWindowUserPointer(window));
        if (win)
        {
            win->width = newWidth;
            win->height = newHeight;
            glViewport(0, 0, win->width, win->height);
        }
    }

    Window::Window()
    {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        win_ptr = glfwCreateWindow(width, height, "ae", NULL, NULL);
        if (win_ptr == NULL)
        {
            std::cout << "Failed to create GLFW window" << std::endl;
            return;
        }
        glfwSetWindowUserPointer(win_ptr, this);
        glfwMakeContextCurrent(win_ptr);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
            return;
        }

        glViewport(0, 0, width, height);
        glfwSetFramebufferSizeCallback(win_ptr, framebuffer_size_callback);
    }

}