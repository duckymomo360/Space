#include "Node.h"

#include "Game.h"

#include <SDL3/SDL_render.h>
#include <SDL3_ttf/SDL_ttf.h>

void Node::Draw(SDL_Renderer* renderer) {
	if (gGame.debug) {
		DrawDebugInfo(renderer);
	}

	for (auto& component : components) {
		component->Draw(renderer);
	}

	for (auto& child : children) {
		child->Draw(renderer);
	}
}

void Node::DrawDebugInfo(SDL_Renderer* renderer) {

}

void Node::Update(float dt) {
	for (auto& child : children) {
		child->Update(dt);
	}
}

void Node::AddChild(Node* child) {
	children.push_back(child);
}
