#include "key.h"

bool loadKeyMedia(SDL_Renderer* gRenderer,LTexture* keyTexture,ALuint* source,ALuint* buffer)
{
    bool success = true;
    
    //initialize key image
    std::string keyTexFilePath = DATADIR_STR + std::string("/Graphics/key-draw.png");
    if(!keyTexture->loadFromFile(keyTexFilePath.c_str(),gRenderer) )
    {
        
        std::cout << "key image loading failed! \n";
        return false;
    }

   
    std::string path = "/Sound/Pickup_Key.wav";
    if(!LoadBuffer(buffer,path))
    {
		printf("Failed to load key pickup sound! \n");
		return false;
	}
    else
    {
         //setup source of dungeon music
        alGenSources(1, source); //allocate source 

        
        alSource3f(*source, AL_POSITION, 0.0f, 0.0f, 0.0f); //source position is at the origin
        alSource3f(*source, AL_VELOCITY, 0.0f, 0.0f, 0.0f); //source is not moving
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
