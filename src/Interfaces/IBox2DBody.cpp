#include "IBox2DBody.h"

#include "DataTypes.h"

Vector2 IBox2DBody::GetPosition() const
{
	auto vec = b2Body_GetPosition(bodyId);
	return { vec.x, -vec.y };
}

float IBox2DBody::GetRotation() const
{
	auto rot = b2Body_GetRotation(bodyId);
	return atan2f(rot.s, rot.c);
}

void IBox2DBody::SetLinearVelocity(const Vector2& force)
{
	b2Body_SetLinearVelocity(bodyId, { force.x, -force.y });
}

void IBox2DBody::SetLinearDamping(float linearDamping)
{
	b2Body_SetLinearDamping(bodyId, linearDamping);
}

void IBox2DBody::SetAngularVelocity(float angularVelocity)
{
	b2Body_SetAngularVelocity(bodyId, angularVelocity);
}

void IBox2DBody::SetAngularDamping(float angularDamping)
{
	b2Body_SetAngularDamping(bodyId, angularDamping);
}

void IBox2DBody::ApplyForceToCenter(const Vector2& force)
{
	b2Body_ApplyForceToCenter(bodyId, { force.x, -force.y }, true);
}

void IBox2DBody::ApplyAngularImpulse(float impulse)
{
	b2Body_ApplyAngularImpulse(bodyId, impulse, true);
}

void IBox2DBody::DestroyBody()
{
	b2DestroyBody(bodyId);
}
