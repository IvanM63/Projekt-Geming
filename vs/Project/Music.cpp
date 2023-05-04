#include "Music.h"

using namespace Engine;

Music::Music(const char* path)
{
	music = Mix_LoadMUS(path);
}

Music::~Music()
{
	Mix_FreeMusic(music);
}

bool Music::IsPaused()
{
	return Mix_PausedMusic() == 1;
}

bool Music::IsPlaying()
{
	return Mix_PlayingMusic() == 1;
}

void Engine::Music::Play(bool loop)
{
	Mix_PlayMusic(music, loop ? -1 : 0);
}

void Music::Pause()
{
	Mix_PauseMusic();
}

void Music::Resume()
{
	Mix_ResumeMusic();
}

void Music::Stop()
{
	Mix_HaltMusic();
}

void Engine::Music::SetVolume(int volume)
{
	this->volume = volume;
	Mix_VolumeMusic(volume * 128 / 100);
}
