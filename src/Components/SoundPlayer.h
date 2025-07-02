#pragma once

#include "Component.h"

#include <SDL3/SDL_audio.h>
#include <cstdint>

class SoundPlayerComponent : public Component
{
	using Component::Component;

	SDL_AudioStream* stream{ nullptr };
	SDL_AudioSpec audioSpec;
	uint8_t* audioBuffer{ nullptr };
	uint32_t audioLength{ 0 };

public:
	const char* wavPath = nullptr;

	bool playing = false;

	bool loaded = false;

	void Play();

	void Stop();

	bool PreloadWAV();

	void OnStart() override;

	void OnStop() override;
};
