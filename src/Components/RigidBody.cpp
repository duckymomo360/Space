#include "RigidBody.h"

void RigidBodyComponent::CreateBodies(b2WorldId worldId)
{
	b2BodyDef bodyDef = b2DefaultBodyDef();
	bodyDef.type = b2_dynamicBody;
	bodyDef.position = (b2Vec2){ 0.0f, -10.0f };

	bodyId = b2CreateBody(worldId, &bodyDef);

	if (auto vectorRenderer = node->GetComponent<VectorRendererComponent>(); vectorRenderer)
	{
		b2ShapeDef shapeDef = b2DefaultShapeDef();
		b2Polygon groundBox = b2MakeBox(50.0f, 10.0f);
		b2CreatePolygonShape(bodyId, shapeDef, groundBox);
	}
}

void RigidBodyComponent::OnAttached()
{
	if (auto root = node->GetRoot(); root)
	{
		CreateBodies(root);
	}
}

void RigidBodyComponent::OnDetached()
{
	b2DestroyBody(bodyId);
}
