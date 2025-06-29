#pragma once

#include "Component.h"

#include <box2d/box2d.h>

struct Vector2;

class RigidBodyComponent : public Component
{
	using Component::Component;

	b2BodyId bodyId;

	void CreateBodies(b2WorldId worldId);

public:
	Vector2 GetPosition() const;
	float   GetRotation() const;

	void SetLinearVelocity(const Vector2& force);
	void SetLinearDamping(float linearDamping);

	void SetAngularVelocity(float angularVelocity);
	void SetAngularDamping(float angularDamping);

	void ApplyForceToCenter(const Vector2& force);

	void ApplyAngularImpulse(float impulse);

public:
	void OnUpdate(float deltaTime) override;

	void OnStart() override;

	void OnStop() override;

	void OnAttached() override;

	void OnDetached() override;
};
