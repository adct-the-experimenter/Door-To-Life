#ifndef WEAPON_H
#define WEAPON_H

#include "LTexture.h" // for Texture
#include "collisionobject.h" // for Collision Object and check collision
#include <cstdint>

#include "sprite.h"

class Weapon 
{
public:
    
    //constructor
    Weapon();
    //destructor
    virtual ~Weapon();

     //action state
    enum class WeaponState : std::int8_t {
                                    ON_GROUND = 0,
                                            
                                    IN_INVENTORY,
    
                                    STAND_WITH_HANDLER_NO_ACTION,
                                    STAND_WITH_HANDLER_ACTIVATED,
                                    
                                    MOVING_WITH_HANDLER_NO_ACTION,
                                    MOVING_WITH_HANDLER_ACTIVATED,
                                    };
                                    
    //functions to set and getstate variable
    virtual void setWeaponState(Weapon::WeaponState state);
    virtual Weapon::WeaponState getWeaponState();
    
    //functions to face sprite and box a certain direction
    virtual void faceWeaponSouth();
    virtual void faceWeaponNorth();
    virtual void faceWeaponWest();
    virtual void faceWeaponEast();
    
    virtual void faceWeaponNorthEast();
    virtual void faceWeaponSouthEast();
    virtual void faceWeaponSouthWest();
    virtual void faceWeaponNorthWest();
    
    virtual void faceWeaponGroundNorth();
    
//Sprite of Weapon

    //function to assign texture pointer to point to address of sprite sheet texture
    virtual void setSpriteSheetTexture(LTexture* thisTexPtr);
    //function to return pointer to sprite sheet texture
    virtual LTexture* getSpriteSheetTexture();
    //function to set walk clips for sword animation
    virtual void setWalkClips(std::vector <SDL_Rect> *walk_clips);
    //function to return pointer to walk clips
    std::vector <SDL_Rect> *getWalkClips();
    
    //enum for face direction
    enum class FaceDirection : std::int8_t { NORTH = 0, NORTHEAST,
                                            EAST, 
                                            SOUTHEAST, SOUTH, SOUTHWEST,
                                            WEST,
                                            NORTHWEST,
                                            GROUND_NORTH};
    
    //have sprite face certain directions
    virtual void faceSpriteSouth();
    virtual void faceSpriteNorth();
    virtual void faceSpriteWest();
    virtual void faceSpriteEast();
    
    virtual void faceSpriteNorthEast();
    virtual void faceSpriteSouthEast();
    virtual void faceSpriteSouthWest();
    virtual void faceSpriteNorthWest();

    virtual void faceSpriteGroundNorth();
                                            
    //set which direction sprite is facing
    virtual void setFaceDirection(Weapon::FaceDirection dir);
    //return which direction sprite is facing
    virtual Weapon::FaceDirection getFaceDirection();

     //Frame animation 
    virtual void setMoveClip();
    //function to determine which frame to use based on current frame count
    virtual void setFrame();
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
    
    //function to set clip
    virtual void setClipToShow(SDL_Rect* clip);
    
    enum WalkAnimFrames{
                        //Walk
                        UP_1 = 0, UP_2, UP_3, UP_4,
                        UP_RIGHT_1, UP_RIGHT_2, UP_RIGHT_3, UP_RIGHT_4,
                        UP_LEFT_1, UP_LEFT_2, UP_LEFT_3, UP_LEFT_4,
                        LEFT_1,LEFT_2,LEFT_3, LEFT_4,
                        DOWN_1,DOWN_2,DOWN_3,DOWN_4,
                        DOWN_RIGHT_1, DOWN_RIGHT_2, DOWN_RIGHT_3, DOWN_RIGHT_4,
                        DOWN_LEFT_1, DOWN_LEFT_2, DOWN_LEFT_3, DOWN_LEFT_4,
                        RIGHT_1,RIGHT_2,RIGHT_3,RIGHT_4,
                        
                        //On Ground
                        GROUND_NORTH,
                        
                        //Attack
                        ATTACK_UP_1, ATTACK_UP_2, ATTACK_UP_3, ATTACK_UP_4,
                        ATTACK_UP_RIGHT_1, ATTACK_UP_RIGHT_2, ATTACK_UP_RIGHT_3, ATTACK_UP_RIGHT_4,
                        ATTACK_UP_LEFT_1, ATTACK_UP_LEFT_2, ATTACK_UP_LEFT_3, ATTACK_UP_LEFT_4,
                        ATTACK_LEFT_1,ATTACK_LEFT_2,ATTACK_LEFT_3, ATTACK_LEFT_4,
                        ATTACK_DOWN_1,ATTACK_DOWN_2,ATTACK_DOWN_3,ATTACK_DOWN_4,
                        ATTACK_DOWN_RIGHT_1, ATTACK_DOWN_RIGHT_2, ATTACK_DOWN_RIGHT_3, ATTACK_DOWN_RIGHT_4,
                         ATTACK_DOWN_LEFT_1,  ATTACK_DOWN_LEFT_2,  ATTACK_DOWN_LEFT_3,  ATTACK_DOWN_LEFT_4,
                        ATTACK_RIGHT_1,ATTACK_RIGHT_2,ATTACK_RIGHT_3,ATTACK_RIGHT_4,
                        };

//Collision Box of Weapon

