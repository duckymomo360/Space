#include <map>

struct SDL_Renderer;
struct TTF_Font;
struct SDL_Color;
struct Vector2;

enum DefaultFont : char {
	FONT_DEBUG = 0,
};

class TextRenderer {
	std::map<DefaultFont, TTF_Font*> fontCache;

public:
	TextRenderer();

	void DrawText(SDL_Renderer* renderer, DefaultFont font, const char* text, Vector2 position, float scale, SDL_Color color);
};
