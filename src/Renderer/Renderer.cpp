#include "Renderer/Renderer.h"

#include "Game.h"
#include "DataTypes.h"
#include "Nodes/Camera.h"

#include <SDL3/SDL_render.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <vector>
#include <format>

const char* fontFiles[FONT_COUNT] = {
	"data/FONT/Roboto-Regular.ttf", // FONT_DEBUG
};

std::vector<std::weak_ptr<CachedFont>> fontCache;

Renderer::Renderer(SDL_Window* sdlWindow)
{
	sdlRenderer = SDL_CreateRenderer(sdlWindow, NULL);

	if (!sdlRenderer)
	{
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
		return;
	}

	SDL_SetRenderVSync(sdlRenderer, 1);

	if (!TTF_Init())
	{
		SDL_Log("Failed to init TTF: %s", SDL_GetError());
		return;
	}
}

Renderer::~Renderer()
{
	SDL_DestroyRenderer(sdlRenderer);
}

void Renderer::ToCameraSpace(Vector2& vector) const
{
	if (currentCamera)
	{
		vector.x -= currentCamera->globalPosition.x;
		vector.y -= currentCamera->globalPosition.y;
	}
}

void Renderer::DrawRendererDebugInfo() const
{
	static auto debugFont = GetCachedFont(FONT_DEBUG, 16.0f);
	RenderText(std::format("LOADED FONTS: {}", fontCache.size()), { 0.0f, 400.0f }, Vector2::Zero, Color4::Blue, debugFont, 1.0f);
}

void Renderer::Clear(Color4 color) const
{
	SDL_SetRenderDrawColor(sdlRenderer, color.g, color.g, color.b, color.a);
	SDL_RenderClear(sdlRenderer);
}

void Renderer::Present() const
{
	if (gGame.debug)
	{
		DrawRendererDebugInfo();
	}

	SDL_RenderPresent(sdlRenderer);
}

void Renderer::RenderLine(Vector2 point1, Vector2 point2, Color4 color) const
{
	ToCameraSpace(point1);
	ToCameraSpace(point2);

	SDL_SetRenderDrawColor(sdlRenderer, color.r, color.g, color.b, color.a);
	SDL_RenderLine(sdlRenderer, point1.x, point1.y, point2.x, point2.y);
}

void Renderer::RenderPoint(Vector2 point, Color4 color) const
{
	ToCameraSpace(point);

	SDL_SetRenderDrawColor(sdlRenderer, color.r, color.g, color.b, color.a);
	SDL_RenderPoint(sdlRenderer, point.x, point.y);
}

void Renderer::RenderCircle(Vector2 origin, float radius, Color4 color) const
{
	ToCameraSpace(origin);
}

struct CachedFont
{
	EngineFont font;
	float      pointSize;
	TTF_Font* sdlFont;

	inline bool IsValid()
	{
		return pointSize > 0.0f && sdlFont != NULL;
	}

	~CachedFont()
	{
		TTF_CloseFont(sdlFont);
	}
};

std::shared_ptr<CachedFont> Renderer::GetCachedFont(EngineFont font, float pointSize) const
{
	std::shared_ptr<CachedFont> cachedFont;

	for (auto it = fontCache.begin(); it < fontCache.end();)
	{
		if (it->expired())
		{
			it = fontCache.erase(it);
			continue;
		}

		cachedFont = it->lock();

		if (cachedFont->font == font && cachedFont->pointSize == pointSize)
		{
			return cachedFont;
		}

		++it;
	}

	cachedFont = std::make_shared<CachedFont>();
	cachedFont->font = font;
	cachedFont->pointSize = pointSize;
	cachedFont->sdlFont = TTF_OpenFont(fontFiles[font], pointSize);

	if (!cachedFont->sdlFont)
	{
		SDL_Log("Font failed to load: %s %.1f %s", fontFiles[font], pointSize, SDL_GetError());
	}

	if (cachedFont->IsValid())
	{
		fontCache.push_back(cachedFont);
		SDL_Log("Font cached: %s %.1f", fontFiles[font], pointSize);
	}

	return cachedFont;
}

void Renderer::RenderText(
	const std::string& text,
	Vector2 position,
	Vector2 anchor,
	Color4  color,
	std::shared_ptr<CachedFont> cachedFont,
	float renderScale) const
{
	if (!cachedFont->IsValid())
	{
		SDL_Log("Font is invalid: %s %.1f", fontFiles[cachedFont->font], cachedFont->pointSize);
		return;
	}

	SDL_Surface* surface = TTF_RenderText_Blended(cachedFont->sdlFont, text.c_str(), text.length(), { color.r, color.g, color.b, color.a });
	if (!surface)
	{
		SDL_Log("Couldn't create text: %s\n", SDL_GetError());
		return;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(sdlRenderer, surface);

	SDL_DestroySurface(surface);

	if (!texture)
	{
		SDL_Log("Couldn't create text: %s\n", SDL_GetError());
		return;
	}

	ToCameraSpace(position);

	SDL_FRect dst;
	SDL_GetTextureSize(texture, &dst.w, &dst.h);
	dst.x = position.x;
	dst.y = position.y;

	dst.w *= renderScale;
	dst.h *= renderScale;

	SDL_RenderTexture(sdlRenderer, texture, NULL, &dst);

	SDL_DestroyTexture(texture);
}
