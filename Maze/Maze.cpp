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

Scene* scene;

void init();

int main()
{
    initGLF();
    init();

    scene = new Scene();
    scene->initBaseScene();

    while (!glfwWindowShouldClose(window))
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        static float lookX = -3, lookY = 4, lookZ = 0;

        ImGui::Begin("DebugWindow");
        ImGui::SliderFloat("lightDirx", &lookX, -1, 1);
        ImGui::SliderFloat("lightDiry", &lookY, -1, 1);
        ImGui::SliderFloat("lightDirz", &lookZ, -1, 1);
        ImGui::End();

        tigl::shader->setLightPosition(0, glm::vec3(lookX, lookY, lookZ));

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
    tigl::shader->setLightCount(1);
    tigl::shader->setLightDirectional(0, true);
    tigl::shader->setLightAmbient(0, glm::vec3(0.5f, 0.5f, 0.5f));
    tigl::shader->setLightDiffuse(0, glm::vec3(0.5f, 0.5f, 0.5f));
    tigl::shader->setLightSpecular(0, glm::vec3(1, 1, 1));
    tigl::shader->setShinyness(0);


    //keyboard callback usefull for quick actions, ingame actions should use pull request instead
    glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            if (key == GLFW_KEY_ESCAPE)
                glfwSetWindowShouldClose(window, true);
        });

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

}