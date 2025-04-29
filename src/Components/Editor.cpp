#include "Editor.h"

#include "Game.h"
#include "DataTypes.h"
#include "Nodes/Node.h"
#include "Components/VectorRenderer.h"

#include <SDL3/SDL_scancode.h>
#include <SDL3/SDL_keyboard.h>
#include <SDL3/SDL_mouse.h>
#include <SDL3/SDL_log.h>

#include <format>


void EditorComponent::OnAttached()
{
}

void EditorComponent::OnDetached()
{
}

void EditorComponent::OnUpdate(float dt)
{
	static const bool* keyStates = SDL_GetKeyboardState(NULL);

	if (keyStates[SDL_SCANCODE_F1])
	{
		editMode = EDITMODE_NONE;
	}
	else if (keyStates[SDL_SCANCODE_F2])
	{
		editMode = EDITMODE_VECTORS;
	}

	auto mouseButtonState = SDL_GetMouseState(&mouseX, &mouseY);

	bool lmbPressed = false;
	if (!lmbDown && mouseButtonState & SDL_BUTTON_LMASK)
		lmbPressed = true;

	lmbDown = mouseButtonState & SDL_BUTTON_LMASK;

	bool rmbPressed = false;
	if (!rmbDown && mouseButtonState & SDL_BUTTON_RMASK)
		rmbPressed = true;

	rmbDown = mouseButtonState & SDL_BUTTON_RMASK;

	switch (editMode)
	{
	case EDITMODE_NONE:
		editModeText = "EDIT MODE: NONE";
		break;

	case EDITMODE_VECTORS:
		editModeText = "EDIT MODE: VECTORS";

		auto vectorRenderer = node->GetOrAddComponent<VectorRendererComponent>();

		if (vectorRenderer == nullptr)
		{
			warnings.push("Object has no VectorRenderer component");
			break;
		}

		messages.push(std::format("POINTS: {}", vectorRenderer->points.size()));
		
		if (rmbPressed)
		{
			selectedPointIndex = vectorRenderer->FindNearestPointIndex(Vector2(mouseX, mouseY), 10.0f);
		}
		
		if (lmbPressed && selectedPointIndex < 0)
		{
			vectorRenderer->points.push_back(Vector2(mouseX, mouseY));
		}

		if (selectedPointIndex >= 0)
		{
			messages.push(std::format("INDEX: {}", selectedPointIndex));

			if (lmbPressed)
			{
				vectorRenderer->points.insert(vectorRenderer->points.begin() + selectedPointIndex + 1, Vector2(mouseX, mouseY));
			}

			if (keyStates[SDL_SCANCODE_UP])
				vectorRenderer->points[selectedPointIndex].y -= 1.f;

			if (keyStates[SDL_SCANCODE_DOWN])
				vectorRenderer->points[selectedPointIndex].y += 1.f;

			if (keyStates[SDL_SCANCODE_LEFT])
				vectorRenderer->points[selectedPointIndex].x -= 1.f;

			if (keyStates[SDL_SCANCODE_RIGHT])
				vectorRenderer->points[selectedPointIndex].x += 1.f;

			if (keyStates[SDL_SCANCODE_DELETE])
			{
				vectorRenderer->points.erase(vectorRenderer->points.begin() + selectedPointIndex);
				selectedPointIndex = -1;
			}
		}

		break;
	}
}

void EditorComponent::OnDraw(SDL_Renderer* renderer)
{
	int w, h;
	SDL_GetWindowSizeInPixels(gGame.window, &w, &h);

	gGame.textRenderer.DrawText(renderer, FONT_DEBUG, Vector2(5, h - 20), 1.5f, Color3(255, 0, 255), editModeText);

	while (!warnings.empty())
	{
		gGame.textRenderer.DrawText(renderer, FONT_DEBUG, Vector2(200, h - 20 * (messages.size() + warnings.size())), 1.5f, Color3(255, 0, 0), warnings.front().c_str());
		warnings.pop();
	}

	while (!messages.empty())
	{
		gGame.textRenderer.DrawText(renderer, FONT_DEBUG, Vector2(200, h - 20 * (messages.size() + warnings.size())), 1.5f, Color3(255, 255, 255), messages.front().c_str());
		messages.pop();
	}

	if (selectedPointIndex >= 0)
	{
		auto vectorRenderer = node->GetOrAddComponent<VectorRendererComponent>();
		const Vector2& point = vectorRenderer->points[selectedPointIndex];

		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		SDL_RenderLine(renderer, point.x - 5.f, point.y - 5.f, point.x + 5.f, point.y + 5.f);
		SDL_RenderLine(renderer, point.x - 5.f, point.y + 5.f, point.x + 5.f, point.y - 5.f);

		if (selectedPointIndex + 1 < vectorRenderer->points.size())
		{
			DrawPointerLine(renderer, point, vectorRenderer->points[selectedPointIndex + 1]);
		}

		if (selectedPointIndex > 0)
		{
			DrawPointerLine(renderer, vectorRenderer->points[selectedPointIndex - 1], point);
		}
	}
}

void EditorComponent::DrawPointerLine(SDL_Renderer* renderer, const Vector2& p1, const Vector2& p2)
{
	float numArrows = floorf(p1.DistanceFrom(p2) / 40.0f) + 1.0f;

	for (float i = 1; i < numArrows; i++)
	{
		Node node;
		node.name = "Arrow";

		auto vr = node.AddComponent<VectorRendererComponent>();
		vr->color = Color3(150, 150, 255);
		vr->scale = 5.0f;
		vr->points = {
			{-1.0f, -1.0f},
			{ 0.0f,  1.0f},
			{ 1.0f, -1.0f},
		};

		// This should use normalization instead
		float r = atan2(p1.x - p2.x, p2.y - p1.y);
		node.UpdateTransformRecursive(p1 + Vector2::FromAngle(r) * (i * 40.f), r);

		node.Draw(renderer);
	}
}
