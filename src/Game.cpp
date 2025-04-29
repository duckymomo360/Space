#include "Game.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_render.h>

#include "Nodes/Node.h"
#include "Nodes/Spaceship.h"
#include "Components/Editor.h"
#include "Components/VectorRenderer.h"

void Game::Run()
{
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

	if (!SDL_CreateWindowAndRenderer("Space", 640, 480, 0, &window, &renderer))
	{
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create window and renderer: %s\n", SDL_GetError());
		return;
	}

	SDL_SetWindowFullscreen(window, true);

	SDL_SetRenderVSync(renderer, 1);

	SetupScene();

	while (!shouldExit)
	{
		frameTime = frameTimer.Elapsed();
		fpsSampler.Push(1.0 / frameTime);
		frameTimer.Reset();

		PollEvents();
		UpdateScene();
		RenderFrame();
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();
}

void Game::SetupScene()
{
	sceneRoot = std::make_shared<Node>();
	sceneRoot->name = "Root";

	sceneRoot->AddComponent<VectorRendererComponent>();
	sceneRoot->AddComponent<EditorComponent>();

	sceneRoot->AddChild(std::make_shared<Spaceship>());
}

void Game::PollEvents()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{

		case SDL_EVENT_QUIT:
			shouldExit = true;
			break;

		case SDL_EVENT_KEY_DOWN:
			if (event.key.scancode == SDL_SCANCODE_F3)
			{
				debug = !debug;
			}
			break;
		}
	}
}

void Game::UpdateScene()
{
	sceneRoot->UpdateTransformRecursive();

	sceneRoot->Update(frameTime);
}

void Game::RenderFrame()
{
	// Clear Screen
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	sceneRoot->Draw(renderer);

	textRenderer.DrawText(renderer, FONT_DEBUG, Vector2::Zero, 2.0f, {255, 255, 255}, "FPS %.f", fpsSampler.Average());

	// Present
	SDL_RenderPresent(renderer);
}
