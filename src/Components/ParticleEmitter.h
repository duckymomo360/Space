#pragma once
#include "Component.h"
#include "DataTypes.h"

#include <vector>
#include <utility>

class ParticleEmitterComponent : public Component {
	struct Particle {
		Vector2 position;
		Vector2 velocity;
		Color3 color;
	};

	std::vector<Particle> particles;

public:
	COMPONENT_CONSTRUCTOR(ParticleEmitterComponent);

	float spread = 0.0f;

	float speed = 50.0f;

	void OnUpdate(float dt) override;

	void OnDraw(SDL_Renderer* renderer) override;

	void Emit(Vector2 velocity);

	void Emit();

	void Emit(uint32_t count);
};