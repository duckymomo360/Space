#include "RigidBody.h"

#include "Nodes/Node.h"
#include "Nodes/SceneRoot.h"
#include "Components/VectorRenderer.h"

void RigidBodyComponent::CreateBodies(b2WorldId worldId)
{
	b2BodyDef bodyDef = b2DefaultBodyDef();
	bodyDef.type = b2_dynamicBody;
	bodyDef.position = { node->position.x, -node->position.y };

	bodyId = b2CreateBody(worldId, &bodyDef);

	if (auto vectorRenderer = node->GetComponent<VectorRendererComponent>(); vectorRenderer)
	{
		b2ShapeDef shapeDef = b2DefaultShapeDef();
		b2Polygon groundBox = b2MakeBox(25.0f, 25.0f);
		b2CreatePolygonShape(bodyId, &shapeDef, &groundBox);
	}
}

Vector2 RigidBodyComponent::GetPosition() const
{
	auto vec = b2Body_GetPosition(bodyId);
	return { vec.x, -vec.y };
}

float RigidBodyComponent::GetRotation() const
{
	auto rot = b2Body_GetRotation(bodyId);
	return atan2f(rot.s, rot.c);
}

void RigidBodyComponent::SetLinearVelocity(const Vector2& force)
{
	b2Body_SetLinearVelocity(bodyId, { force.x, -force.y });
}

void RigidBodyComponent::SetLinearDamping(float linearDamping)
{
	b2Body_SetLinearDamping(bodyId, linearDamping);
}

void RigidBodyComponent::SetAngularVelocity(float angularVelocity)
{
	b2Body_SetAngularVelocity(bodyId, angularVelocity);
}

void RigidBodyComponent::SetAngularDamping(float angularDamping)
{
	b2Body_SetAngularDamping(bodyId, angularDamping);
}

void RigidBodyComponent::ApplyForceToCenter(const Vector2& force)
{
	b2Body_ApplyForceToCenter(bodyId, { force.x, -force.y }, true);
}

void RigidBodyComponent::ApplyAngularImpulse(float impulse)
{
	b2Body_ApplyAngularImpulse(bodyId, impulse, true);
}

void RigidBodyComponent::OnUpdate(float deltaTime)
{
	node->globalPosition = GetPosition();
	node->globalRotation = GetRotation();
}

void RigidBodyComponent::OnStart()
{
	if (auto root = node->GetRoot(); root)
	{
		CreateBodies(root->GetWorldId());
	}
}

void RigidBodyComponent::OnStop()
{
	b2DestroyBody(bodyId);
}

void RigidBodyComponent::OnAttached()
{
	node->bUpdateGlobalTransform = false;
}

void RigidBodyComponent::OnDetached()
{
	node->bUpdateGlobalTransform = true;
}
