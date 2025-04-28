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

	Color3 color{ 255, 255, 255 };

	int FindNearestPointIndex(const Vector2& point, float maxDistance = 10000.0f);

	void OnDraw(SDL_Renderer* renderer) override;
};