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

	void Update(float dt) override;

	void Draw(SDL_Renderer* renderer) override;

	void Emit(uint32_t count);

	void Emit();
};