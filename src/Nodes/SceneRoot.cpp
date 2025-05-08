#include "SceneRoot.h"

#include "Components/RigidBody.h"

SceneRoot::SceneRoot()
{
	name = "SceneRoot";

	b2WorldDef worldDef = b2DefaultWorldDef();
	worldDef.gravity = { 0.0f, -10.0f };

	b2World = b2CreateWorld(&worldDef);
}

void SceneRoot::StepSimulation(float deltaTime)
{
	for (const auto node : GetDescendants())
	{
		if (auto rigidBody = node->GetComponent<RigidBodyComponent>(); rigidBody)
		{

		}
	}

	b2World_Step(b2World, deltaTime, 4);
}
