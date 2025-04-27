#include "Registry.h"
#include "Game.h"

#include <SDL3/SDL_main.h>

int main(int argc, char* argv[])
{
	Registry::Initialize();
	gGame.Run();
	return 0;
}