    //function to add collision object of weapon to collision handler system
    virtual void addWeaponToCollisionHandler();
    //function to remove collision object of weapon from collision handler system
    virtual void removeWeaponFromCollisionHandler();
    
    //functions to set the width and height of the ground box weapon
    virtual void setWeaponGroundBoxWidth(std::int16_t& width);
    virtual void setWeaponGroundBoxHeight(std::int16_t& height);
    
    //functions to set the width and height of attack box for weapon
    //assuming Height is the long side
    //assuming width is the short side
    virtual void setWeaponAttackBoxWidth(std::int16_t& width);
    virtual void setWeaponAttackBoxHeight(std::int16_t& height);
    
    //function to change location of the box if on ground
    virtual void setGroundLocation(std::int16_t& x, std::int16_t& y);
    
    //functions to set and get position of weapon collision box
    virtual void setWeaponPosX(std::int16_t& x);
    virtual void setWeaponPosY(std::int16_t& y);
    virtual std::int16_t& getWeaponPosX();
    virtual std::int16_t& getWeaponPosY();
    
    //functions to set and return where to render sprite
    virtual void setWeaponRenderPosX(std::int16_t& x);
    virtual void setWeaponRenderPosY(std::int16_t& y);
    
    virtual std::int16_t& getWeaponRenderPosX();
    virtual std::int16_t& getWeaponRenderPosY();
    
    //function to assign SDL_Rect pointer to address of whoever has weapon
    virtual void attachWeaponToHandlerBox(SDL_Rect* box);
    //function to return pointer to handler box
    virtual SDL_Rect* getHandlerBox();
    
    //function to set location of box based on location of handler's box
    virtual void moveWeaponWithHandler();
    
    //functions to change direction box is facing when carried by Handler
    virtual void faceBoxUp();
    virtual void faceBoxDown();
    virtual void faceBoxLeft();
    virtual void faceBoxRight();
    
    
    virtual void faceBoxUpLeft();
    virtual void faceBoxUpRight();
    virtual void faceBoxDownLeft();
    virtual void faceBoxDownRight();
    
    //function to set collision box of weapon on ground
    virtual void faceBoxGround();
    
    //function to render line of sight
    virtual void renderWeaponBox(SDL_Rect& camera,SDL_Renderer* gRenderer);
    
    //function to set weapon collision box hidden by changing width and height to zero
    virtual void suppressWeapon();
    
//Collision object Functions
    
    // set owner type of collision object
    virtual void setOwnerTypeOfCollisionObject(CollisionBoxOwnerType& oType);
    //get type of collision that happened
    virtual CollisionType getCollisionType();
    //function to reset collision type to none to avoid getting stuck at a collision type
    virtual void resetCollisionType();
    //get pointer to collision object
    virtual CollisionObject* getCollisionObjectPtr();
    
    //set direction of collision
    virtual void setDirectionOfCollision(CollisionDirection thisDirection);
            
    //bool to return if hero collided with weapon while in ground state
    virtual bool getBool_HeroTouchedWeaponOnGround();
    
    //bool to return if an object collided with weapon
    virtual bool checkCollisionWithWeapon(SDL_Rect& thisBox);
    
//Game Loop Modules

	//handles lgoic for weapon
	virtual void logic(float& timeStep);
	//Shows the sprite on screen
    virtual void render(SDL_Rect& camera, SDL_Renderer* gRenderer, SDL_Rect* clip = nullptr); 

	void SetHeightFromGround(std::int16_t height);
    
private:

//Sprite

     //pointer to texture for sprite sheet
    LTexture* weapon_sprite_sheet_ptr;
    
    //pointer to vector of SDL_Rect clips of sword for sprite sheet
    //walking animation clips 
    std::vector <SDL_Rect> *weapon_clips;
    
    //number of frames passed
    std::int8_t framesPassedCount;
    
    //number of frames to pass to get to wanted frame
    std::int8_t frameOffset;
    
    //max number of frames of animation
    std::int8_t numberOfFramesOfAnimation;
    
    //pointer to SDL_Rect clip, which frame should be rendered
    SDL_Rect* clipPtr;
    
    //state of weapon
    Weapon::WeaponState weaponState;
    
    //Direction weapon sprite is facing
    Weapon::FaceDirection faceDirection;
    
    //where to render weapon sprite
    std::int16_t xRenderPos;
    std::int16_t yRenderPos;
    

//Collision Box
    //position of weapon
    std::int16_t xWeaponPos;
    std::int16_t yWeaponPos;
    
    //dimensions of handler
    std::int16_t handlerWidth;
    std::int16_t handlerHeight;
    
    //height from ground
    std::int16_t heightFromGround;
    
    //collision box of handler
    SDL_Rect* handlerBox;
    
    //dimensions of weapon box when on ground
    std::int16_t weaponGroundWidth;
    std::int16_t weaponGroundHeight;
    
    //dimensions of attack box for when weapon used to attack
    std::int16_t attackBoxWidth;
    std::int16_t attackBoxHeight;
    
    //Final box to use for collider object
    //Manipulate for ground and attack
    SDL_Rect weapon_collisionBox;
    
    //Collision Object member
    CollisionObject weapon_ColliderObject;
};

#endif
