#pragma once
#include "Component.h"
#include "DataTypes.h"

#include <vector>
#include <utility>

class VectorRendererComponent : public Component {
	using Component::Component;

public:
	float scale = 1.0f;

	std::vector<Vector2> points;

	virtual void Draw(SDL_Renderer* renderer) override;
};