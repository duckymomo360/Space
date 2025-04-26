#pragma once

#include "Components/Component.h"
#include "DataTypes.h"

#include <vector>

struct SDL_Renderer;

class Node {
public:
	Vector2 position;
	float rotation = 0.0f;

	Vector2 globalPosition;
	float globalRotation = 0.0f;

	std::vector<Node*> children;
	std::vector<Component*> components;

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
		Component* newComponent = new T(this);
		components.push_back(newComponent);
		return reinterpret_cast<T*>(newComponent);
	}
};
