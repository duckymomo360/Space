#pragma once

#include "Node.h"

#include <box2d/box2d.h>

class SceneRoot : public Node, private std::enable_shared_from_this<SceneRoot>
{
	b2WorldId b2World;

public:
	SceneRoot();

	std::shared_ptr<SceneRoot> GetRoot() override { return shared_from_this(); }

	void StepSimulation(float deltaTime);


};
