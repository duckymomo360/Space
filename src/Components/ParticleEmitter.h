#pragma once

#include "Component.h"
#include "DataTypes.h"
#include "Profiler.h"

#include <vector>
#include <utility>

class ParticleEmitterComponent : public Component {
	struct Particle {
		Vector2 position;
		Vector2 velocity;
		Color3 color;
		Timer lifeTimer;
	};

	std::vector<Particle> particles;

	Timer emissionTimer;

public:
	Vector2 velocity{ 0.f, 10.f };

	uint32_t emissionRate{ 0 };

	float lifetime{ 1.f };

public:
	COMPONENT_CONSTRUCTOR(ParticleEmitterComponent);

	void OnUpdate(float dt) override;

	void OnDraw(SDL_Renderer* renderer) override;

	void Emit();

	void Emit(uint32_t count);
};