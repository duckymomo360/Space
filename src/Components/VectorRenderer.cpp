#include "VectorRenderer.h"
#include "Nodes/Node.h"

#include <SDL3/SDL_render.h>
#include <SDL3/SDL.h>

#include <optional>

void VectorRendererComponent::OnDraw(SDL_Renderer* renderer) {
	color.SetRenderDrawColor(renderer);

	std::optional<Vector2> last;

	for (Vector2 point : points) {
		Vector2 local = point * scale;
		Vector2 rotated = local.RotateAround(Vector2::Zero, node->globalRotation);
		Vector2 world = rotated + node->globalPosition;

		if (last.has_value()) {
			SDL_RenderLine(renderer, last->x, last->y, world.x, world.y);
		}

		last = world;
	}
}
