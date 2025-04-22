#pragma once

#include "KeyboardInputManager.h"
#include "TextRenderer.h"
#include "Profiler.h"

#include <vector>
#include <optional>

struct SDL_Window;
struct SDL_Renderer;
class Node;

class Game {
public:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	Node* sceneRoot = nullptr;

	KeyboardInputManager inputManager;
	TextRenderer textRenderer;

	bool shouldExit = false;
	bool debug = true;

	float frameTime;
	Timer frameTimer;
	Averager fpsAverager;

public:
	void Run();
	void SetupScene();
	void PollEvents();
	void UpdateScene();
	void RenderFrame();
};

inline Game gGame;
