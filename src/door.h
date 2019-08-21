#ifndef DOOR_H
#define DOOR_H

#include "globalvariables.h"
#include "key.h"

#include "dot_final.h"

#include <cstdint>


class Door
{
    
public:

    friend bool loadDoorMedia(SDL_Renderer* gRenderer,
                            LTexture* doorTexture,
                            ALuint* source,
                            ALuint* doorBufferOpen, 
                            ALuint* doorBufferFail,
                            std::vector <SDL_Rect> &doorClips);
    
    friend void freeDoorMedia(
                            LTexture* doorTexture,
                            ALuint* source,
                            ALuint* doorBufferOpen, 
                            ALuint* doorBufferFail);
                            
    friend void setupNewDoorObject(Door** thisDoor,
                            LTexture* doorTexture,
                            ALuint* source,
                            ALuint* doorBufferOpen, 
                            ALuint* doorBufferFail,
                            std::vector <SDL_Rect> *ptrDoorClips);

    //constructor
    Door();
    //desturctor
    ~Door();
    
    void setLock(Key* thisKey);

    static const int DOOR_WIDTH = 40;
    static const int DOOR_HEIGHT = 80;

    void setPointersToMedia(LTexture* doorTexture,
                            ALuint* source,
                            ALuint* doorBufferOpen, 
                            ALuint* doorBufferFail,
                            std::vector <SDL_Rect> *ptrDoorClips);
                            
    //Type of door
    enum class Type : std::int8_t { NO_LOCK_DOOR = 0,LOCK_DOOR,WINNER_DOOR };
    void setDoorType(Door::Type type);
    Door::Type getDoorType();
    
    //state of door                        
    enum class State : std::int8_t {DOOR_CLOSED = 0, DOOR_OPEN_FAIL, DOOR_OPEN};
    void setDoorState(Door::State state);
    Door::State getDoorState();
    
    //state of sound door is making
    enum class SoundState : std::int8_t {PLAY_DOOR_OPEN = 0,PLAY_DOOR_OPEN_KEY,
                                        PLAY_DOOR_FAIL, NO_SOUND};
    
    
    
//Game Loop Functions
    //checks if space was pressed, if yes then keyInsert is true
    void handle_event(Event& thisEvent);
    //plays sounds
    void playSounds();
    //show door on screen
    void render(SDL_Rect& camera, SDL_Renderer* gRenderer);


//Setup Functions

    void setPointersToMedia(LTexture* doorTexture,        
                            Mix_Chunk* doorOpenSound,
                            Mix_Chunk* doorFailSound,
                            std::vector <SDL_Rect> *ptrDoorClips);
    
    //functions to place door
    void placeDoor1(std::int16_t& x, std::int16_t& y);
    void placeDoor2(std::int16_t& x,std::int16_t& y);
    
    //set bool for open door if it is true
    void openDoorLogic();
    
    enum class DoorCollided : std::int8_t {NONE = 0, DOT_TO_DOOR1,DOT_TO_DOOR2};
    Door::DoorCollided getDoorCollidedState();
    
    friend bool checkDotCollidesWithDoor(Door* thisDoor, Dot* mainDot);

    //set door open attempt fail bool
    void setDoorOpenAttemptFail(bool state);

    //return if space was pressed to insert key or not
    bool getKeyInsertStatus();
    //return if door is open or not
    bool getDoorOpenStatus();

    //return collision box of door
    SDL_Rect& getCollisionBoxDoor1();
    SDL_Rect& getCollisionBoxDoor2();
    
    void resetDoorsToClose();
    
private:

    //Type of door
    Door::Type doorType;

    //state of door
    Door::State doorState;

    //pointer to key for door
    Key* doorKey;

    //bool if key is inserted
    bool keyInsert;
    void setKeyInsertStatus(bool state);
    //collision boxes for door
    SDL_Rect collisionBoxDoor1;
    SDL_Rect collisionBoxDoor2;
    
    //image of door
    LTexture* doorImage;

    //door sounds
   //sound effect for door
    ALuint* doorSource;
    ALuint* doorOpenBuffer; 
    ALuint* doorFailBuffer;
    Door::SoundState doorSoundState;
    void setSoundState(Door::SoundState thisState);
    Door::SoundState getSoundState();
    
    //which door is being collided with
    Door::DoorCollided doorCollideState;
    
    //function to open door if it has lock
    void openDoorLogicWithLock();
    void openDoorLogicNoLock();
    
    std::vector <SDL_Rect> *doorClips;
    
    SDL_Rect* renderRectClip;
    
   
};

#endif
