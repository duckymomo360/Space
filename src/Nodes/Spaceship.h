#pragma once

#include "Nodes/Node.h"
#include "DataTypes.h"

class VectorRendererComponent;

class Spaceship : public Node {
	VectorRendererComponent* renderer;

	Node* particlePoint;
	class ParticleEmitterComponent* emitter;

	Vector2 velocity;

public:
	Spaceship();

	virtual void Update(float dt);
};