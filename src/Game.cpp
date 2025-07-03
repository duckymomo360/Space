#include "Game.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_render.h>

#include "Nodes/SceneRoot.h"
#include "Nodes/Camera.h"
#include "Nodes/Spaceship.h"
#include "Components/Editor.h"
#include "Components/VectorRenderer.h"

#include <imgui_impl_sdl3.h>

#include <format>

void Game::Run()
{
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

	window = SDL_CreateWindow("Space", 640, 480, NULL);

	if (!window)
	{
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Error: SDL_CreateWindow(): %s\n", SDL_GetError());
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
	sceneRoot = Node::Create<SceneRoot>();

	sceneRoot->AddComponent<VectorRendererComponent>();
	sceneRoot->AddComponent<EditorComponent>();

	auto spaceship = Node::Create<Spaceship>();
	spaceship->SetParent(sceneRoot);

	auto camera = Node::Create<Camera>();
	camera->position = { 0.0f, 0.0f };
	camera->SetParent(sceneRoot);
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
	sceneRoot->StepSimulation(frameTime);

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
