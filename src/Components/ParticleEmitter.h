#pragma once

#include "Component.h"
#include "DataTypes.h"
#include "Profiler.h"

#include <vector>
#include <utility>

class ParticleEmitterComponent : public Component
{
	using Component::Component;

	struct Particle
	{
		Vector2 position;
		Vector2 velocity;
		Color4 color;
		Timer lifeTimer;
	};

	std::vector<Particle> particles;

	Timer emissionTimer;

public:
	Vector2 velocity = { 0.f, 10.f };

	uint32_t emissionRate = 0;

	float lifetime = 1.0f;

	void OnUpdate(float dt) override;

	void OnDraw(Renderer* renderer) override;

	void Emit();

	void Emit(uint32_t count);
};