#include "VectorRenderer.h"

#include "Renderer.h"
#include "Nodes/Node.h"

#include <optional>

int VectorRendererComponent::FindNearestPointIndex(const Vector2& point, float maxDistance)
{
	int nearestPointIndex = -1;

	for (int index = 0; index < points.size(); ++index) {
		if (float distance = point.DistanceFrom(points[index]); distance < maxDistance) {
			maxDistance = distance;
			nearestPointIndex = index;
		}
	}

	return nearestPointIndex;
}

void VectorRendererComponent::OnDraw(Renderer* renderer)
{
	std::optional<Vector2> last;

	for (Vector2 point : points) {
		Vector2 local = point * scale;
		Vector2 rotated = local.RotateAround(Vector2::Zero, node->globalRotation);
		Vector2 world = rotated + node->globalPosition;

		if (last.has_value()) {
			renderer->RenderLine(last.value(), world, color);
		}

		last = world;
	}
}
