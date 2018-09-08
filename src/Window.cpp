#include <utility>

#include "Window.hpp"

#include <glad/glad.h>

void windowSizeUpdate(GLFWwindow* ptr, i32 width, i32 height)
{
	auto window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(ptr));
	window->size[0] = width;
	window->size[1] = height;
	glViewport(0, 0, width, height);
	if (window->windowSizeCallback != nullptr) {
		window->windowSizeCallback(window);
	}
}

void keyCallback(GLFWwindow* ptr, i32 key, i32 scanCode, i32 action, i32 mods)
{
	auto window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(ptr));
	window->keys[key] = KeyState(action);

	auto callback = window->keyCallbacks[key];
	if (callback != nullptr) {
		callback(window, key, scanCode, KeyState(action), mods);
	}
}

void cursorPosUpdate(GLFWwindow* ptr, f64 xpos, f64 ypos)
{
	auto window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(ptr));
	window->cursorPos[0] = static_cast<float>(xpos);
	window->cursorPos[1] = static_cast<float>(ypos);
	if (window->cursorPosCallback != nullptr) {
		window->cursorPosCallback(window);
	}
}

void scrollUpdate(GLFWwindow* ptr, f64 xoffset, f64 yoffset)
{
	auto window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(ptr));
	window->scroll[0] = static_cast<float>(xoffset);
	window->scroll[1] = static_cast<float>(yoffset);
	if (window->scrollCallback != nullptr) {
		window->scrollCallback(window);
	}
}

void mouseButtonCallback(GLFWwindow* ptr, i32 button, i32 action, i32 mods)
{
	auto window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(ptr));
	window->mouseButtons[button] = KeyState(action);
}

Window::Window(const std::string& title, i32 width, i32 height, bool vsync, bool fullscreen)
	: title(title), size{width, height}, cursorPos{0.0f, 0.0f}, scroll{0.0f, 0.0f},
	  keys{Released}, mouseButtons{Released}
{
	if (!glfwInit()) {
		std::fprintf(stderr, "Failed to init GLFW\n");
		std::fflush(stderr);
		std::exit(1);
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

	if (!(ptr = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr))) {
		std::fprintf(stderr, "Failed to create window\n");
		std::fflush(stderr);
		std::exit(1);
	}
	glfwMakeContextCurrent(ptr);

	glfwSetWindowUserPointer(ptr, this);
	glfwSwapInterval(vsync ? 1 : 0);

	glfwSetWindowSizeCallback(ptr, windowSizeUpdate);
	glfwSetKeyCallback(ptr, keyCallback);
	glfwSetCursorPosCallback(ptr, cursorPosUpdate);
	glfwSetScrollCallback(ptr, scrollUpdate);
	glfwSetMouseButtonCallback(ptr, mouseButtonCallback);

	f64 xpos = 0.0, ypos = 0.0;
	glfwGetCursorPos(ptr, &xpos, &ypos);
	cursorPos[0] = xpos;
	cursorPos[1] = ypos;

	if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
		std::fprintf(stderr, "Failed to load GLAD\n");
		std::fflush(stderr);
		std::exit(1);
	}

	glViewport(0, 0, width, height);
}

Window::~Window()
{
}

void Window::PoolEvents()
{
	glfwPollEvents();
}

void Window::WaitEvents()
{
	glfwWaitEvents();
}

void Window::AddKeyCallback(i32 key, Window::keyCallbackFun callback)
{
	keyCallbacks[key] = std::move(callback);
}

const std::string& Window::GetTitle() const
{
	return title;
}
