#include "door.h"


bool loadDoorMedia(SDL_Renderer* gRenderer,
LTexture* doorTexture,
ALuint* source,
ALuint* doorBufferOpen, 
ALuint* doorBufferFail,
std::vector <SDL_Rect> &doorClips)
{
    bool success = true;
    
    //initialize texture for door
    std::string doorTexFilePath = DATADIR_STR + std::string("/Graphics/door-draw.png");
    if(!doorTexture->loadFromFile(doorTexFilePath.c_str(),gRenderer) )
    {
        success = false;
        printf("Failed to load door image! \n");
    }
    else
    {
        doorClips.resize(3);
        
        std::int16_t width = 41;
        std::int16_t height = 80;
        
        doorClips[0] = {20,0,width,height};
        doorClips[1] = {81,0,width,height};
        doorClips[2] = {142,0,width,height};
    }
    
    

    //initialize doors sound effects
  
    std::string path = ("/Sound/Door_Open_Fail1.wav");
    if(!LoadBuffer(doorBufferFail,path))
    {
        printf( "Failed to load door open fail sound effect!\n");
        return false;
    }

    path = ("/Sound/Door_Open_Success.wav");
    if(!LoadBuffer(doorBufferOpen,path))
    {
		printf( "Failed to load door open success sound effect! %s\n");
		return false;
	}
	
    //setup source of door
	alGenSources(1, source); //allocate source 

	alSource3f(*source, AL_POSITION, 0.0f, 0.0f, 0.0f);
	alSource3f(*source, AL_VELOCITY, 0.0f, 0.0f, 0.0f);
	
    return success;
}

void freeDoorMedia(LTexture* doorTexture,
                    ALuint* source,
                    ALuint* doorBufferOpen, 
                    ALuint* doorBufferFail)
{
    //free source
    alDeleteSources(1, source); // delete source
    
    //free buffer
	alDeleteBuffers(1, doorBufferOpen); 
    alDeleteBuffers(1,doorBufferFail);
    
    //free tile texture map
    doorTexture->free();
}


void setupNewDoorObject(Door** thisDoor,
                            LTexture* doorTexture,
                            ALuint* source,
                            ALuint* doorBufferOpen, 
                            ALuint* doorBufferFail,
                            std::vector <SDL_Rect> *ptrDoorClips)
{
    *thisDoor = new Door();
    (*thisDoor)->setPointersToMedia(
                        doorTexture,
                        source,
                        doorBufferOpen, 
                        doorBufferFail,
                        ptrDoorClips);
}

Door::Door()
{
  //std::cout << "Door created! \n";  

    //initialize bool keyInsert
    keyInsert = false;
    
    //initialize door collision box
    collisionBoxDoor1.x=0;
    collisionBoxDoor1.y=0;
    collisionBoxDoor1.w = DOOR_WIDTH;
    collisionBoxDoor1.h = DOOR_HEIGHT;
    
    collisionBoxDoor2.x=0;
    collisionBoxDoor2.y=0;
    collisionBoxDoor2.w = DOOR_WIDTH;
    collisionBoxDoor2.h = DOOR_HEIGHT;

    //initialize door type
    Door::setDoorType(Door::Type::NO_LOCK_DOOR);
    //initialize door state to closed
    Door::setDoorState(Door::State::DOOR_CLOSED);
    //initialize key insert status
    Door::setKeyInsertStatus(false);
   
}

Door::~Door()
{
    //set pointer to key to null
    doorKey = nullptr;
    Door::setSoundState(Door::SoundState::NO_SOUND);
}

void Door::setDoorType(Door::Type type){doorType = type;}
Door::Type Door::getDoorType(){return doorType;}

void Door::setLock(Key* thisKey)
{
    //initialize door key pointer
    doorKey = thisKey;
    //set door type as locked door 
    Door::setDoorType(Door::Type::LOCK_DOOR);
}


