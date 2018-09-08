#include "App.hpp"

#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT

#define NK_IMPLEMENTATION
#define NK_GLFW_GL2_IMPLEMENTATION
#include <nuklear.h>
#include <nuklear_glfw_gl2.h>

#include <glad/glad.h>

static const char* getLabel(const SleepPrevention& noSleep);
static const char* getButtonLabel(const SleepPrevention& noSleep);

App::App(Window* window)
	: window(window), title(window->GetTitle().c_str())
{
	ctx = nk_glfw3_init(**window, NK_GLFW3_INSTALL_CALLBACKS);

	struct nk_font_atlas* atlas;
	nk_glfw3_font_stash_begin(&atlas);
	nk_glfw3_font_stash_end();

	nk_colorf bg = {0.10f, 0.18f, 0.24f, 1.0f};
	glClearColor(bg.r, bg.g, bg.b, bg.a);

	noSleep.setSleepPreventionState(true);
}

App::~App()
{
	nk_glfw3_shutdown();
}

void App::UpdateAndRender()
{
	nk_glfw3_new_frame();

	if (nk_begin(ctx, title,
				 nk_rect(0.0f, 0.0f, window->size[0], window->size[1]),
				 0)) {
		nk_layout_row_dynamic(ctx, 20, 1);
		nk_label(ctx, getLabel(noSleep), NK_TEXT_ALIGN_CENTERED);

		nk_layout_row_dynamic(ctx, 30, 1);
		if (nk_button_label(ctx, getButtonLabel(noSleep))) {
			noSleep.cycleSleepPreventionState();
		}

		nk_end(ctx);
	}

	glClear(GL_COLOR_BUFFER_BIT);

	/* IMPORTANT: `nk_glfw_render` modifies some global OpenGL state
	 * with blending, scissor, face culling and depth test and defaults everything
	 * back into a default state. Make sure to either save and restore or
	 * reset your own state after drawing rendering the UI. */
	nk_glfw3_render(NK_ANTI_ALIASING_ON);
	window->SwapBuffers();
}

static const char* getLabel(const SleepPrevention& noSleep)
{
	return noSleep.getSleepPreventionState() ?
		   "Sleep prevention is on" :
		   "Sleep prevention is off";
}

static const char* getButtonLabel(const SleepPrevention& noSleep)
{
	return noSleep.getSleepPreventionState() ? "Turn off" : "Turn on";
}