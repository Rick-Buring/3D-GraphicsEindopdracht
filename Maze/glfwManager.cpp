#include "glfwManager.hpp"

GLFWwindow* Window;

void glfwManager_initGLF()
{
    if (!glfwInit())
        throw "Could not initialize glwf";

    Window = glfwCreateWindow(1280, 720, "hello World", NULL, NULL);
    if (!Window)
    {
        glfwTerminate();
        throw "Could not initialize glwf";
    }
    glfwMakeContextCurrent(Window);
}
