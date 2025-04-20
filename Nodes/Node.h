#pragma once

#include "Components/Component.h"
#include "DataTypes.h"

#include <vector>

struct SDL_Renderer;

class Node {
public:
	Vector2 position;
	float rotation = 0.0f;

	std::vector<Node*> children;
	std::vector<Component*> components;

public:
	Node() {};

	virtual void Draw(SDL_Renderer* renderer);

	virtual void Update(float dt);

	void DrawDebugInfo(SDL_Renderer* renderer);

	void AddChild(Node* child);

	template<std::derived_from<Component> T>
	T* GetComponent() {
		Component* newComponent = new T(this);
		components.push_back(newComponent);
		return reinterpret_cast<T*>(newComponent);
	}
};
