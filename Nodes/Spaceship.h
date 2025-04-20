#pragma once

#include "Nodes/Node.h"

class VectorRendererComponent;

class Spaceship : public Node {
	VectorRendererComponent* renderer;

	Node* particlePoint;

public:
	Spaceship();

	virtual void Update(float dt);
};