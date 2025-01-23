#pragma once
#include "PreCompiledHeader/PreCompiledHeader.h"

class SoundManager
{
public:
	SoundManager() = default;
	~SoundManager() = default;

	static void Init_FMOD();
	static void Play(std::string _filename);
	static void Pause(FMOD::Sound& _sound);
	static void Resume(FMOD::Sound& _sound);
	static void Stop(FMOD::Sound& _sound);


private:
	FMOD::System* system = nullptr;

};
