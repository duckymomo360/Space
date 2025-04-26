#include "Editor.h"

#include "Game.h"

#include <SDL3/SDL_scancode.h>
#include <SDL3/SDL_keyboard.h>

void EditorComponent::OnAttached()
{
}

void EditorComponent::OnDetached()
{
}

void EditorComponent::OnUpdate(float dt)
{
	const bool* keyStates = SDL_GetKeyboardState(nullptr);

	if (keyStates[SDL_SCANCODE_LCTRL])
	{
		if (keyStates[SDL_SCANCODE_1])
		{
			editMode = EDITMODE_NONE;
		}
		else if (keyStates[SDL_SCANCODE_2])
		{
			editMode = EDITMODE_VECTORS;
		}
	}
}
