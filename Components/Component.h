#pragma once

class Node;
struct SDL_Renderer;

class Component {
protected:
	Node* node;

public:
	Component(Node* node) : node(node) {};

	virtual void Update(float dt) {};
	virtual void Draw(SDL_Renderer* renderer) {};
};