#pragma once

#include "DataTypes.h"
#include "Components/Component.h"

#include <vector>
#include <unordered_map>
#include <memory>
#include <typeindex>
#include <typeinfo>

class Renderer;
class SceneRoot;

class Node : public std::enable_shared_from_this<Node>
{
public:
	using Ptr = std::shared_ptr<Node>;

	// === Factory ===
	template<std::derived_from<Node> T>
	static std::shared_ptr<T> Create()
	{
		auto node = std::make_shared<T>();
		node->Init();
		return node;
	}

	// === Lifecycle ===
	virtual void Init();
	virtual void Update(float deltaTime);
	virtual void Draw(Renderer* renderer);

	// === Transform ===
	Vector2 position{ 0.0f, 0.0f };
	float   rotation{ 0.0f };

	Vector2 globalPosition{ 0.0f, 0.0f };
	float   globalRotation{ 0.0f };

	bool bUpdateGlobalTransform{ true };

	void UpdateTransformRecursive(Vector2 parentGlobalPosition = { 0.0f, 0.0f }, float parentGlobalRotation = 0.0f);

	// === Hierarchy ===
private:
	std::weak_ptr<Node> parent;
	std::vector<Ptr> children;

	void AddChild(Ptr child);

public:
	void             SetParent(Ptr newParent);
	std::vector<Ptr> GetChildren() const;
	Ptr              FindFirstChild(const char* name, bool recursive = false) const;
	void             GetDescendants(std::vector<Ptr>& descendants) const;
	std::vector<Ptr> GetDescendants() const;
	bool             IsInScene() const { return GetRoot() != nullptr; }
	virtual std::shared_ptr<SceneRoot> GetRoot() const;

	// === Components ===
	std::unordered_map<std::type_index, std::shared_ptr<Component>> components;

	template<std::derived_from<Component> T>
	std::shared_ptr<T> AddComponent()
	{
		auto component = std::make_shared<T>(this);
		components[typeid(T)] = component;

		if (IsInScene())
		{
			component->Start();
		}

		return static_pointer_cast<T>(component);
	}

	template<std::derived_from<Component> T>
	std::shared_ptr<T> GetComponent()
	{
		if (components.contains(typeid(T)))
		{
			return static_pointer_cast<T>(components[typeid(T)]);
		}

		return nullptr;
	}

	template<std::derived_from<Component> T>
	std::shared_ptr<T> GetOrAddComponent()
	{
		if (components.contains(typeid(T)))
		{
			return static_pointer_cast<T>(components[typeid(T)]);
		}

		return AddComponent<T>();
	}

	void DetachComponent(Component* componentToDetach);

	// === Misc ===
	const char* name{ "Node" };

private:
	void DrawDebugInfo(Renderer* renderer);
};
