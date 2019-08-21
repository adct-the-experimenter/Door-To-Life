#ifndef SPRITE_H
#define SPRITE_H


#include <stack>
#include <vector>
#include <cstdint> //for integer types with definite sizes
#include "dot_final.h"

class Sprite : public Dot
{
    //friend function with access to Dot and Tile private data members , checks collision between 2 rectangles
    //friend bool checkCollision(SDL_Rect a, SDL_Rect b);

public:


    //constructor to set up resources
    Sprite( int x, int y,int width,int height);

    //destructor to free resources
    virtual ~Sprite();
    
    //sprite action state
    enum class State : std::int8_t {STAND=0,
                                    WALK,
                                    RUN, JUMP};
                                    
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
    
    //function to load media for 1 sprite
    virtual bool loadMedia(LTexture* thisTex, std::string path,SDL_Renderer* gRenderer);
    
    virtual void setPointerToTexture(LTexture* thisTex);
	virtual LTexture* getPointerToTexture();
	
    //Takes key presses and adjusts sprite's velocity
    virtual void handleEvent(Event& thisEvent);

    //functions to initialize and return sprite clips
    virtual void setSpriteClips(std::vector <SDL_Rect> *this_clips);
    virtual std::vector <SDL_Rect> *getSpriteClips();
    
     //frames of animation, 0 to 15
    enum WalkAnimFrames{
                        UP_1 = 0, UP_2, UP_3, UP_4,
                        
                        UP_RIGHT_1, UP_RIGHT_2, UP_RIGHT_3, UP_RIGHT_4,
                        
                        UP_LEFT_1, UP_LEFT_2, UP_LEFT_3, UP_LEFT_4,
                        
                        LEFT_1,LEFT_2,LEFT_3, LEFT_4,
                        
                        DOWN_1,DOWN_2,DOWN_3,DOWN_4,
                        
                        DOWN_RIGHT_1, DOWN_RIGHT_2, DOWN_RIGHT_3, DOWN_RIGHT_4,
                        
                        DOWN_LEFT_1, DOWN_LEFT_2, DOWN_LEFT_3, DOWN_LEFT_4,
                        
                        RIGHT_1,RIGHT_2,RIGHT_3,RIGHT_4
                        };

    //initialize screen dimensions and level dimensions that sprite will move in
    virtual void setPlace(std::int16_t& screenWidth, std::int16_t& screenHeight);

    //Centers the camera over the sprite and intialize screen dimensions and level dimensions
    virtual void setCamera( SDL_Rect& camera);


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
 
    //enum for face direction
    enum class FaceDirection : std::int8_t { NORTH = 0, NORTHEAST,
                                            EAST, 
                                            SOUTHEAST, SOUTH, SOUTHWEST,
                                            WEST,
                                            NORTHWEST};
                                            
    //set which direction sprite is facing
    virtual void setFaceDirection(Sprite::FaceDirection dir);
    //return which direction sprite is facing
    virtual Sprite::FaceDirection getFaceDirection();
    
    //Shows the sprite on screen
    virtual void render(SDL_Rect& camera, SDL_Renderer* lRenderer, SDL_Rect* clip = NULL); 

    //place sprite to a specific place. helpful between state changes
    virtual void placeChar(int x, int y);

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
	
    //Get sprite's's position and dimensions and velocity
    virtual float getPosX(); virtual float getPosY(); 
    virtual int getHeight(); virtual int getWidth();

    virtual float getVelX(); virtual float getVelY();

    virtual float getSpeed();
    

    //set dot's collision box
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
    
    

private:

//members not inherited from dot class
    
    //number of frames passed
    std::int8_t framesPassedCount;
    
    //number of frames to pass to get to wanted frame
    std::int8_t frameOffset;
    
    //max number of frames of animation
    std::int8_t numberOfFramesOfAnimation;
    
    //state of sprite
    Sprite::State spriteState;
    
    //pointer to vector of SDL_Rect clips
    std::vector <SDL_Rect> *clips;

    //pointer to SDL_Rect clips
    SDL_Rect* clipPtr;

    //Direction sprite is facing
    Sprite::FaceDirection faceDirection;
};

#endif
