#include "Editor.h"

#include "Game.h"
#include "DataTypes.h"
#include "Nodes/Node.h"
#include "Components/VectorRenderer.h"

#include <SDL3/SDL_scancode.h>
#include <SDL3/SDL_keyboard.h>
#include <SDL3/SDL_mouse.h>
#include <SDL3/SDL_log.h>

const char* GetNameForEditMode(EditMode mode)
{
	switch (mode)
	{
	case EDITMODE_NONE:
		return "NONE";
	case EDITMODE_VECTORS:
		return "VECTORS";
	}
}

void EditorComponent::OnAttached()
{
}

void EditorComponent::OnDetached()
{
}

void EditorComponent::OnUpdate(float dt)
{
	const bool* keyStates = SDL_GetKeyboardState(nullptr);

	if (keyStates[SDL_SCANCODE_F1])
	{
		editMode = EDITMODE_NONE;
	}
	else if (keyStates[SDL_SCANCODE_F2])
	{
		editMode = EDITMODE_VECTORS;
	}

	auto buttonState = SDL_GetMouseState(&mouseX, &mouseY);

	if ((buttonState & SDL_BUTTON_LMASK))
	{
		if (!lmbDown)
		{
			lmbDown = true;

			if (editMode == EDITMODE_VECTORS)
			{
				auto vectorRenderer = node->GetComponent<VectorRendererComponent>();

				vectorRenderer->points.push_back(Vector2(mouseX, mouseY));
			}
		}
	}
	else
	{
		lmbDown = false;
	}
}

void EditorComponent::OnDraw(SDL_Renderer* renderer)
{
	int w, h;
	SDL_GetWindowSizeInPixels(gGame.window, &w, &h);

	gGame.textRenderer.DrawText(renderer, FONT_DEBUG, Vector2(5, h - 20), 1.5f, Color3(255, 0, 0),
		"EDIT MODE: %s", GetNameForEditMode(editMode));
}
