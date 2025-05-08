#pragma once

#include "DataTypes.h"
#include "Components/Component.h"

#include <vector>
#include <unordered_map>
#include <memory>
#include <typeindex>
#include <typeinfo>

class SceneRoot;

class Node
{
	void DrawDebugInfo(Renderer* renderer);

public:
	const char* name = "Node";

	Vector2 position;
	float   rotation{ 0.0f };

	Vector2 globalPosition;
	float   globalRotation{ 0.0f };

	std::weak_ptr<Node> parent;

	std::vector<std::shared_ptr<Node>> children;

	std::unordered_map<std::type_index, std::shared_ptr<Component>> components;

public:
	virtual void Draw(Renderer* renderer);

	virtual void Update(float deltaTime);

	void UpdateTransformRecursive(Vector2 parentGlobalPosition = { 0.0f, 0.0f }, float parentGlobalRotation = 0.0f);

	void AddChild(const std::shared_ptr<Node>& node);

	std::shared_ptr<Node> FindFirstChild(const char* name, bool recursive = false);

	template<std::derived_from<Component> T> std::shared_ptr<T> AddComponent()
	{
		auto component = std::make_shared<T>(this);
		components[typeid(T)] = component;
		component->OnAttached();

		return static_pointer_cast<T>(component);
	}

	template<std::derived_from<Component> T> std::shared_ptr<T> GetComponent()
	{
		if (components.contains(typeid(T)))
		{
			return static_pointer_cast<T>(components[typeid(T)]);
		}

		return nullptr;
	}

	template<std::derived_from<Component> T> std::shared_ptr<T> GetOrAddComponent()
	{
		if (components.contains(typeid(T)))
		{
			return static_pointer_cast<T>(components[typeid(T)]);
		}

		return AddComponent<T>();
	}

	void DetachComponent(Component* componentToDetach);

	virtual std::shared_ptr<SceneRoot> GetRoot();
	
	std::vector<std::shared_ptr<Node>> GetChildren() const
	{
		return children;
	}

	void GetDescendants(std::vector<std::shared_ptr<Node>>& descendants) const;

	std::vector<std::shared_ptr<Node>>& GetDescendants() const
	{
		std::vector<std::shared_ptr<Node>> descendants;
		GetDescendants(descendants);
		return descendants;
	}
};
