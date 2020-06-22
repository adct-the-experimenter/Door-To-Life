#ifndef MY_ENEMY_H
#define MY_ENEMY_H

#include "enemy.h"
#include <array>

class ScriptedEnemy : public Enemy
{
    
public:

 //constructor to set up resources
    ScriptedEnemy( int x, int y,int width,int height);

    //destructor to free resources
    virtual ~ScriptedEnemy();
                                    
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
    friend bool loadScriptedEnemyMedia(LTexture* cTexture,
                                    std::vector <SDL_Rect> &clips,
                                    SDL_Renderer* gRenderer );
                                    
    friend void freeScriptedEnemyMedia(LTexture* cTexture);                                
                        
    
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
  
    //function to determine which frame to use
    virtual void setFrame();
    
    
    //Shows the sprite on screen
    virtual void render(SDL_Rect& camera, SDL_Renderer* lRenderer, SDL_Rect* clip = NULL);

//Collision object Functions
    
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
    enum class ScriptedEnemyState : std::int8_t {MOVE_UP = 0,MOVE_DOWN,MOVE_LEFT,MOVE_RIGHT,
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
    
    std::stack <ScriptedEnemy::ScriptedEnemyState> state_stack;
    
    void pushState(ScriptedEnemy::ScriptedEnemyState state);
    void popState();
    ScriptedEnemy::ScriptedEnemyState getCurrentState();
    
    void setupScriptedEnemyCollisionObject();
    
    void renderEnemyCollisionBox(SDL_Rect& camera, SDL_Renderer* gRenderer);
};

#endif