void Door::handle_event(Event& thisEvent)
{
    
    switch( thisEvent )
    {
        case Event::SPACE:{ Door::setKeyInsertStatus(true); break;} //make keyInsert true
        case Event::SPACE_RELEASE:{ Door::setKeyInsertStatus(true); break;}
        case Event::JOYSTICK_0_BUTTON_DOWN_PRESSED:{ Door::setKeyInsertStatus(true); break;}
        case Event::JOYSTICK_1_BUTTON_DOWN_PRESSED:{ Door::setKeyInsertStatus(true); break;}
        default:{ Door::setKeyInsertStatus(false); break;} //make keyInsert false
    }
}

void Door::playSounds()
{
    //if  door is open and has lock
    if(Door::getSoundState() == Door::SoundState::PLAY_DOOR_OPEN_KEY)
    {
        //set buffer to source that is playing sound
        alSourcei(*doorSource, AL_BUFFER, *doorOpenBuffer);
        alSourcePlay(*doorSource);
        Door::setSoundState(Door::SoundState::NO_SOUND);
    }

    //if key is inserted but door doesn't open
    else if( Door::getSoundState() == Door::SoundState::PLAY_DOOR_FAIL)
    {
        
        //set buffer to source that is playing sound
        alSourcei(*doorSource, AL_BUFFER, *doorFailBuffer);
        //play sound
        alSourcePlay(*doorSource);
        Door::setSoundState(Door::SoundState::NO_SOUND);
    }
    
}

void Door::setSoundState(Door::SoundState thisState){doorSoundState = thisState;}
Door::SoundState Door::getSoundState(){return doorSoundState;}

void Door::render(SDL_Rect& camera, SDL_Renderer* gRenderer)
{
    switch(Door::getDoorType())
    {
        case Door::Type::NO_LOCK_DOOR:{ renderRectClip = &doorClips->at(0); break;}
        case Door::Type::LOCK_DOOR:{ renderRectClip = &doorClips->at(1); break;}
        case Door::Type::WINNER_DOOR:{ renderRectClip = &doorClips->at(2); break;}
    }
    
    if(checkCollision(Door::getCollisionBoxDoor1(),camera) )
    {
      //std::cout << "Door rendered at " << "x: " << //Door::getCollisionBoxDoor1().x << " y: " << Door::getCollisionBoxDoor1().y //<< std::endl; 
        doorImage->render(Door::getCollisionBoxDoor1().x - camera.x, 
                            Door::getCollisionBoxDoor1().y - camera.y, gRenderer, renderRectClip);
    }
    
    if(checkCollision(Door::getCollisionBoxDoor2(),camera) )
    {
      //std::cout << "Door rendered at " << "x: " << //Door::getCollisionBoxDoor2().x << " y: " << Door::getCollisionBoxDoor2().y //<< std::endl;
        doorImage->render(Door::getCollisionBoxDoor2().x - camera.x, 
                            Door::getCollisionBoxDoor2().y - camera.y, gRenderer, renderRectClip);
    }

}

void Door::setPointersToMedia(LTexture* doorTexture,
                            ALuint* source,
                            ALuint* doorBufferOpen, 
                            ALuint* doorBufferFail,
                            std::vector <SDL_Rect> *ptrDoorClips)
{
    doorImage = doorTexture;
    doorSource = source;
    doorOpenBuffer = doorBufferOpen;
    doorFailBuffer = doorBufferFail;
    doorClips = ptrDoorClips;
}

void Door::placeDoor1(std::int16_t&  x, std::int16_t&  y)
{
    collisionBoxDoor1.x = x;
    collisionBoxDoor1.y = y;
}

void Door::placeDoor2(std::int16_t&  x, std::int16_t&  y)
{
    collisionBoxDoor2.x = x;
    collisionBoxDoor2.y = y;
}

void Door::setDoorState(Door::State state){doorState = state;}
Door::State Door::getDoorState(){return doorState;}

