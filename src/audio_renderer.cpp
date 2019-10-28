#include "audio_renderer.h"


AudioSource::AudioSource()
{
	source = 0;
	
	
	occupied = false;
}

void AudioSource::InitSource()
{
	 /* Create the source to play the sound with. */
	alGenSources(1, &source); //allocate source 
	alSourcei(source, AL_SOURCE_RELATIVE, AL_TRUE);
    
	alSourcef(source, AL_PITCH, 1); //how fast the sound is playing, 1 = normal speed
	alSourcef(source, AL_GAIN, 1); //
	alSource3f(source, AL_POSITION, 0, 0, 0); //source position is at the origin
	alSource3f(source, AL_VELOCITY, 0, 0, 0); //source is not moving
	alSourcei(source, AL_LOOPING, AL_FALSE); //loop the audio that source is playing
}

bool AudioSource::IsOccupied(){return occupied;}

void AudioSource::playSoundXZPlane(float& x, float& y, ALuint* buffer)
{
	occupied = true;
	
	//2d only using xz plane
	alSource3f(source, AL_POSITION, x, 0, y);
	
	//set buffer to source that is playing sound
    alSourcei(source, AL_BUFFER, (ALint)*buffer);
    assert(alGetError()==AL_NO_ERROR && "Failed to setup sound source");
    
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
	m_camera_ptr = nullptr;
	
	for(size_t i = 0; i < source_pool.size(); i++)
	{
		source_pool[i].InitSource();
	}
}

AudioRenderer::~AudioRenderer()
{
	m_camera_ptr = nullptr;
}
	

void AudioRenderer::renderAudio(float& x, float& y, ALuint* buffer)
{
	//find an available source to play
	
	for(size_t i=0; i < source_pool.size(); i++)
	{
		if(!source_pool[i].IsOccupied())
		{
			//convert to relative coordinates
			float relX = x - m_camera_ptr->x - m_camera_ptr->w/2;
			float relY = y - m_camera_ptr->y  - m_camera_ptr->h/2;
			
			relX = 4*x / m_camera_ptr->w;
			relY = 4*y / m_camera_ptr->h;
			
			source_pool[i].playSoundXZPlane(relX,relY,buffer);
		}
	}
}

void AudioRenderer::SetPointerToCamera(SDL_Rect* camera)
{
	m_camera_ptr = camera;
}

SDL_Rect* AudioRenderer::GetPointerToCamera()
{
	return m_camera_ptr;
}
