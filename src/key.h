#ifndef KEY_H
#define KEY_H

#include "globalvariables.h"
#include "LTexture.h"

class Key
{
public:

    friend bool loadKeyMedia(SDL_Renderer* gRenderer,LTexture* keyTexture,
    ALuint* source,ALuint* buffer);
    
    friend void freeKeyMedia(LTexture* keyTexture,ALuint* source,ALuint* buffer);
    
    friend void setupNewKeyObject(Key** thisKey,LTexture* keyTexture,ALuint* source,ALuint* buffer);
    
    Key();
    //destructor
    ~Key();

    //width and height of key
    static const int KEY_WIDTH = 30;
    static const int KEY_HEIGHT = 30;

    //set position for key
    void setKeyPosition(int x, int y);

    //set bool for hasKey
    void setKeyBool(bool state);

    //return bool of hasKey
    bool getKeyBool();

    //play key sound
    void playSound();
    
    //function to load media for key
   void setPointersToMedia(LTexture* keyTexture,ALuint* source,ALuint* buffer);

    //renders key object when not obtained
    void render(SDL_Rect& camera, SDL_Renderer* lRenderer);

    //return collision box for key
    SDL_Rect& getCollisionBox();


private:

    SDL_Rect collisionBox;

    LTexture* keyImage;

    bool hasKey;

    //sound effect for key
    ALuint* keyPickUpBuffer; //buffer for dungeon music 
    ALuint* keySource;//source, what is playing dungeon music
    ALint musicState;
};

#endif
