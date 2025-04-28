#pragma once

#include "Nodes/Node.h"
#include "DataTypes.h"

#include <memory>

class VectorRendererComponent;
class ParticleEmitterComponent;

class Spaceship : public Node
{
	std::shared_ptr<Node> particlePoint;
	std::shared_ptr<VectorRendererComponent> vectorRenderer;
	std::shared_ptr<ParticleEmitterComponent> particleEmitter;

	Vector2 velocity;

public:
	Spaceship();

	void Update(float deltaTime) override;
};
