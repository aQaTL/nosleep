#pragma once

#include <cstdio>
#include <glad/glad.h>
#include <cstdlib>

#include <GLFW/glfw3.h>

static void errorCallback(int e, const char* d) {
	printf("Error %d: %s\n", e, d);
}

void window_focus_callback(GLFWwindow* window, int focused) {
	if (focused) {
		glfwSwapInterval(4);
	} else {
		glfwSwapInterval(30);
	}
}

static GLFWwindow* InitWindow(std::string title, std::pair<int, int> size) {
	if (!glfwInit()) {
		std::cerr << "Error initializing glfw" << std::endl;
		exit(-1);
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	/* GLFW */
	glfwSetErrorCallback(errorCallback);
	if (!glfwInit()) {
		fprintf(stdout, "[GFLW] failed to init!\n");
		exit(1);
	}

	GLFWwindow* window = glfwCreateWindow(size.first, size.second, title.c_str(), NULL, NULL);

	glfwMakeContextCurrent(window);
	glfwSwapInterval(2);
	glfwSetWindowFocusCallback(window, window_focus_callback);

	if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
		fprintf(stderr, "Failed to load GLAD\n");
		fflush(stderr);
	}


	return window;
}

