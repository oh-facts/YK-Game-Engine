#include <GLFW/glfw3.h>
auto main() -> int
{

    if (!glfwInit()) {
        return -1;
    }

 
    GLFWwindow* window = glfwCreateWindow(800, 600, "GLFW Sample Code", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return -1;
    }


    glfwMakeContextCurrent(window);

    while (!glfwWindowShouldClose(window)) {

        // Swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}