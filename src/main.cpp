#include <glfw/glfw3.h>

#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_IMPLEMENTATION
#define NK_GLFW_GL2_IMPLEMENTATION

#include "nuklear.h"
#include "nuklear_glfw_gl2.h"

#include "WindowUtils.hpp"
#include "SleepPrevention.hpp"

const char* getButtonLabel(const SleepPrevention& noSleep);
const char* getLabel(const SleepPrevention& noSleep);

struct AppState
{
	GLFWwindow* window;
	std::pair<int, int> windowSize;

	nk_context* ctx;

	SleepPrevention noSleep;
};

void init();
void updateAndRender();

AppState* state;

int main()
{
	state = new AppState();
	init();

	while (!glfwWindowShouldClose(state->window))
	{
		glfwWaitEvents();
		updateAndRender();
	}

	nk_glfw3_shutdown();
	glfwTerminate();
	delete state;
}

void init()
{
	state->noSleep.setSleepPreventionState(true);

	state->windowSize = std::make_pair(200, 80);
	state->window = InitWindow("nosleep", state->windowSize);

	glfwSetWindowRefreshCallback(state->window, [](GLFWwindow* window) -> void
	{
		updateAndRender();
	});
	glfwSetFramebufferSizeCallback(
		state->window,
		[](GLFWwindow* window, int width, int height) -> void
		{
			state->windowSize.first = width;
			state->windowSize.second = height;
			glViewport(0, 0, width, height);
		});

	state->ctx = nk_glfw3_init(state->window, NK_GLFW3_INSTALL_CALLBACKS);

	struct nk_font_atlas* atlas;
	nk_glfw3_font_stash_begin(&atlas);
	nk_glfw3_font_stash_end();

	nk_colorf bg = {0.10f, 0.18f, 0.24f, 1.0f};
	glClearColor(bg.r, bg.g, bg.b, bg.a);
}

void updateAndRender()
{
	nk_glfw3_new_frame();

	if (nk_begin(state->ctx, "nosleep",
				 nk_rect(0.0f, 0.0f, state->windowSize.first, state->windowSize.second),
				 0))
	{
		nk_layout_row_dynamic(state->ctx, 20, 1);
		nk_label(state->ctx, getLabel(state->noSleep), NK_TEXT_ALIGN_CENTERED);

		nk_layout_row_dynamic(state->ctx, 30, 1);
		if (nk_button_label(state->ctx, getButtonLabel(state->noSleep)))
		{
			state->noSleep.cycleSleepPreventionState();
		}

		nk_end(state->ctx);
	}

	glClear(GL_COLOR_BUFFER_BIT);

	/* IMPORTANT: `nk_glfw_render` modifies some global OpenGL state
	 * with blending, scissor, face culling and depth test and defaults everything
	 * back into a default state. Make sure to either save and restore or
	 * reset your own state after drawing rendering the UI. */
	nk_glfw3_render(NK_ANTI_ALIASING_ON);
	glfwSwapBuffers(state->window);
}

const char* getLabel(const SleepPrevention& noSleep)
{
	return noSleep.getSleepPreventionState() ?
		   "Sleep prevention is on" :
		   "Sleep prevention is off";
}

const char* getButtonLabel(const SleepPrevention& noSleep)
{
	return noSleep.getSleepPreventionState() ? "Turn off" : "Turn on";
}
