#include "Spaceship.h"

#include "Game.h"
#include "Components/VectorRenderer.h"
#include "Components/ParticleEmitter.h"
#include "Components/SoundPlayer.h"
#include "Components/RigidBody.h"

#include "Nodes/SceneRoot.h"

#include <SDL3/SDL_scancode.h>
#include <SDL3/SDL_log.h>
#include <random>

std::random_device rd;
std::mt19937 gen(rd());

Spaceship::Spaceship()
{
	name = "Spaceship";
}

void Spaceship::Init()
{
	position = { 300.f, 300.f };

	vectorRenderer = AddComponent<VectorRendererComponent>();
	vectorRenderer->scale = 10.0f;
	vectorRenderer->points = {
		{-1.0f,  1.0f},
		{ 0.0f, -1.0f},
		{ 1.0f,  1.0f},
	};

	particlePoint = Create<Node>();
	particlePoint->name = "ParticlePoint";
	particlePoint->position = { 0.0f, 15.0f };

	particleEmitter = particlePoint->AddComponent<ParticleEmitterComponent>();
	particleEmitter->lifetime = 10.f;

	AddChild(particlePoint);

	soundPlayer = AddComponent<SoundPlayerComponent>();
	soundPlayer->wavPath = "data/SOUND/thruster_loop.wav";

	rigidBody = AddComponent<RigidBodyComponent>();
}

void Spaceship::Update(float deltaTime)
{
	Node::Update(deltaTime);
	rigidBody->SetAngularDamping(10.0f);

	particleEmitter->emissionRate = 0;

	if (dead)
	{
		return;
	}

	std::uniform_real_distribution<float> dist(M_PI * -.2f, M_PI * .2f);
	particleEmitter->velocity = velocity * .5f + Vector2::FromAngle(globalRotation + dist(gen)) * 100.f;

	static const bool* keyStates = SDL_GetKeyboardState(NULL);

	if (keyStates[SDL_SCANCODE_A])
	{
		rigidBody->ApplyAngularImpulse(-500000.0f);
	}
	
	if (keyStates[SDL_SCANCODE_D])
	{
		rigidBody->ApplyAngularImpulse(500000.0f);
	}

	if (keyStates[SDL_SCANCODE_SPACE])
	{
		rigidBody->ApplyForceToCenter(Vector2::FromAngle(rigidBody->GetRotation() - M_PI) * 500000.0f);
		
		particleEmitter->emissionRate = 100;

		if (!soundPlayer->playing)
		{
			soundPlayer->Play();
		}
	}
	else
	{
		soundPlayer->Stop();
	}

	if (keyStates[SDL_SCANCODE_E])
	{
		Explode();
	}

	//position += velocity * deltaTime;
}

void Spaceship::Explode()
{
	if (dead) return;

	// TODO: Only one of each component type can be attached.
	// auto sound = AddComponent<SoundPlayerComponent>();
	// sound->wavPath = "data/SOUND/explosion_02.wav";
	// sound->Play();

	Die();
}

void Spaceship::Die()
{
	if (dead) return;

	dead = true;

	soundPlayer->Stop();

	vectorRenderer->enabled = false;
}
