#include "RigidBody.h"

#include "Nodes/Node.h"
#include "Nodes/SceneRoot.h"
#include "Components/VectorRenderer.h"

void RigidBodyComponent::CreateBody(b2WorldId worldId)
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

void RigidBodyComponent::OnStart()
{
	node->bUpdateGlobalTransform = false;

	if (auto root = node->GetRoot(); root)
	{
		CreateBody(root->GetWorldId());
	}
}

void RigidBodyComponent::OnStop()
{
	node->bUpdateGlobalTransform = true;

	DestroyBody();
}

void RigidBodyComponent::OnUpdate(float deltaTime)
{
	node->globalPosition = GetPosition();
	node->globalRotation = GetRotation();
}
