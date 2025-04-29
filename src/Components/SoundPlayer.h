#pragma once

#include "Component.h"

#include <SDL3/SDL_audio.h>
#include <cstdint>

class SoundPlayerComponent : public Component
{
	using Component::Component;

	SDL_AudioStream* stream;
	SDL_AudioSpec audioSpec;
	uint8_t* audioBuffer;
	uint32_t audioLength;

public:
	const char* wavPath = nullptr;

	bool playing = false;

	bool loaded = false;

	void Play();

	void Stop();

	bool PreloadWAV();

	void OnAttached() override;

	void OnDetached() override;
};
