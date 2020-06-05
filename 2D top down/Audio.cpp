#include "Audio.h"
#include "Debug.h"

Sound::Sound()
{
	Clear();
}

void Sound::Clear()
{
	name = "";
}

bool Sound::Load(std::string fileLoc, std::string name)
{
	Clear();
	return false;
}

void Sound::Play()
{

}

void Sound::Pause()
{

}

void Sound::Unpause()
{

}

void Sound::Stop()
{

}

Music::Music()
{
	Clear();
}

Music::~Music()
{
	Clear();
}

void Music::Clear()
{
	name = "";
	if (sound != nullptr)
	{
		Mix_FreeMusic(sound);
		sound = nullptr;
	}
}

bool Music::Load(std::string fileLoc, std::string name)
{
	sound = Mix_LoadMUS(fileLoc.c_str());
	if (sound != nullptr)
	{
		this->name = name;
		return true;
	}

	Clear();

	return false;
}

void Music::Play()
{
	if (Mix_PlayingMusic() == 0)
		Mix_PlayMusic(sound, -1);
	else if (Mix_PausedMusic() == 1)
		Unpause();
	else
		Pause();
}

void Music::Pause()
{
	Mix_PauseMusic();
}

void Music::Unpause()
{
	Mix_ResumeMusic();
}

void Music::Stop()
{
	Mix_HaltMusic();
}

Chunk::Chunk()
{
	Clear();
}

Chunk::~Chunk()
{
	Clear();
}

void Chunk::Clear()
{
	name = "";
	channel = 0;
	if (sound != nullptr)
	{
		Mix_FreeChunk(sound);
		sound = nullptr;
	}
}

bool Chunk::Load(std::string fileLoc, std::string name)
{
	sound = Mix_LoadWAV(fileLoc.c_str());
	if (sound != nullptr)
	{
		this->name = name;
		return true;
	}

	Clear();

	return false;
}

void Chunk::Play()
{
	channel = Mix_PlayChannel(-1, sound, 0);
}

// TODO: pause/unpause/halt sound chunks
/*
void Chunk::Pause()
{
	if (Mix_ChannelFinished)
	Mix_Pause(channel);
}

void Chunk::Unpause()
{
	Mix_Resume(channel);
}

void Chunk::Stop()
{
	Mix_HaltChannel(channel);
}*/

void Sounds::Cleanup()
{
	for (auto& sound : soundList)
		sound->Clear();

	debug.Log("Sounds", "Cleanup", "Destroyed all sounds");
}

Sound* Sounds::GetSound(std::string name)
{
	for (auto& sound : soundList)
		if (sound->Name() == name)
			return sound;

	return nullptr;
}

Sound* Sounds::CreateSound(std::string fileLoc, std::string name)
{
	Sound* sound = new Sound();
	if (!sound->Load(fileLoc, name))
	{
		delete sound;
		return nullptr;
	}

	soundList.push_back(sound);

	return soundList.back();
}

void Sounds::DeleteSound(std::string name)
{
	int i = 0;
	for (auto& tex : soundList)
		if (tex->Name() == name)
		{
			soundList.erase(soundList.begin() + i);
			break;
		}
		else
			i++;
}