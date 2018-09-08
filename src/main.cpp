#include "Window.hpp"
#include "SleepPrevention.hpp"
#include "App.hpp"

int main()
{
	Window window("nosleep", 200, 80);
	App app(&window);

	window.windowSizeCallback = [&](Window* window)
	{
		app.UpdateAndRender();
	};

	while (!window.ShouldClose()) {
		window.WaitEvents();
		app.UpdateAndRender();
	}

	window.Terminate();
}
