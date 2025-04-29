#pragma once

#include "Renderer.h"
#include "Profiler.h"

#include <vector>
#include <optional>
#include <memory>

struct SDL_Window;
struct SDL_Renderer;
class Node;

class Game
{
public:
	SDL_Window* window = nullptr;

	std::shared_ptr<Node> sceneRoot;

	Renderer* renderer;

	bool shouldExit = false;

	bool debug = false;

	float frameTime;
	Timer frameTimer;
	Sampler<float, 16> fpsSampler;

public:
	void Run();
	void SetupScene();
	void PollEvents();
	void UpdateScene();
	void RenderFrame();
};

inline Game gGame;
