#include "Game.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_render.h>

#include "Nodes/Node.h"
#include "Nodes/Camera.h"
#include "Nodes/Spaceship.h"
#include "Components/Editor.h"
#include "Components/VectorRenderer.h"

#include <format>

void Game::Run()
{
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

	window = SDL_CreateWindow("Space", 640, 480, NULL);

	if (!window)
	{
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create window: %s\n", SDL_GetError());
		return;
	}

	renderer = new Renderer(window);

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

	auto camera = std::make_shared<Camera>();
	camera->position = { -100.0f, -100.0f };
	sceneRoot->AddChild(camera);

	renderer->currentCamera = camera;
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
			else if (event.key.scancode == SDL_SCANCODE_F11)
			{
				bool isFullscreen = SDL_GetWindowFlags(window) & SDL_WINDOW_FULLSCREEN;
				SDL_SetWindowFullscreen(window, !isFullscreen);
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
	renderer->Clear(Color4::Black);

	sceneRoot->Draw(renderer);

	static auto fpsFont = renderer->GetCachedFont(FONT_DEBUG, 16.0f);
	renderer->RenderText(std::format("FPS {:.0f}", fpsSampler.Average()), Vector2::Zero, Vector2::Zero, Color4::White, fpsFont);

	renderer->Present();
}
