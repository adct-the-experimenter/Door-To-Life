#ifndef MY_ENEMY_H
#define MY_ENEMY_H

#include "enemy.h"
#include <array>

class MyEnemy : public Enemy
{
    
public:

 //constructor to set up resources
    MyEnemy( int x, int y,int width,int height);

    //destructor to free resources
    virtual ~MyEnemy();
                                    
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
    
    //function to load media outside class
    friend bool loadMyEnemyMedia(LTexture* cTexture,
                                    std::vector <SDL_Rect> &clips,
                                    SDL_Renderer* gRenderer );
                                    
    friend void freeMyEnemyMedia(LTexture* cTexture);                                
                        
    
    //function to set 
    void setPointersToMedia(LTexture* cTexture,std::vector <SDL_Rect> &clips);
    
    //functions to initialize and return sprite clips
    virtual void setSpriteClips(std::vector <SDL_Rect> *this_clips);
    virtual std::vector <SDL_Rect> *getSpriteClips();
    
   

    //initialize screen dimensions and level dimensions that sprite will move in
    virtual void setPlace(std::int16_t& screenWidth, std::int16_t& screenHeight);
    //Centers the camera over the sprite and intialize screen dimensions and level dimensions
    virtual void setCamera( SDL_Rect& camera);

     //Takes key presses and adjusts sprite's velocity
    virtual void handleEvent(Event& thisEvent);
    
    //Takes random seed and determines actions
    virtual void handleEvent_EnemyAI(RNGType& rngSeed);
    
    virtual void logic(float& timeStep, std::vector<DungeonTile*> &dungeonTiles);
    


 /** Move sprite**/
    virtual void move(float& timeStep);
    
    virtual bool moveOnTiles(float& timeStep, std::vector<DungeonTile*> &dungeonTiles);

    //moves dot based on time since last render and returns tile type of tile dot collides with
    virtual DungeonTile::TileType moveOnTiles_TileType(float& timeStep, std::vector<DungeonTile*> &dungeonTiles);
    
    virtual void moveBack(float& timeStep);
    
    //Frame animation 
    virtual void setDirection();
    virtual void setMoveClip();
    //function to determine which frame to use
    virtual void setFrame();
    
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

    //have sprite face certain directions
    virtual void faceSouth();
    virtual void faceNorth();
    virtual void faceWest();
    virtual void faceEast();
    
     //set which direction sprite is facing
    virtual void setFaceDirection(Sprite::FaceDirection dir);
    //return which direction sprite is facing
    virtual Sprite::FaceDirection getFaceDirection();

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
    //function to reset collision type to none to avoid getting stuck at a collision type
    virtual void resetCollisionType();
    //get pointer to collision object
    virtual CollisionObject* getCollisionObjectPtr();
    
    //function to push back enemy a certain distance
    virtual void pushBackEnemy(float& timeStep,std::int16_t& pushBackDist,CollisionDirection dir);
    //function to set number of times to push back enemy
    virtual void setNumTimesEnemyPushBack(std::int8_t& num);
    //function to return number of times to push back enemy
    virtual std::int8_t getNumTimesEnemyPushBack();
    //functions to determine count for times enemy pushed back
    virtual std::int8_t getCountPushBack();
    virtual void incrementCountPushBack();
    virtual void resetCountPushBack();
    
    virtual void setPushBackDirection(CollisionDirection dir);
    virtual CollisionDirection getPushBackDirection();
    virtual void resetPushBackDirection();
    
    virtual void resetPushBackVariables();
    
    //functions for movement
    virtual void moveUp(float& timeStep);
    virtual void moveDown(float& timeStep);
    virtual void moveLeft(float& timeStep);
    virtual void moveRight(float& timeStep);
    virtual void pause(float& timeStep);
    
    //function to do logic for reacting to certain collision types
    virtual void reactToCollision();
    
//Health
    //function to set health
    virtual void setHealth(std::int16_t& thisHP);
    //function to increment health
    virtual void incrementHealth(std::int16_t& amount);
    //function to decrement health
    virtual void decrementHealth(std::int16_t& amount);
    //function to return health 
    virtual std::int16_t getHealth();
    virtual std::int16_t& getHealthAddress();

//State
    virtual void setEnemyState(Enemy::EnemyState state);
    virtual Enemy::EnemyState getEnemyState();
    
    virtual void setRandNumber(std::int8_t& thisNum);
    virtual std::int8_t getRandNumber();
    
    virtual void runLogicState_MovingNoPlayer(float& timeStep);
    virtual void runLogicState_MovingSeePlayer(float& timeStep);
    virtual void runLogicState_HitByWeapon(float& timeStep);
    virtual void runLogicState_HitPlayer(float& timeStep);
    virtual void runLogicState_PushedBack(float& timeStep);
    virtual void runLogicState_CollideWithWall(float& timeStep);
    
    virtual void incrementLoopCount();
    virtual std::int8_t getLoopCount();
    virtual void resetLoopCount();
    
    //state specific to greedy zombie
    enum class MyEnemyState : std::int8_t {MOVE_UP = 0,MOVE_DOWN,MOVE_LEFT,MOVE_RIGHT,
                                            PAUSE,
                                            DETERMINE_DIRECTION};
    
    std::int8_t timeIntervalSwitchDirection = 20;

//Enemy View Options

    //function to set enemy view
    virtual void setEnemyView(Enemy::EnemyViewOption option);
    
    //function to set dimensions for line of sight
    virtual void setLineOfSightDimensions(std::int16_t& w, std::int16_t& h);
    virtual void setLineOfSightToEnemyBox();
    //function to check view for player
    //depending on what was set. Line of Sight or field of view or none
    //and set enemy state to see player if true
    virtual void checkViewForPlayer();
    
//Sound
	virtual void sound(AudioRenderer* gAudioRenderer);
    
private:
    //members not inherited from enemy
    
    //Array for probabilities of which direction to take
    std::array <double,5> probabilitiesDirection;
    
    std::stack <MyEnemy::MyEnemyState> state_stack;
    
    void pushState(MyEnemy::MyEnemyState state);
    void popState();
    MyEnemy::MyEnemyState getCurrentState();
    
    void setupMyEnemyCollisionObject();
    
    void renderEnemyCollisionBox(SDL_Rect& camera, SDL_Renderer* gRenderer);
};

#endif
