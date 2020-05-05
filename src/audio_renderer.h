#ifndef AUDIO_RENDERER_H
#define AUDIO_RENDERER_H

#include "globalvariables.h"

//Uses OpenAL Soft and assumes OpenAL Soft system is initialized

struct AudioSource
{
	ALuint openal_source = 0;
	bool occupied = false;
};

class AudioRenderer
{

public:
	AudioRenderer();
	~AudioRenderer();
	
	//function to initialize audio renderer source pool
	bool InitSourcePool();
	
	//function to free audio renderer source pool
	void FreeSourcePool();
	
	//function to play buffer at a position x,y
	void renderAudio(float& x, float& y, ALuint* buffer);
	
	//function to play buffer at a position x,y with height of player taken into account.
	//enemies shorter than player will make sound that is heard below player.
	//enmies taller than player will make sound that is heard above player
	void renderAudioRelativeToPlayerHeight(float& x, float& y,int& height, ALuint* buffer);
	
	void SetPointerToCamera(SDL_Rect* camera);
	SDL_Rect* GetPointerToCamera();
	
	void SetPlayerHeight(int& height);
	
private:

	std::array <AudioSource,10> source_pool;
	
	SDL_Rect* m_camera_ptr;
	
	//function to play a buffer with a source in 2.5D space
	void playSoundXZPlane(ALuint* source,float& x, float& y, ALuint* buffer);
	
	//function to play a buffer with a source in 3D space
	void playSoundXZPlaneHeightY(ALuint* source,float& x, float& y, int& height, ALuint* buffer);
	
	int playerHeight;
	
};

#endif
