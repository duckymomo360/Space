#include <map>

struct SDL_Renderer;
struct TTF_Font;
struct SDL_Color;
struct Vector2;
struct Color3;

enum DefaultFont : char {
	FONT_DEBUG = 0,
};

class TextRenderer {
	std::map<DefaultFont, TTF_Font*> fontCache;

public:
	TextRenderer();

	void DrawText(SDL_Renderer* renderer, DefaultFont font, Vector2 position, float scale, Color3 color, const char* fmt, ...);
};
