#ifndef AUDIO_RENDERER_H
#define AUDIO_RENDERER_H

#include "globalvariables.h"

//Uses OpenAL Soft and assumes OpenAL Soft system is initialized

struct AudioSource
{
	ALuint* sourcePtr;
	bool occupied;
};

class AudioRenderer
{

public:
	AudioRenderer();
	~AudioRenderer();
	
	//function to initialize audio renderer source pool
	bool InitSourcePool();
	
	//function to play buffer at a position x,y,z
	void renderAudio(float& x, float& y, ALuint* buffer);
	
	void SetPointerToCamera(SDL_Rect* camera);
	SDL_Rect* GetPointerToCamera();
	
private:
	//std::array <ALuint,10> source_pool;
	ALuint source_pool;
	SDL_Rect* m_camera_ptr;
	
	bool InitThisSource(ALuint* source);
	
	//function to play a buffer with a source in 2.5D space
	void playSoundXZPlane(ALuint* source,float& x, float& y, ALuint* buffer);
};

#endif
