#pragma once
#include "Component.h"
#include "DataTypes.h"

#include <vector>
#include <utility>

class VectorRendererComponent : public Component {
public:
	COMPONENT_CONSTRUCTOR(VectorRendererComponent);

	float scale = 1.0f;

	std::vector<Vector2> points;

	void Draw(SDL_Renderer* renderer) override;
};