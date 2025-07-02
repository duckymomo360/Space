#pragma once

#include "Node.h"

#include <box2d/box2d.h>

class SceneRoot : public Node
{
	static uint8_t numWorlds;

	b2WorldId worldId;

public:
	SceneRoot();

	~SceneRoot();

	std::shared_ptr<SceneRoot> GetRoot() const override
	{
		return std::const_pointer_cast<SceneRoot>(std::static_pointer_cast<const SceneRoot>(shared_from_this()));
	}

	void StepSimulation(float deltaTime);

	b2WorldId GetWorldId() { return worldId; }
};
