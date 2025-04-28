#include "Spaceship.h"

#include "Game.h"
#include "Components/VectorRenderer.h"
#include "Components/ParticleEmitter.h"

#include <SDL3/SDL_scancode.h>
#include <SDL3/SDL_log.h>

Spaceship::Spaceship()
{
	name = "Spaceship";
	position = { 300.f, 300.f };

	vectorRenderer = AddComponent<VectorRendererComponent>();
	vectorRenderer->scale = 10.0f;
	vectorRenderer->points = {
		{-1.0f,  1.0f},
		{ 0.0f, -1.0f},
		{ 1.0f,  1.0f},
	};

	particlePoint = std::make_shared<Node>();
	particlePoint->name = "ParticlePoint";
	particlePoint->position = { 0.0f, 15.0f };
	
	particleEmitter = particlePoint->AddComponent<ParticleEmitterComponent>();
	particleEmitter->spread = M_PI * 0.3f;

	AddChild(particlePoint);
}

void Spaceship::Update(float deltaTime)
{
	Node::Update(deltaTime);

	if (gGame.inputManager.IsKeyDown(SDL_SCANCODE_A))
	{
		rotation -= deltaTime * 4.0f;
	}

	if (gGame.inputManager.IsKeyDown(SDL_SCANCODE_D))
	{
		rotation += deltaTime * 4.0f;
	}

	if (gGame.inputManager.IsKeyDown(SDL_SCANCODE_SPACE))
	{
		velocity += Vector2::FromAngle(rotation + M_PI) * deltaTime * 200.0f;
	}

	position += velocity * deltaTime;
}
