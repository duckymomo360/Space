#include "Editor.h"

#include "Game.h"
#include "DataTypes.h"
#include "Renderer.h"
#include "Nodes/Node.h"
#include "Nodes/Camera.h"
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

void EditorComponent::OnUpdate(float deltaTime)
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

	/*
	if (keyStates[SDL_SCANCODE_UP])
		gGame.renderer->currentCamera->position.y -= 200.0f * deltaTime;

	if (keyStates[SDL_SCANCODE_DOWN])
		gGame.renderer->currentCamera->position.y += 200.0f * deltaTime;

	if (keyStates[SDL_SCANCODE_LEFT])
		gGame.renderer->currentCamera->position.x -= 200.0f * deltaTime;

	if (keyStates[SDL_SCANCODE_RIGHT])
		gGame.renderer->currentCamera->position.x += 200.0f * deltaTime;
	*/

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

void EditorComponent::OnDraw(Renderer* renderer)
{
	int w, h;
	SDL_GetWindowSizeInPixels(gGame.window, &w, &h);

	static auto editorFont = renderer->GetCachedFont(FONT_DEBUG, 16.0f);

	renderer->RenderText(editModeText, Vector2(5, h - 20), Vector2::Zero, { 255, 0, 255, 255 }, editorFont);

	while (!warnings.empty())
	{
		renderer->RenderText(warnings.front(), Vector2(200, h - 20 * (messages.size() + warnings.size())), Vector2::Zero, Color4::Red, editorFont);
		warnings.pop();
	}

	while (!messages.empty())
	{
		renderer->RenderText(messages.front(), Vector2(200, h - 20 * (messages.size() + warnings.size())), Vector2::Zero, Color4::White, editorFont);
		messages.pop();
	}

	if (selectedPointIndex >= 0)
	{
		auto vectorRenderer = node->GetOrAddComponent<VectorRendererComponent>();
		const Vector2& point = vectorRenderer->points[selectedPointIndex];

		renderer->RenderLine(point + Vector2::One, point + Vector2::One, Color4::Red);
		renderer->RenderLine(point - Vector2::One, point - Vector2::One, Color4::Red);

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

void EditorComponent::DrawPointerLine(Renderer* renderer, Vector2 p1, Vector2 p2)
{
	Vector2 delta = p2 - p1;
	Vector2 direction = delta.Normalize();
	float rotation = atan2(delta.y, delta.x);
	float numArrows = floorf(delta.Magnitude() / 40.0f) + 1.0f;

	for (float i = 1; i < numArrows; ++i)
	{
		Node node;
		node.name = "Arrow";

		auto vr = node.AddComponent<VectorRendererComponent>();
		vr->color = { 150, 150, 255, 255 };
		vr->scale = 5.0f;
		vr->points = {
			{-1.0f, -1.0f},
			{ 0.0f,  1.0f},
			{ 1.0f, -1.0f},
		};

		node.UpdateTransformRecursive(p1 + direction * (i * 40.f), rotation);

		node.Draw(renderer);
	}
}
