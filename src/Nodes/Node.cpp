#include "Node.h"

#include "Game.h"
#include "Renderer/Renderer.h"

using Ptr = Node::Ptr;

// === Lifecycle ===
void Node::Init()
{
}

void Node::Update(float deltaTime)
{
	for (const auto& child : children)
	{
		child->Update(deltaTime);
	}

	for (const auto& [id, component] : components)
	{
		component->Update(deltaTime);
	}
}

void Node::Draw(Renderer* renderer)
{
	for (const auto& child : children)
	{
		child->Draw(renderer);
	}

	for (const auto& [id, component] : components)
	{
		component->Draw(renderer);
	}

	if (gGame.debug)
	{
		DrawDebugInfo(renderer);
	}
}

// === Transform ===
void Node::UpdateTransformRecursive(Vector2 parentGlobalPosition, float parentGlobalRotation)
{
	auto rot = (parentGlobalRotation + rotation);
	auto pos = (parentGlobalPosition + position).RotateAround(parentGlobalPosition, parentGlobalRotation);

	if (bUpdateGlobalTransform)
	{
		globalRotation = rot;
		globalPosition = pos;
	}

	for (const auto& child : children)
	{
		child->UpdateTransformRecursive(globalPosition, globalRotation);
	}
}

// === Hierarchy ===
void Node::AddChild(Ptr child)
{
	child->parent = shared_from_this();
	children.push_back(child);
}

void Node::SetParent(Ptr newParent)
{
	newParent->AddChild(shared_from_this());

	if (IsInScene())
	{
		for (const auto& [id, component] : components)
		{
			component->Start();
		}
	}
	else
	{
		for (const auto& [id, component] : components)
		{
			component->Stop();
		}
	}
}

std::vector<Ptr> Node::GetChildren() const
{
	return children;
}

Ptr Node::FindFirstChild(const char* name, bool recursive) const
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

void Node::GetDescendants(std::vector<Ptr>& descendants) const
{
	for (const auto child : children)
	{
		descendants.push_back(child);
		child->GetDescendants(descendants);
	}
}

std::vector<Ptr> Node::GetDescendants() const
{
	std::vector<Ptr> descendants;
	GetDescendants(descendants);
	return descendants;
}

std::shared_ptr<SceneRoot> Node::GetRoot() const
{
	if (parent.expired())
	{
		return nullptr;
	}

	return parent.lock()->GetRoot();
}

// === Components ===
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
			it->second->Stop();
			components.erase(it);
			return;
		}
	}
}

// === Misc ===
void Node::DrawDebugInfo(Renderer* renderer)
{
	renderer->RenderPoint(globalPosition, Color4::Red);

	static auto debugFont = renderer->GetCachedFont(FONT_DEBUG, 16.0f);
	renderer->RenderText(name, globalPosition + Vector2(2.0f, 2.0f), Vector2::Zero, Color4::Red, debugFont, 1.0f);
}
