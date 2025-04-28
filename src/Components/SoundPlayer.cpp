#include "SoundPlayer.h"

#include <SDL3/SDL_log.h>

void SoundPlayerComponent::Play()
{
	if (!loaded && !PreloadWAV())
	{
		SDL_Log("Failed to load audio");
		return;
	}

	stream = SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &audioSpec, NULL, NULL);

	if (!stream)
	{
		SDL_Log("Failed to create audio stream: %s", SDL_GetError());
		return;
	}

	if (!SDL_ResumeAudioStreamDevice(stream))
	{
		SDL_Log("Failed to resume audio stream device: %s", SDL_GetError());
		return;
	}

	if (!SDL_PutAudioStreamData(stream, audioBuffer, audioLength))
	{
		SDL_Log("Failed to put audio stream data: %s", SDL_GetError());
		return;
	}

	SDL_Log("Audio should now be playing");
}

bool SoundPlayerComponent::PreloadWAV()
{
	if (!wavPath)
	{
		SDL_Log("wavPath is null");
		return;
	}

	if (!loaded && SDL_LoadWAV(wavPath, &audioSpec, &audioBuffer, &audioLength))
	{
		loaded = true;
	}

	if (!loaded)
	{
		SDL_Log("Failed to load audio: %s", SDL_GetError());
		return;
	}

	return loaded;
}

void SoundPlayerComponent::OnAttached()
{
}

void SoundPlayerComponent::OnDetached()
{
}
