#include "SceneRoot.h"

#include "Components/RigidBody.h"

#include <cassert>

uint8_t SceneRoot::numWorlds = 0;

SceneRoot::SceneRoot()
{
	assert(numWorlds < 128, "Maximum Box2D worlds reached (128)");

	name = "SceneRoot";

	b2WorldDef worldDef = b2DefaultWorldDef();
	worldDef.gravity = { 0.0f, -10.0f };

	worldId = b2CreateWorld(&worldDef);

	numWorlds++;
}

SceneRoot::~SceneRoot()
{
	b2DestroyWorld(worldId);

	numWorlds--;
}

void SceneRoot::StepSimulation(float deltaTime)
{
	for (const auto& node : GetDescendants())
	{
		if (const auto& rigidBody = node->GetComponent<RigidBodyComponent>(); rigidBody)
		{

		}
	}

	b2World_Step(world, deltaTime, 4);
}
