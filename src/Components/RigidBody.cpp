#include "RigidBody.h"

#include "Nodes/Node.h"
#include "Nodes/SceneRoot.h"
#include "Components/VectorRenderer.h"

void RigidBodyComponent::CreateBodies(b2WorldId worldId)
{
	b2BodyDef bodyDef = b2DefaultBodyDef();
	bodyDef.type = b2_dynamicBody;
	bodyDef.position = { node->globalPosition.x, node->globalPosition.y };

	bodyId = b2CreateBody(worldId, &bodyDef);

	if (auto vectorRenderer = node->GetComponent<VectorRendererComponent>(); vectorRenderer)
	{
		b2ShapeDef shapeDef = b2DefaultShapeDef();
		b2Polygon groundBox = b2MakeBox(50.0f, 10.0f);
		b2CreatePolygonShape(bodyId, &shapeDef, &groundBox);
	}
}

void RigidBodyComponent::OnUpdate(float deltaTime)
{
	/*
	b2Vec2 pos = b2Body_GetPosition(bodyId);
	node->globalPosition = { pos.x, pos.y };

	b2Rot rot = b2Body_GetRotation(bodyId);
	node->globalRotation = atan2f(rot.s, rot.c);
	*/
}

void RigidBodyComponent::OnAttached()
{
	if (auto root = node->GetRoot(); root)
	{
		CreateBodies(root->GetWorldId());
	}
}

void RigidBodyComponent::OnDetached()
{
	b2DestroyBody(bodyId);
}
