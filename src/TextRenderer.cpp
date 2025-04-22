#include "TextRenderer.h"

#include <SDL3_ttf/SDL_ttf.h>
#include <DataTypes.h>

const std::map<DefaultFont, const char*> fontFiles = {
    {FONT_DEBUG, "C:\\WINDOWS\\FONTS\\ARIAL.TTF"}
};

TextRenderer::TextRenderer() {
    if (!TTF_Init()) {
        SDL_Log("Couldn't initialize SDL_ttf: %s\n", SDL_GetError());
        return;
    }
}

void TextRenderer::DrawText(SDL_Renderer* renderer, DefaultFont font, Vector2 position, float scale, Color3 color, const char* text) {
    if (!fontCache.contains(font)) {
        const char* file = fontFiles.at(font);

        TTF_Font* ttfFont = TTF_OpenFont(file, 8);
        if (!ttfFont) {
            SDL_Log("Couldn't open font: %s\n", SDL_GetError());
            return;
        }

        fontCache[font] = ttfFont;
    }

    SDL_Surface* surface = nullptr;
    SDL_Texture* texture = nullptr;

    surface = TTF_RenderText_Blended(fontCache[font], text, 0, color.SDL_Color());
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
