#pragma once

#include "Component.h"
#include "DataTypes.h"

#include <cstdint>
#include <queue>
#include <cstdarg>
#include <string>

enum EditMode : uint8_t
{
	EDITMODE_NONE,
	EDITMODE_VECTORS,
};

class EditorComponent : public Component
{
	using Component::Component;

private:
	EditMode editMode = EDITMODE_NONE;
	const char* editModeText = nullptr;

	std::queue<std::string> warnings;
	std::queue<std::string> messages;

	int selectedPointIndex;

	float mouseX = 0.0f;
	float mouseY = 0.0f;

	bool lmbDown = false;
	bool rmbDown = false;

	static void DrawPointerLine(Renderer* renderer, Vector2 p1, Vector2 p2);

public:
	void OnAttached() override;

	void OnDetached() override;

	void OnUpdate(float deltaTime) override;

	void OnDraw(Renderer* renderer) override;
};
