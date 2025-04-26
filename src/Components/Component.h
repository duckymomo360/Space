#pragma once

class Node;
struct SDL_Renderer;

#define COMPONENT_CONSTRUCTOR(ClassName) \
	ClassName(Node* node) : Component::Component(#ClassName, node) {}

class Component {
protected:
	Node* node;

	Component(const char* className, Node* node) : className(className), node(node) {}

public:
	const char* className;

	virtual void OnAttached() {}

	virtual void OnDetached() {}

	virtual void OnUpdate(float dt) {}

	virtual void OnDraw(SDL_Renderer* renderer) {}
};