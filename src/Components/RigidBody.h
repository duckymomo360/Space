#pragma once

#include "Component.h"

#include <box2d/box2d.h>

class RigidBodyComponent : public Component
{
	using Component::Component;

	b2BodyId bodyId;

	void CreateBodies(b2WorldId worldId);

public:
	void OnUpdate(float deltaTime) override;

	void OnAttached() override;

	void OnDetached() override;
};
