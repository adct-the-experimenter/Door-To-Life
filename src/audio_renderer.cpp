#include "audio_renderer.h"


AudioRenderer::AudioRenderer()
{
	m_camera_ptr = nullptr;
	
	//source_pool.resize(10);
	
	//for(size_t i = 0; i < source_pool.size(); i++)
	//{
	//	source_pool[i].InitSource();
	//}
	
	playerHeight = 0;
}

AudioRenderer::~AudioRenderer()
{
	m_camera_ptr = nullptr;
	
	if(source_pool != 0)
	{
		alDeleteSources(1, &source_pool);
	}
	
}
	
bool AudioRenderer::InitSourcePool()
{
	return AudioRenderer::InitThisSource(&source_pool);
	
}	

bool AudioRenderer::InitThisSource(ALuint* source)
{
	alGetError();
	
	//initialize source
	alGenSources(1, source);
	alSourcei(*source, AL_SOURCE_RELATIVE, AL_FALSE);
	
	ALenum test_error_flag = alGetError();
	if(test_error_flag != AL_NO_ERROR)
	{
		std::cout << "\nError found in audio source init" << ": " << alGetString(test_error_flag) << "\n";
		return false;
	}
	
	return true;
}

void AudioRenderer::renderAudio(float& x, float& y, ALuint* buffer)
{
	//find an available source to play
	
	//for(size_t i=0; i < source_pool.size(); i++)
	//{
		//if(!source_pool[i].IsOccupied())
		//{
			//convert to relative coordinates
			float relX = x - m_camera_ptr->x - m_camera_ptr->w/2;
			float relY = y - m_camera_ptr->y  - m_camera_ptr->h/2;
			
			relX = 4*relX / m_camera_ptr->w;
			relY = 4*relY / m_camera_ptr->h;
			
			AudioRenderer::playSoundXZPlane(&source_pool,relX,relY,buffer);
		//}
	//}
}

void AudioRenderer::playSoundXZPlane(ALuint* source, float& x, float& y, ALuint* buffer)
{
	//2d only using xz plane
	alSource3f(*source, AL_POSITION, x, 0, y);
	
	//attach buffer to source
    alSourcei(*source, AL_BUFFER, (ALint)(*buffer));
    	
    ALenum test_error_flag = alGetError();
	if(test_error_flag != AL_NO_ERROR)
	{
		//std::cout << "\nError found in attaching buffer to source:" << alGetString(test_error_flag) << "\n";
		return;
	}
	
    //play source
    ALint state;
    alGetSourcei(*source, AL_SOURCE_STATE, &state);
    
    if(state == AL_INITIAL || state == AL_STOPPED)
    {
		alSourcePlay(*source);
	}
	
	
	//detach buffer from source
	alSourcei(*source, AL_BUFFER, NULL);
}



void AudioRenderer::renderAudioRelativeToPlayerHeight(float& x, float& y,  int& height, ALuint* buffer)
{
	//convert to relative coordinates
	float relX = x - m_camera_ptr->x - m_camera_ptr->w/2;
	float relY = y - m_camera_ptr->y  - m_camera_ptr->h/2;
	
	relX = 4*relX / m_camera_ptr->w;
	relY = 4*relY / m_camera_ptr->h;
	
	AudioRenderer::playSoundXZPlaneHeightY(&source_pool,relX,relY,height,buffer);
}

void AudioRenderer::playSoundXZPlaneHeightY(ALuint* source,float& x, float& y, int& height, ALuint* buffer)
{
	float diff = (height - playerHeight) / 10;
	
	//2d only using xz plane
	alSource3f(*source, AL_POSITION, x, diff, y);
	
	//attach buffer to source
    alSourcei(*source, AL_BUFFER, (ALint)(*buffer));
    	
    ALenum test_error_flag = alGetError();
	if(test_error_flag != AL_NO_ERROR)
	{
		//std::cout << "\nError found in attaching buffer to source:" << alGetString(test_error_flag) << "\n";
		return;
	}
	
    //play source
    ALint state;
    alGetSourcei(*source, AL_SOURCE_STATE, &state);
    
    if(state == AL_INITIAL || state == AL_STOPPED)
    {
		alSourcePlay(*source);
	}
	
	//detach buffer from source
	alSourcei(*source, AL_BUFFER, NULL);
}

void AudioRenderer::SetPointerToCamera(SDL_Rect* camera)
{
	m_camera_ptr = camera;
}

SDL_Rect* AudioRenderer::GetPointerToCamera()
{
	return m_camera_ptr;
}

void AudioRenderer::SetPlayerHeight(int& height)
{
	playerHeight = height;
}
