#include "audio_renderer.h"


AudioSource::AudioSource()
{
	//setup source
	alGenSources(1, &source); //allocate source 

	alSourcef(source, AL_PITCH, 1); //how fast the sound is playing, 1 = normal speed
	alSourcef(source, AL_GAIN, 1); //
	alSource3f(source, AL_POSITION, 0, 0, 0); //source position is at the origin
	alSource3f(source, AL_VELOCITY, 0, 0, 0); //source is not moving
	alSourcei(source, AL_LOOPING, AL_FALSE); //loop the audio that source is playing
	
	occupied = false;
}

bool AudioSource::IsOccupied(){return occupied;}

void AudioSource::playSoundXZPlane(float& x, float& y, ALuint* buffer)
{
	occupied = true;
	
	//2d only using xz plane
	alSource3f(source, AL_POSITION, x, 0, y);
	
	//set buffer to source that is playing sound
    alSourcei(source, AL_BUFFER, *buffer);
    
    //play source
    ALint state;
    alGetSourcei(source, AL_SOURCE_STATE, &state);
    
	alSourcePlay(source);
	
    
    occupied = false;
}

AudioSource::~AudioSource()
{
	alDeleteSources(1, &source);
}

AudioRenderer::AudioRenderer()
{
	
}

AudioRenderer::~AudioRenderer()
{
	
}
	

void AudioRenderer::renderAudio(float& x, float& y, ALuint* buffer)
{
	//find an available source to play
	
	for(size_t i=0; i < source_pool.size(); i++)
	{
		if(!source_pool[i].IsOccupied())
		{
			source_pool[i].playSoundXZPlane(x,y,buffer);
		}
	}
}
