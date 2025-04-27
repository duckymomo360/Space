#pragma once

#include "Component.h"

#include <cstdint>

enum EditMode : uint8_t
{
	EDITMODE_NONE,
	EDITMODE_VECTORS,
};

class EditorComponent : public Component
{
public:
	COMPONENT_CONSTRUCTOR(EditorComponent);

private:
	EditMode editMode = EDITMODE_NONE;

	float mouseX = 0.0f;
	float mouseY = 0.0f;

	bool lmbDown = false;

public:
	void OnAttached() override;

	void OnDetached() override;

	void OnUpdate(float dt) override;

	void OnDraw(SDL_Renderer* renderer) override;
};
