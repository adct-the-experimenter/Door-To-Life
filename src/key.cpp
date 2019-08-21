#include "key.h"

bool loadKeyMedia(SDL_Renderer* gRenderer,LTexture* keyTexture,ALuint* source,ALuint* buffer)
{
    bool success = true;
    
    //initialize key image
    std::string keyTexFilePath = DATADIR_STR + std::string("/Graphics/key-draw.png");
    if(!keyTexture->loadFromFile(keyTexFilePath.c_str(),gRenderer) )
    {
        success = false;
        std::cout << "key image loading failed! \n";
    }

    //initialize key sound media
    std::string keySoundFilePath = DATADIR_STR + std::string("/Sound/Pickup_Key.wav");
    Mix_Chunk* keyPickupSoundMedia = Mix_LoadWAV(keySoundFilePath.c_str());
    if(keyPickupSoundMedia == nullptr)
    {
        success = false;
        printf( "Failed to load key pickup sound effect! %s\n", Mix_GetError() );
    }
    else
    {
         //setup source of dungeon music
        alGenSources(1, source); //allocate source 

        alSourcef(*source, AL_PITCH, 1); //how fast the sound is playing, 1 = normal speed
        alSourcef(*source, AL_GAIN, 1); //
        alSource3f(*source, AL_POSITION, 0, 0, 0); //source position is at the origin
        alSource3f(*source, AL_VELOCITY, 0, 0, 0); //source is not moving
        alSourcei(*source, AL_LOOPING, AL_FALSE); //loop the audio that source is playing
        
        //setup buffer of dungeon music
        
        //allocate buffer
        alGenBuffers(1, buffer);
        //transfer Mix_Chunk data and length to OpenAL buffer
        alBufferData(*buffer, AL_FORMAT_STEREO16, keyPickupSoundMedia->abuf, keyPickupSoundMedia->alen, 44100); 
        //set buffer to source that is playing sound
        alSourcei(*source, AL_BUFFER, *buffer);
        
        //free dungeon music media
        Mix_FreeChunk(keyPickupSoundMedia);
        keyPickupSoundMedia = nullptr;
    }
    
    return success;
}

void freeKeyMedia(LTexture* keyTexture,ALuint* source,ALuint* buffer)
{
    //free source
    alDeleteSources(1, source); // delete source
    //free buffer
	alDeleteBuffers(1, buffer); //delete buffer
    //free tile texture map
    keyTexture->free();
}


void setupNewKeyObject(Key** thisKey,LTexture* keyTexture,ALuint* source,ALuint* buffer)
{
    *thisKey = new Key();
    (*thisKey)->setPointersToMedia(keyTexture,source,buffer);
}

Key::Key()
{
    //initialize collision box dimensions
    collisionBox.x=0;
    collisionBox.y=0;
    collisionBox.w= KEY_WIDTH;
    collisionBox.h= KEY_HEIGHT;

    //initialize hasKey bool
    hasKey = false;
}

Key::~Key()
{
    //set hasKey bool backto false
    hasKey = false;

    //set collision box to null
    collisionBox.x=0; collisionBox.y=0; collisionBox.w=0; collisionBox.h=0;

}

void Key::setKeyPosition(int x, int y)
{
    collisionBox.x = x;
    collisionBox.y = y;
}

void Key::setKeyBool(bool state){hasKey = state;}

bool Key::getKeyBool(){return hasKey;}

void Key::playSound()
{
    //if key picked up and count is
    //if(hasKey == true )
    //{
        //play key sound effect
        //Mix_PlayChannel(-1,keyPickUpSound,0);
        alSourcePlay(*keySource);
    //}

}

void Key::setPointersToMedia(LTexture* keyTexture,ALuint* source,ALuint* buffer)
{
    keyImage = keyTexture;
    keyPickUpBuffer = buffer; 
    keySource = source;
}

void Key::render(SDL_Rect& camera, SDL_Renderer* lRenderer)
{
    if(hasKey == false)
    {
        keyImage->render( collisionBox.x - camera.x, collisionBox.y - camera.y, lRenderer);
    }
    else {}
}

SDL_Rect& Key::getCollisionBox()
{
    return collisionBox;
}
