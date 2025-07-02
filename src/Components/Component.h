#pragma once

class Node;
class Renderer;

class Component
{
public:
	Component(Node* node) : node(node)
	{
	}

	bool bEnabled{ true };

	void Start();
	void Stop();
	void Update(float deltaTime);
	void Draw(Renderer* renderer);

protected:
	Node* node;

	virtual void OnStart();
	virtual void OnStop();
	virtual void OnUpdate(float deltaTime);
	virtual void OnDraw(Renderer* renderer);
};
