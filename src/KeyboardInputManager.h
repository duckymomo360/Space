#pragma once
#include <stdint.h>

union SDL_Event;
enum SDL_Scancode;

class KeyboardInputManager {
	uint64_t state = 0;

public: // Handlers
	void ProcessEvent(SDL_Event& e);

public: // Public API
	bool IsKeyDown(SDL_Scancode sc);
};