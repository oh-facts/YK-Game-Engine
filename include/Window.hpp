#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <glad/glad.h>

#include <GLFW/glfw3.h>

namespace AE
{

    struct Window
    {
        GLFWwindow *win_ptr;
        int width = 800;
        int height = 600;

        Window();
    };

}

#endif