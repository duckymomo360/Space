#pragma once

#include <string>
#include <memory>

struct SDL_Renderer;
struct SDL_Window;

class Vector2;
class Color4;

enum EngineFont : uint8_t {
	FONT_DEBUG,
	FONT_COUNT,
};

class CachedFont;

class Renderer
{
	SDL_Renderer* sdlRenderer = nullptr;

public:
	Renderer(SDL_Window* sdlWindow);

	~Renderer();

	void DrawRendererDebugInfo();

	void Clear(Color4 color);

	void Present();

	void RenderLine(Vector2 point1, Vector2 point2, Color4 color) const;

	void RenderPoint(Vector2 point, Color4 color) const;

	void RenderCircle(Vector2 origin, float radius, Color4 color) const;

	std::shared_ptr<CachedFont> GetCachedFont(EngineFont font, float pointSize) const;

	void RenderText(
		const std::string& text,
		Vector2 position,
		Vector2 anchor,
		Color4  color,
		std::shared_ptr<CachedFont> cachedFont,
		float renderScale = 1.0f) const;
};
