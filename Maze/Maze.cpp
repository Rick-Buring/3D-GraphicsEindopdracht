#ifdef TEST
#define CONFIG_CATCH_MAIN
#include "catch.hpp"

int main() {
    return 0;
}
#else
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include "tigl.h"
#include "Scene.hpp"
#include "glfwManager.hpp"
#include "LightManager.hpp"

Scene* scene;

void init();

int main()
{
    initGLF();
    init();

    scene = new Scene();

    while (!glfwWindowShouldClose(window))
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        scene->update();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();

    return 0;
}


void init()
{
    tigl::init();

    tigl::shader->enableLighting(true);

    //keyboard callback usefull for quick actions, ingame actions should use pull request instead
    glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            if (key == GLFW_KEY_ESCAPE) {
                //quit application
                glfwSetWindowShouldClose(window, true);
            }
            if (key == GLFW_KEY_TAB && action == GLFW_RELEASE) {
                //togle mouse state
                int newMouseState = glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED ? GLFW_CURSOR_NORMAL: GLFW_CURSOR_DISABLED;
                glfwSetInputMode(window, GLFW_CURSOR, newMouseState);
            }
        });

    //im gui initilization
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

}

#endif