#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include "tigl.h"
#include "Scene.hpp"

GLFWwindow* window;
Scene* scene;

void init();

int main()
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

    init();

    scene = new Scene();
    scene->initBaseScene();

    while (!glfwWindowShouldClose(window))
    {
        scene->update();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}

void init()
{
    tigl::init();
    tigl::shader->enableTexture(true);

    //keyboard callback usefull for quick actions, ingame actions should use pull request instead
    glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            if (key == GLFW_KEY_ESCAPE)
                glfwSetWindowShouldClose(window, true);
        });
}