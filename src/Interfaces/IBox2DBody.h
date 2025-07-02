#pragma once

#include <box2d/box2d.h>

struct Vector2;

class IBox2DBody
{
protected:
	b2BodyId bodyId;

	virtual void CreateBody(b2WorldId worldId) = 0;

	void DestroyBody();

public:
	Vector2 GetPosition() const;
	float GetRotation() const;

	void SetLinearVelocity(const Vector2& force);
	void SetLinearDamping(float linearDamping);

	void SetAngularVelocity(float angularVelocity);
	void SetAngularDamping(float angularDamping);

	void ApplyForceToCenter(const Vector2& force);

	void ApplyAngularImpulse(float impulse);
};
