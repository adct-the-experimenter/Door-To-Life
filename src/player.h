#ifndef PLAYER_H
#define PLAYER_H

#include <array>

#include "sprite.h"
#include "damage_values.h"
#include "weapon.h"

#include "audio_renderer.h"

class Player : public Sprite
{

public:

    //constructor to set up resources
    Player( int x, int y,int width,int height);

    //destructor to free resources
    virtual ~Player();
    
    //Player State
    enum class PlayerState : std::int8_t { NORMAL = 0, FALLING_IN_HOLE, 
                                            PUSHED_BACKED_BY_ENEMY,  
                                            COLLIDING_CONTRA_WALL};
    //functions to set and get player state
    void setPlayerState(Player::PlayerState thisState);
    Player::PlayerState getPlayerState();
    
                                                                            
    //functions to manipulate sprite state variable
    virtual void setSpriteState(Sprite::State state);
    virtual Sprite::State getSpriteState();
    
    //set speed
    virtual void setSpeed(float& speed);

    //set current position of dot
    virtual void setPosX(float& x);
    virtual void setPosY(float& y);

    //set x and y velocity of dot
    virtual void setVelX(float& dx);
    virtual void setVelY(float& dy);
    
    //function to load media for sprite
    virtual bool loadMedia(LTexture* thisTex, std::string path,SDL_Renderer* gRenderer);
    virtual void setPointerToTexture(LTexture* thisTex);
	virtual LTexture* getPointerToTexture();
	
    //Takes key presses and adjusts sprite's velocity
    virtual void handleEvent(Event& thisEvent);
    
    //functions to initialize and return sprite clips
    virtual void setSpriteClips(std::vector <SDL_Rect> *this_clips);
    virtual std::vector <SDL_Rect> *getSpriteClips();

    //initialize screen dimensions and level dimensions that sprite will move in
    virtual void setPlace(std::int16_t& screenWidth, std::int16_t& screenHeight);

    //Centers the camera over the sprite and intialize screen dimensions and level dimensions
    virtual void setCamera( SDL_Rect& camera);

    //logic module for player
    void logic(float& timeStep);
    

 /** Move sprite**/
    virtual void move(float& timeStep);

    virtual bool moveOnTiles(float& timeStep, std::vector<DungeonTile*> &dungeonTiles);
    
    //moves dot based on time since last render and returns tile type of tile dot collides with
    virtual DungeonTile::TileType moveOnTiles_TileType(float& timeStep, std::vector<DungeonTile*> &dungeonTiles);


    virtual void moveBack(float& timeStep);
    
    

    //have sprite face certain directions
    virtual void faceSouth();
    virtual void faceNorth();
    virtual void faceWest();
    virtual void faceEast();

	//Frame Animation
    
    //functions to determine frame count
    virtual void incrementFrameCount();
    virtual std::int8_t getFrameCount();
    virtual void resetFrameCount();
    
    //functions to determine frame offset
    virtual void setFrameOffset(std::int8_t& thisOffset);
    virtual std::int8_t getFrameOffset();
    
    //functions to set and get number of frames of animation
    virtual void setNumberOfAnimationFrames(std::int8_t& numFrames);
    virtual std::int8_t getNumberOfFramesOfAnimation();
    
    //functions to set and get clip
    virtual void setClipToShow(SDL_Rect* clip);
	virtual SDL_Rect* getClipToShow();

    //Shows the sprite on screen
    virtual void render(SDL_Rect& camera, SDL_Renderer* lRenderer, SDL_Rect* clip = NULL);

    //place sprite to a specific place. helpful between state changes
    virtual void placeChar(int x, int y);

    //Get sprite's's position and dimensions and velocity
    virtual float getPosX(); virtual float getPosY(); 
    virtual int getHeight(); virtual int getWidth();

    virtual float getVelX(); virtual float getVelY();

    virtual float getSpeed();

    virtual void setCollisionBox(SDL_Rect& box);
    //return sprite's collision box
    virtual SDL_Rect& getCollisionBox();

    //return Sprite's spacing box
    virtual SDL_Rect& getSpaceBox();
    
    //Collision object Functions
    
    // set owner type of collision object
    virtual void setOwnerTypeOfCollisionObject(CollisionBoxOwnerType& oType);
    //get type of collision that happened
    virtual CollisionType getCollisionType();
    //function to reset collision type
    void resetCollisionType();
    //get pointer to collision object
    virtual CollisionObject* getCollisionObjectPtr();
    
    //function to push back player a certain distance
    //if hit by something or collided with something
    void pushBackPlayer(float& timeStep,std::int16_t& pushBackDist);
//Health
    //function to set health
    void setHealth(std::int16_t& thisHP);
    //function to increment health
    void incrementHealth(std::int16_t& amount);
    //function to decrement health
    void decrementHealth(std::int16_t& amount);
    //function to return health 
    std::int16_t getHealth();
    std::int16_t& getHealthAddress();
    
    
    
    virtual void incrementLoopCount();
    virtual std::int8_t getLoopCount();
    virtual void resetLoopCount();

	friend class PlayerInventory;

//Sound
	void sound(AudioRenderer* gAudioRenderer);
	
	int getPlayerHeight();
private:

//members not inherited from sprite class
    std::int16_t health;
    
    LTexture playerTexture;
    
    //function to setup collision object
    void setupPlayerCollisionObject();
    
    Player::PlayerState playerState;
    
    //function to handle what happens to player depending on collision type
    void reactToCollision(float& timeStep);
    
    //number of times loop has been repeated
    //gives idea of time  interval for a frame
    std::int8_t loopCount;
    
    //clip of player for rendering
    //e.g. falling in hole
    SDL_Rect clipPlayer;
    
    //function to run logic for equipped weapon
    void runEquippedWeaponLogic(float& timeStep);
    
    //function to render equiped weapon
    void renderEquippedWeapon(SDL_Rect& camera, SDL_Renderer* gRenderer);
    
    //functions to run logic for certain states
    void runLogicState_CollideWithWall(float& timeStep);
    void runLogicState_Normal(float& timeStep);
    void runLogicState_PushedBack(float& timeStep);
    
    //Push Back
    std::int8_t numTimes_pushBackPlayer; // number of times to push back player by 10 pixels to match playerPushBack
    void setNumTimesPushBackPlayer(std::int8_t& thisNum);
    std::int8_t getNumTimesPushBackPlayer();
    void resetNumTimesPushBackPlayer();
    
    std::int8_t countPushBack;
    void incrementCountPushBack();
    std::int8_t getCountPushBack();
    void resetCountPushBack();
    
    //function to render collision box of player
    void renderPlayerCollisionBox(SDL_Rect& camera,SDL_Renderer* gRenderer);
    
    Weapon* equippedPlayerWeapon;
    
    //orientation of Listener
	std::array <float,6> listener_orientation_vector; //vector to hold values of listener orientation
	//first 3 values are forward vector xyz , last 3 values are up vector xyz
	//enum to help set orientation vector
	enum ORIENTATION_INDEX { FORWARD_X=0,FORWARD_Y=1,FORWARD_Z=2,
												 UP_X=3, UP_Y=4, UP_Z=5 };
													 
    //function to change listener position along with player
    void MoveListener(AudioRenderer* gAudioRenderer);
    
    void SetListenerDirection();
    
    void FaceListenerNorth();
    void FaceListenerNorthEast();
    void FaceListenerEast();
    void FaceListenerSouthEast();
    void FaceListenerSouth();
    void FaceListenerSouthWest();
    void FaceListenerWest();
    void FaceListenerNorthWest();
    
};

#endif
