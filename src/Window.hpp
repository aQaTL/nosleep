#pragma once

#include <glfw/glfw3.h>
#include <string>
#include <functional>
#include "Primitives.hpp"

enum KeyState
{
	Released,
	Pressed,
	Repeat
};

class Window
{
public:
	typedef std::function<void(Window* window, i32 key, i32 scanCode, KeyState action,
							   i32 mods)> keyCallbackFun;
private:
	std::string title;

	std::unordered_map<i32, keyCallbackFun> keyCallbacks;

	friend void keyCallback(GLFWwindow* ptr, i32 key, i32 scanCode, i32 action, i32 mods);
public:
	GLFWwindow* ptr;

	i32 size[2];
	f32 cursorPos[2];
	f32 scroll[2];

	KeyState keys[GLFW_KEY_LAST];
	KeyState mouseButtons[GLFW_MOUSE_BUTTON_LAST];

	Window(const std::string& title, i32 width, i32 height,
		   bool vsync = true, bool fullscreen = false);
	~Window();

	std::function<void(Window*)> windowSizeCallback;
	std::function<void(Window*)> cursorPosCallback;
	std::function<void(Window*)> scrollCallback;

	inline void SwapBuffers()
	{ glfwSwapBuffers(ptr); }

	inline i32 ShouldClose()
	{ return glfwWindowShouldClose(ptr); }

	inline void Terminate()
	{ glfwTerminate(); }

	void PoolEvents();
	void WaitEvents();

	GLFWwindow* operator*()
	{
		return ptr;
	}

	void AddKeyCallback(i32 key, keyCallbackFun callback);

	const std::string& GetTitle() const;
};


