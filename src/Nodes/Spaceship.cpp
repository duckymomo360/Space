#include "Spaceship.h"

#include "Game.h"
#include "Components/VectorRenderer.h"
#include "Components/ParticleEmitter.h"

#include <SDL3/SDL_scancode.h>
#include <SDL3/SDL_log.h>

Spaceship::Spaceship() {
	strcpy(name, "Spaceship");

	position.x = 300.0f;
	position.y = 300.0f;

	renderer = GetComponent<VectorRendererComponent>();

	renderer->scale = 10.0f;

	renderer->points = {
		{-1.0f,  1.0f},
		{ 0.0f, -1.0f},
		{ 1.0f,  1.0f},
	};

	particlePoint = new Node("Emitter");
	particlePoint->position = Vector2(0.0f, 15.0f);
	
	emitter = particlePoint->GetComponent<ParticleEmitterComponent>();

	AddChild(particlePoint);
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
		velocity += Vector2::FromAngle(rotation + M_PI) * 2.0f;

		emitter->Emit();
	}

	position += velocity * dt;
}
