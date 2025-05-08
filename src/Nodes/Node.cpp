#include "Node.h"

#include "Game.h"
#include "Renderer.h"

void Node::Draw(Renderer* renderer)
{
	for (const auto& child : children)
	{
		child->Draw(renderer);
	}

	for (const auto& [id, component] : components)
	{
		if (component->enabled)
		{
			component->OnDraw(renderer);
		}
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
		if (component->enabled)
		{
			component->OnUpdate(deltaTime);
		}
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

void Node::DrawDebugInfo(Renderer* renderer)
{
	renderer->RenderPoint(globalPosition, Color4::Red);

	static auto debugFont = renderer->GetCachedFont(FONT_DEBUG, 16.0f);
	renderer->RenderText(name, globalPosition + Vector2(2.0f, 2.0f), Vector2::Zero, Color4::Red, debugFont, 1.0f);
}

void Node::AddChild(const std::shared_ptr<Node>& node)
{
	children.push_back(node);
}

std::shared_ptr<Node> Node::FindFirstChild(const char* name, bool recursive)
{
	for (const auto child : children)
	{
		if (strcmp(name, child->name) == 0)
		{
			return child;
		}

		if (recursive)
		{
			if (const auto found = child->FindFirstChild(name, true); found)
			{
				return found;
			}
		}
	}

	return nullptr;
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

std::shared_ptr<SceneRoot> Node::GetRoot()
{
	if (parent.expired())
	{
		return nullptr;
	}

	return parent.lock()->GetRoot();
}

void Node::GetDescendants(std::vector<std::shared_ptr<Node>>& descendants) const
{
	for (const auto child : children)
	{
		descendants.push_back(child);
		GetDescendants(descendants);
	}
}
