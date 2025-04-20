#include "Spaceship.h"

#include "Components/VectorRenderer.h"
#include "Game.h"

#include <SDL3/SDL_scancode.h>
#include <SDL3/SDL_log.h>

Spaceship::Spaceship() {
	position.x = 300.0f;
	position.y = 300.0f;

	renderer = GetComponent<VectorRendererComponent>();

	renderer->scale = 10.0f;

	renderer->points = {
		{-1.0f,  1.0f},
		{ 0.0f, -1.0f},
		{ 1.0f,  1.0f},
	};

	particlePoint = new Node();
	particlePoint->position = Vector2(0.0f, 5.0f);
}

void Spaceship::Update(float dt) {
	Node::Update(dt);

	if (gGame.inputManager.IsKeyDown(SDL_SCANCODE_A)) {
		rotation -= dt * 3.0f;
	}

	if (gGame.inputManager.IsKeyDown(SDL_SCANCODE_D)) {
		rotation += dt * 3.0f;
	}

	if (gGame.inputManager.IsKeyDown(SDL_SCANCODE_SPACE)) {

	}
}
