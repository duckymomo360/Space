#include "KeyboardInputManager.h"

#include <SDL3/SDL_events.h>
#include <SDL3/SDL_log.h>

void KeyboardInputManager::ProcessEvent(SDL_Event& e) {
	switch (e.type) {
	case SDL_EVENT_KEY_DOWN:
		state |=  (1ULL << e.key.scancode);
		break;
	case SDL_EVENT_KEY_UP:
		state &= ~(1ULL << e.key.scancode);
		break;
	}
}

bool KeyboardInputManager::IsKeyDown(SDL_Scancode sc) {
	return state & (1ULL << sc);
}
