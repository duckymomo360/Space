#pragma once

#include "Component.h"

#include "Interfaces/IBox2DBody.h"
#include <box2d/box2d.h>

struct Vector2;

class RigidBodyComponent : public Component, public IBox2DBody
{
	using Component::Component;

private:
	void CreateBody(b2WorldId worldId) override;

public:
	void OnStart() override;
	void OnStop() override;
	void OnUpdate(float deltaTime) override;
};
