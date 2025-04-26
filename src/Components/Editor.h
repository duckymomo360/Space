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

public:
	void OnAttached() override;

	void OnDetached() override;

	void OnUpdate(float dt) override;
};