bool checkDotCollidesWithDoor(Door* thisDoor, Dot* mainDot)
{
    if( checkCollision(thisDoor->getCollisionBoxDoor1(), 
                        mainDot->getSpaceBox()) )
    {
        thisDoor->doorCollideState = Door::DoorCollided::DOT_TO_DOOR1;
        return true;
    }
    else if( checkCollision(thisDoor->getCollisionBoxDoor2(), 
                            mainDot->getSpaceBox()) )
    {
        thisDoor->doorCollideState = Door::DoorCollided::DOT_TO_DOOR2;
        return true;
    }
    else
    {
        thisDoor->doorCollideState = Door::DoorCollided::NONE;
        return false;
    }
}

void Door::openDoorLogic()
{
    //if door has lock, run open door logic with lock function
    if(Door::getDoorType() == Door::Type::LOCK_DOOR){Door::openDoorLogicWithLock();}
    else{Door::openDoorLogicNoLock();}
    
     //set sound state
    switch(Door::getDoorState())
    {
        case Door::State::DOOR_CLOSED:{ Door::setSoundState(Door::SoundState::NO_SOUND); break;}
        case Door::State::DOOR_OPEN_FAIL:{ Door::setSoundState(Door::SoundState::PLAY_DOOR_FAIL); break;}
        case Door::State::DOOR_OPEN:{ Door::setSoundState(Door::SoundState::PLAY_DOOR_OPEN); break;}
    }
}


void Door::openDoorLogicWithLock()
{
    
    //if key is inserted and player has the key that the door owns and player is touching door
    if( Door::getKeyInsertStatus() && doorKey->getKeyBool() )
    {
       
        //if dot collides with either of doors
        if(doorCollideState == Door::DoorCollided::DOT_TO_DOOR1
            || doorCollideState == Door::DoorCollided::DOT_TO_DOOR2)
        {
            //open door
            Door::setDoorState(Door::State::DOOR_OPEN);
        }
    }
    //if key inserted and dot is at door but has no key
    else if( Door::getKeyInsertStatus() && !doorKey->getKeyBool() )
    {
        //if dot collides with either of doors
        if(doorCollideState == Door::DoorCollided::DOT_TO_DOOR1
            || doorCollideState == Door::DoorCollided::DOT_TO_DOOR2)
        {
            //open door
            Door::setDoorState(Door::State::DOOR_OPEN_FAIL);
        }
        
    }
    else
    {
        Door::setDoorState(Door::State::DOOR_CLOSED);
    }
    
    //reset key insert status
    Door::setKeyInsertStatus(false);
}

void Door::openDoorLogicNoLock()
{
     //if dot collides with either of doors
    if(doorCollideState == Door::DoorCollided::DOT_TO_DOOR1
        || doorCollideState == Door::DoorCollided::DOT_TO_DOOR2)
    {
        //if key is inserted
        if( Door::getKeyInsertStatus() )
        {
            //open door
            Door::setDoorState(Door::State::DOOR_OPEN);
        }
        else
        {
            //keep closed
            Door::setDoorState(Door::State::DOOR_CLOSED);
        }
    }
    else
    {
        //keep closed
        Door::setDoorState(Door::State::DOOR_CLOSED);
    }
    
    //reset key insert status
    Door::setKeyInsertStatus(false);
}

void Door::setKeyInsertStatus(bool state){keyInsert = state;}
bool Door::getKeyInsertStatus(){return keyInsert;}

SDL_Rect& Door::getCollisionBoxDoor1(){return collisionBoxDoor1;}
SDL_Rect& Door::getCollisionBoxDoor2(){return collisionBoxDoor2;}

Door::DoorCollided Door::getDoorCollidedState(){return doorCollideState;}

void Door::resetDoorsToClose()
{
    Door::setDoorState(Door::State::DOOR_CLOSED);
}
