#include "Sound.h"

Engine::Sound::Sound(const char* path)
{
	sound = Mix_LoadWAV(path);
}

Engine::Sound::~Sound()
{
	Mix_FreeChunk(sound);
}

bool Engine::Sound::IsPlaying()
{
	return Mix_Playing(-1) == 1;
}

void Engine::Sound::Play(bool loop)
{
	Mix_PlayChannel(-1, sound, loop ? -1 : 0);
}

void Engine::Sound::SetVolume(int volume)
{
	this->volume = volume;
	Mix_VolumeChunk(sound, volume * 128 / 100);
}
