#ifndef GUN_H
#define GUN_H

#include "weapon.h"
#include "bullet.h"

class Gun : public Weapon
{
public:

    friend bool loadGunMedia(SDL_Renderer* gRenderer,LTexture* sTexture, 
                                std::vector <SDL_Rect> &s_walk_clips);
    
    friend void freeGunMedia(LTexture* sTexture);
    
    //constructor
    Gun();
    //destructor
    virtual ~Gun();
                                    
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
    
//Sprite of Sword
    
    //function to assign texture pointer to point to address of sprite sheet texture
    virtual void setSpriteSheetTexture(LTexture* thisTexPtr);
    //function to return pointer to sprite sheet texture
    virtual LTexture* getSpriteSheetTexture();
    //function to set walk clips for sword animation
    virtual void setWalkClips(std::vector <SDL_Rect> *walk_clips);
    //function to return pointer to walk clips
    virtual std::vector <SDL_Rect> * getWalkClips();
    
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
     
    //function to determine which row in sprite sheet to use based on drection
    //char is facing
    virtual void setMoveClip();
    //function to determine which frame to use
    virtual void setFrame();
    
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
    
    //functions to change direction box is facing
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
    
    virtual bool getBool_HeroTouchedWeaponOnGround();
    
    //bool to return if an object collided with weapon
    virtual bool checkCollisionWithWeapon(SDL_Rect& thisBox);    
    
//Game Loop Modules

	//handles lgoic for weapon
	virtual void logic(float& timeStep);
	//Shows the sprite on screen
    virtual void render(SDL_Rect& camera, SDL_Renderer* gRenderer, SDL_Rect* clip = nullptr); 

//Bullet Specific Functions
	void setPointerToBullet(Bullet* thisBullet);
private:
	//Bullet inside gun
	Bullet* gunBullet;

};

#endif
