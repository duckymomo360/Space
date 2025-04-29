#include "Node.h"

#include "Game.h"

void Node::Draw(SDL_Renderer* renderer)
{
	for (const auto& child : children)
	{
		child->Draw(renderer);
	}

	for (const auto& [id, component] : components)
	{
		component->OnDraw(renderer);
	}

	if (gGame.debug)
	{
		DrawDebugInfo(renderer);
	}
}

void Node::Update(float deltaTime)
{
	for (const auto& child : children)
	{
		child->Update(deltaTime);
	}

	for (const auto& [id, component] : components)
	{
		component->OnUpdate(deltaTime);
	}
}

void Node::UpdateTransformRecursive(Vector2 parentGlobalPosition, float parentGlobalRotation)
{
	globalRotation = (parentGlobalRotation + rotation);
	globalPosition = (parentGlobalPosition + position).RotateAround(parentGlobalPosition, parentGlobalRotation);

	for (const auto& child : children) {
		child->UpdateTransformRecursive(globalPosition, globalRotation);
	}
}

void Node::DrawDebugInfo(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderPoint(renderer, globalPosition.x, globalPosition.y);
	gGame.textRenderer.DrawText(renderer, FONT_DEBUG, globalPosition + Vector2(2.0f, 2.0f), 1.0f, { 255, 0, 0 }, name);
}

void Node::AddChild(const std::shared_ptr<Node>& node)
{
	children.push_back(node);
}

void Node::DetachComponent(Component* componentToDetach)
{
	if (!componentToDetach)
	{
		return;
	}

	for (auto it = components.begin(); it != components.end(); ++it)
	{
		if (it->second.get() == componentToDetach)
		{
			it->second->OnDetached();
			components.erase(it);
			return;
		}
	}
}
