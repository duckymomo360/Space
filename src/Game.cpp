#include "Game.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_render.h>

#include "Nodes/Node.h"
#include "Nodes/Spaceship.h"

void Game::Run() {
	SDL_Init(SDL_INIT_VIDEO);

	if (!SDL_CreateWindowAndRenderer("Space", 640, 480, 0, &window, &renderer)) {
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create window and renderer: %s\n", SDL_GetError());
		return;
	}

	SDL_SetRenderVSync(renderer, 1);

	SetupScene();

	while (!shouldExit) {
		PollEvents();
		UpdateScene();
		RenderFrame();
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();
}

void Game::SetupScene() {
	sceneRoot = new Node("Root");

	sceneRoot->children.push_back(new Spaceship());
}

void Game::PollEvents() {
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_EVENT_QUIT) {
			shouldExit = true;
		}

		inputManager.ProcessEvent(event);
	}
}

void Game::UpdateScene() {
	sceneRoot->UpdateTransformRecursive();

	float time = SDL_GetPerformanceCounter();

	if (!lastUpdateTime.has_value()) {
		lastUpdateTime = time;
	}

	float delta = (time - lastUpdateTime.value()) / SDL_GetPerformanceFrequency();

	lastUpdateTime = time;

	sceneRoot->Update(delta);
}

void Game::RenderFrame() {
	float time = SDL_GetPerformanceCounter();

	if (!lastFrameTime.has_value()) {
		lastFrameTime = time;
	}

	float delta = (time - lastFrameTime.value()) / SDL_GetPerformanceFrequency();

	lastFrameTime = time;

	// Clear Screen
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	sceneRoot->Draw(renderer);

	if (debug) {
		textRenderer.DrawText(renderer, FONT_DEBUG, Vector2::Zero, 4.0f, {255, 255, 255}, "FPS %.1f", delta * 60.0f);
	}

	// Present
	SDL_RenderPresent(renderer);
}
