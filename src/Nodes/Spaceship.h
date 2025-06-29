#pragma once

#include "Nodes/Node.h"
#include "DataTypes.h"

#include <memory>

class VectorRendererComponent;
class ParticleEmitterComponent;
class SoundPlayerComponent;
class RigidBodyComponent;

class Spaceship : public Node
{
	std::shared_ptr<Node> particlePoint;
	std::shared_ptr<VectorRendererComponent> vectorRenderer;
	std::shared_ptr<ParticleEmitterComponent> particleEmitter;
	std::shared_ptr<SoundPlayerComponent> soundPlayer;
	std::shared_ptr<RigidBodyComponent> rigidBody;

	Vector2 velocity;

	bool dead = false;

	void Explode();

	void Die();

public:
	Spaceship();

	void Init() override;

	void Update(float deltaTime) override;
};
