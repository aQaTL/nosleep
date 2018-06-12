#include <iostream>
#include <memory>

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

int main() {
	auto windowSize = std::make_pair(200, 80);
	auto window = InitWindow("nosleep", windowSize);

	auto glVersion = glGetString(GL_VERSION);
	printf("%s\n", glVersion);

	nk_context* ctx = nk_glfw3_init(window, NK_GLFW3_INSTALL_CALLBACKS);

	struct nk_font_atlas* atlas;
	nk_glfw3_font_stash_begin(&atlas);
	nk_glfw3_font_stash_end();

	nk_colorf bg = {
		r: 0.10f,
		g: 0.18f,
		b: 0.24f,
		a: 1.0f,
	};

	auto noSleep = std::make_unique<SleepPrevention>();

	auto label = [&noSleep]() {
		return noSleep->getSleepPreventionState() ?
			   "Sleep prevention is on" :
			   "Sleep prevention is off";
	};

	auto buttonLabel = [&noSleep]() {
		return noSleep->getSleepPreventionState() ? "Turn off" : "Turn on";
	};

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		nk_glfw3_new_frame();

		if (nk_begin(ctx, "nosleep", nk_rect(0, 0, windowSize.first, windowSize.second), 0)) {
			nk_layout_row_dynamic(ctx, 20, 1);
			nk_label(ctx, label(), NK_TEXT_ALIGN_CENTERED);

			nk_layout_row_dynamic(ctx, 30, 1);
			if (nk_button_label(ctx, buttonLabel())) {
				noSleep->cycleSleepPreventionState();
				printf("%s\n", label());
			}

			nk_end(ctx);
		}

		glfwGetWindowSize(window, &windowSize.first, &windowSize.second);
		glViewport(0, 0, windowSize.first, windowSize.second);
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(bg.r, bg.g, bg.b, bg.a);

		/* IMPORTANT: `nk_glfw_render` modifies some global OpenGL state
		 * with blending, scissor, face culling and depth test and defaults everything
		 * back into a default state. Make sure to either save and restore or
		 * reset your own state after drawing rendering the UI. */
		nk_glfw3_render(NK_ANTI_ALIASING_ON);
		glfwSwapBuffers(window);
	}

	nk_glfw3_shutdown();
	glfwTerminate();
}

