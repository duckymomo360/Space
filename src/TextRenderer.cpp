#include "TextRenderer.h"

#include <SDL3_ttf/SDL_ttf.h>
#include <DataTypes.h>

const std::map<DefaultFont, const char*> fontFiles = {
    {FONT_DEBUG, "data/FONT/Roboto-Regular.ttf"}
};

TextRenderer::TextRenderer() {
    if (!TTF_Init()) {
        SDL_Log("Couldn't initialize SDL_ttf: %s\n", SDL_GetError());
        return;
    }
}

void TextRenderer::DrawText(SDL_Renderer* renderer, DefaultFont font, Vector2 position, float scale, Color3 color, const char* fmt, ...) {
    if (!fontCache.contains(font)) {
        const char* name = fontFiles.at(font);
        TTF_Font* ttfFont = TTF_OpenFont(name, 8.0f);
        if (!ttfFont) {
            SDL_Log("Couldn't open font: %s\n", SDL_GetError());
            return;
        }

        fontCache[font] = ttfFont;
    }

	char buffer[256];
	va_list args;
	va_start(args, fmt);
    vsnprintf_s(buffer, sizeof(buffer), fmt, args);
	va_end(args);

    SDL_Texture* texture = nullptr;
    SDL_Surface* surface = TTF_RenderText_Blended(fontCache[font], buffer, 0, color.SDL_Color());
    if (surface) {
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_DestroySurface(surface);
    }

    if (!texture) {
        SDL_Log("Couldn't create text: %s\n", SDL_GetError());
        return;
    }

    SDL_FRect dst;

    SDL_GetTextureSize(texture, &dst.w, &dst.h);
    dst.x = position.x;
    dst.y = position.y;

    dst.w *= scale;
    dst.h *= scale;

    /* Draw the text */
    SDL_RenderTexture(renderer, texture, NULL, &dst);
}
