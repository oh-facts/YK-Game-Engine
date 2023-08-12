#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <glad/glad.h>

#include <GLFW/glfw3.h>

namespace AE
{

    struct Window
    {
        GLFWwindow *win_ptr;
        int width = 960;
        int height = 540;

        Window();
    };

}

#endif