#ifndef AUDIO_RENDERER_H
#define AUDIO_RENDERER_H

#include "globalvariables.h"

//Uses OpenAL Soft and assumes OpenAL Soft system is initialized

class AudioSource
{
public:
	AudioSource();
	~AudioSource();
	
	//function to tell if source is being used
	bool IsOccupied();
	
	//function to play a buffer with a source
	void playSoundXZPlane(float& x, float& y, ALuint* buffer);
	
private:
	ALuint source;
	bool occupied;
	
};

class AudioRenderer
{

public:
	AudioRenderer();
	~AudioRenderer();
	
	//function to play buffer at a position x,y,z
	void renderAudio(float& x, float& y, ALuint* buffer);
	
private:
	std::array <AudioSource,10> source_pool;
	
};

#endif
