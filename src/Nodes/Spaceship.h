#pragma once

#include "Nodes/Node.h"
#include "DataTypes.h"

#include <memory>

class VectorRendererComponent;
class ParticleEmitterComponent;
class SoundPlayerComponent;

class Spaceship : public Node
{
	std::shared_ptr<Node> particlePoint;
	std::shared_ptr<VectorRendererComponent> vectorRenderer;
	std::shared_ptr<ParticleEmitterComponent> particleEmitter;
	std::shared_ptr<SoundPlayerComponent> soundPlayer;

	Vector2 velocity;

	bool dead = false;

	void Explode();

	void Die();

public:
	Spaceship();

	void Update(float deltaTime) override;
};
