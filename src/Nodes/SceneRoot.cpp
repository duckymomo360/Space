#include "SceneRoot.h"

#include <cassert>

uint8_t SceneRoot::numWorlds = 0;

SceneRoot::SceneRoot()
{
	assert(numWorlds < 128, "Maximum Box2D worlds reached (128)");

	name = "SceneRoot";

	b2WorldDef worldDef = b2DefaultWorldDef();
	worldDef.gravity = { 0.0f, -50.0f };

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
	b2World_Step(worldId, deltaTime, 4);
}
