#pragma once

class Node;
struct SDL_Renderer;

class Component
{
protected:
	Node* node;

public:
	bool enabled = true;

	Component(Node* node) : node(node) {}

	virtual void OnAttached() {}

	virtual void OnDetached() {}

	virtual void OnUpdate(float dt) {}

	virtual void OnDraw(SDL_Renderer* renderer) {}

	void Detach();
};
