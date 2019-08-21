#ifndef DOT_FINAL_H
#define DOT_FINAL_H

#include "globalvariables.h"
#include <vector>
#include <iostream>


#include "Dungeon_Tile.h"
#include "LTexture.h"

#include "collisionobject.h" // for collision object and checkCollision function
#include "event_handler.h" //for handling key presses

class Dot
{
    
public:


    //constructor to set up resources
    Dot(int x, int y,int width,int height);

    //destructor to free resources
    virtual ~Dot();

    //set speed
    virtual void setSpeed(float& speed);

    //set x and y position of dot
    virtual void setPosX(float& x);
    virtual void setPosY(float& y);

    //set x and y velocity of dot
    virtual void setVelX(float& dx);
    virtual void setVelY(float& dy);

    
    //Takes key presses and adjusts dot's velocity
    virtual void handleEvent(Event& thisEvent);

    //initialize screen dimensions and level dimensions that dot will move in
    virtual void setPlace(std::int16_t& screenWidth, std::int16_t& screenHeight);

      //Centers the camera over the dot and intialize screen dimensions and level dimensions
    virtual void setCamera( SDL_Rect& );

    //move dot
    virtual void move(float& timeStep);
    //move dot back if it hits anything with a collision box
    virtual void moveBack(float& timeStep);

    //moves dot based on time since last render and checks collision against DungeonTiles returns true if colliding with wall
    virtual bool moveOnTiles(float& timeStep, std::vector<DungeonTile*> &dungeonTiles);
    
    //moves dot based on time since last render and returns tile type of tile dot collides with
    virtual DungeonTile::TileType moveOnTiles_TileType(float& timeStep, std::vector<DungeonTile*> &dungeonTiles);

    //Shows the dot on screen
    virtual void render(SDL_Rect& camera, SDL_Renderer* lRenderer, SDL_Rect* clip = NULL);

    //place dot to a specific place. helpful between state changes
    virtual void placeChar(int x, int y);



    //Get Dot's position and dimensions and velocity
    virtual float getPosX(); virtual float getPosY(); virtual int getHeight(); virtual int getWidth();
    virtual float getVelX(); virtual float getVelY();
    virtual float getSpeed();
    
    //set dot's collision box
    virtual void setCollisionBox(SDL_Rect& box);
    //return dot's collision box
    virtual SDL_Rect& getCollisionBox();
    //return space that dot occupies
    virtual SDL_Rect& getSpaceBox();

    //Screen dimensions
    std::int16_t SCREEN_WIDTH;
    std::int16_t SCREEN_HEIGHT;
    
	//Media functions
	
	//default function to load media 
    virtual bool loadMedia(LTexture* thisTex, std::string path,SDL_Renderer* gRenderer);
    
    //functions to set and get pointer to texture member of dot class
    virtual void setPointerToTexture(LTexture* thisTex);
    virtual LTexture* getPointerToTexture();
    
    //Collision object Functions
    
    // set owner type of collision object
    virtual void setOwnerTypeOfCollisionObject(CollisionBoxOwnerType& oType);
    //get type of collision that happened
    virtual CollisionType getCollisionType();
    //function to reset collision type to none to avoid getting stuck at a collision type
    virtual void resetCollisionType();
    //get pointer to collision object
    virtual CollisionObject* getCollisionObjectPtr();
    
    
    
    //let player access private dot collision Object
    friend class Player;
    friend class Enemy;
private:
    
    //speed
    float DOT_VEL;

    //x and y position of the dot
    float mPosX,mPosY;

    //velocity of the dot
    float mVelX,mVelY;

    //Collision box of the dot
    SDL_Rect mBox;
    //offset for collision box 
    std::int16_t xClipPosOffset;
    std::int16_t yClipPosOffset;

    //space that dot occupies
    SDL_Rect spaceBox;

    //Texture of the dot
    LTexture* dotImage;

    //collision object of dot to pass to collision handler
    CollisionObject dotCollisionObject;
    
};


#endif // DOT_FINAL
