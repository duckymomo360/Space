#pragma once
#include "Component.h"
#include "DataTypes.h"

#include <vector>
#include <utility>

class ParticleEmitterComponent : public Component {
	using Component::Component;

	struct Particle {
		Vector2 position;
		Vector2 velocity;
	};

	std::vector<Particle> particles;

public:
	virtual void Update(float dt) override;

	virtual void Draw(SDL_Renderer* renderer) override;

	void Emit(uint32_t count);

	void Emit();
};