#include "Component.h"

#include "Nodes/Node.h"

void Component::OnStart()
{
}

void Component::OnStop()
{
}

void Component::OnUpdate(float deltaTime)
{
}

void Component::OnDraw(Renderer* renderer)
{
}

void Component::Start()
{
	if (bEnabled)
	{
		OnStart();
	}
}

void Component::Stop()
{
	if (bEnabled)
	{
		OnStop();
	}
}

void Component::Update(float deltaTime)
{
	if (bEnabled && node->IsInScene())
	{
		OnUpdate(deltaTime);
	}
}

void Component::Draw(Renderer* renderer)
{
	if (bEnabled && node->IsInScene())
	{
		OnDraw(renderer);
	}
}
