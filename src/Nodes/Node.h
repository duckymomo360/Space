#pragma once

#include "Components/Component.h"
#include "DataTypes.h"

#include <vector>
#include <unordered_map>
#include <typeindex>
#include <typeinfo>

struct SDL_Renderer;

class Node {
public:
	Vector2 position;
	float rotation = 0.0f;

	Vector2 globalPosition;
	float globalRotation = 0.0f;

	std::vector<Node*> children;
	std::unordered_map<std::type_index, Component*> components;

	char name[32];

public:
	Node();

	Node(const char* name);

	virtual void Draw(SDL_Renderer* renderer);

	virtual void Update(float dt);

	void UpdateTransformRecursive(Vector2 parentGlobalPosition = Vector2(0.0f, 0.0f), float parentGlobalRotation = 0.0f);

	void DrawDebugInfo(SDL_Renderer* renderer);

	void AddChild(Node* child);

	template<std::derived_from<Component> T>
	T* GetComponent() {
		std::type_index typeId = typeid(T);

		if (components.contains(typeId)) {
			return reinterpret_cast<T*>(components[typeId]);
		}

		Component* newComponent = new T(this);
		components[typeId] = newComponent;

		newComponent->OnAttached();

		return reinterpret_cast<T*>(newComponent);
	}
};
