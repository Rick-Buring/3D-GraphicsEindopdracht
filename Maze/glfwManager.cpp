#include "glfwManager.hpp"

GLFWwindow* window;

void initGLF()
{
    if (!glfwInit())
        throw "Could not initialize glwf";

    window = glfwCreateWindow(1280, 720, "hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        throw "Could not initialize glwf";
    }
    glfwMakeContextCurrent(window);
}
