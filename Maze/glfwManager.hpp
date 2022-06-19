#pragma once

#include <GLFW/glfw3.h>

/// <summary>
/// creates a glfw window or throws an exception
/// </summary>
void glfwManager_initGLF();

/// <summary>
/// pointer to window created by initGLF
/// </summary>
extern GLFWwindow* Window;

