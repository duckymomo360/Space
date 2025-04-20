#include "VectorRenderer.h"
#include "Nodes/Node.h"

#include <SDL3/SDL_render.h>
#include <SDL3/SDL.h>

#include <optional>

void VectorRendererComponent::Draw(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	std::optional<Vector2> last;

	for (Vector2 point : points) {
		Vector2 local = point * scale;
		Vector2 rotated = local.RotateAround(Vector2::Zero, node->rotation);
		Vector2 world = rotated + node->position;

		if (last.has_value()) {
			SDL_RenderLine(renderer, last->x, last->y, world.x, world.y);
		}

		last = world;
	}
}
