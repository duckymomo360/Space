#include "Node.h"

#include "Game.h"

#include <SDL3/SDL_render.h>
#include <SDL3_ttf/SDL_ttf.h>

Node::Node() : name("Node") {}

Node::Node(const char* nodeName) {
	strncpy_s(name, nodeName, sizeof(name));
}

void Node::Draw(SDL_Renderer* renderer) {
	for (auto& component : components) {
		component->Draw(renderer);
	}

	for (auto& child : children) {
		child->Draw(renderer);
	}

	if (gGame.debug) {
		DrawDebugInfo(renderer);
	}
}

void Node::DrawDebugInfo(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderPoint(renderer, globalPosition.x, globalPosition.y);
	gGame.textRenderer.DrawText(renderer, FONT_DEBUG, name, globalPosition + Vector2(2.0f, 2.0f), 1.0f, {255, 0, 0, SDL_ALPHA_OPAQUE});
}

void Node::Update(float dt) {
	for (auto& child : children) {
		child->Update(dt);
	}
}

void Node::UpdateTransformRecursive(Vector2 parentGlobalPosition, float parentGlobalRotation) {
	globalRotation = (parentGlobalRotation + rotation);
	globalPosition = (parentGlobalPosition + position).RotateAround(parentGlobalPosition, parentGlobalRotation);

	for (auto& child : children) {
		child->UpdateTransformRecursive(globalPosition, globalRotation);
	}
}

void Node::AddChild(Node* child) {
	children.push_back(child);
}

Node* Node::Copy() {
	Node* newNode = new Node;
	memcpy(newNode, this, sizeof(Node));
	return newNode;
}