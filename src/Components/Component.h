#pragma once

class Node;
class Renderer;

class Component
{
protected:
	Node* node;

public:
	bool enabled = true;

	Component(Node* node) : node(node) {}

	virtual void OnStart() {}
	
	virtual void OnStop() {}

	virtual void OnAttached() {}

	virtual void OnDetached() {}

	virtual void OnUpdate(float dt) {}

	virtual void OnDraw(Renderer* renderer) {}

	void Start() { OnStart(); }
	void Stop() { OnStop(); }

	void Detach();
};
