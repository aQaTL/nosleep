#pragma once

#include <glad/glad.h>

#include <windows.h>

#include <GLFW/glfw3.h>

static GLFWwindow* InitWindow(const char* title, std::pair<int, int> size)
{
	if (!glfwInit())
	{
		MessageBox(NULL, "Failed to initialize GLFW", "Error", MB_OK | MB_ICONERROR);
		exit(1);
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	GLFWwindow* window = glfwCreateWindow(size.first, size.second, title, NULL, NULL);

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
	{
		MessageBox(NULL, "Failed to load GLAD", "Error", MB_OK | MB_ICONERROR);
		exit(1);
	}

	return window;
}
