#ifndef BULLET_H
#define BULLET_H

#include "globalvariables.h" //for SDL_Rect
#include "LTexture.h" // for LTexture

class Bullet
{
public:
	
	Bullet();
	~Bullet();
	
	friend bool loadBulletMedia(SDL_Renderer* gRenderer,LTexture* bulletTexture, 
                                std::vector <SDL_Rect> &bullet_clips);
	
//Dimensions
	virtual void setBulletWidth(std::int8_t& width);
	virtual void setBulletHeight(std::int8_t& height);
	
//Position

	//get bullet's collision box
	virtual SDL_Rect& getCollisionBox();
	//set location of bullet 
	virtual void setBulletPositionX(float& thisX);
	virtual void setBulletPositionY(float& thisY);
	//function to reset bullet
	virtual void resetBulletPosition();
	
//Movement

	
	//functions to move bullet
	virtual void moveUp(float& timeStep);
	virtual void moveUpRight(float& timeStep);
	virtual void moveRight(float& timeStep);
	virtual void moveDownRight(float& timeStep);
	virtual void moveDown(float& timeStep);
	virtual void moveDownLeft(float& timeStep);
	virtual void moveLeft(float& timeStep);
	virtual void moveUpLeft(float& timeStep);
	
	virtual void moveInStateDirection(float& timeStep);
	
	virtual void setBulletSpeed(float& thisSpeed);
	virtual float getBulletSpeed();

//Animation	

	//functions to set and get texture for bullet
	virtual void setSpriteTexture(LTexture* thisTexture);
	virtual LTexture* getSpriteTexture();
	
	//functions to set and get clips of bullets
	virtual void setBulletSpriteClips(std::vector <SDL_Rect> *thisClips);
	virtual std::vector <SDL_Rect> *getBulletSpriteClips();
	
	//functions to set and get clip for rendering
	virtual void setSpriteClip(SDL_Rect* thisClip);
	virtual SDL_Rect* getSpriteClip();
	
	//frames for different directions for bullet
	enum BulletFrame { NORTH = 0,NORTHEAST,EAST,SOUTHEAST,SOUTH,SOUTHWEST,WEST,NORTHWEST };
	
	//functions to determine which direction bullet faces
	virtual void faceSpriteNorth();
	virtual void faceSpriteNorthEast();
	virtual void faceSpriteEast();
	virtual void faceSpriteSouthEast();
	virtual void faceSpriteSouth();
	virtual void faceSpriteSouthWest();
	virtual void faceSpriteWest();
	virtual void faceSpriteNorthWest();
//States

	enum class BulletState : std::int8_t {	
											NONE = 0, 
											FIRED, 
											MOVING_UP,
											MOVING_UP_RIGHT,
											MOVING_RIGHT,
											MOVING_DOWN_RIGHT, 
											MOVING_DOWN,
											MOVING_DOWN_LEFT,
											MOVING_LEFT,
											MOVING_UP_LEFT};
											
	virtual void setBulletState(Bullet::BulletState state);
	virtual Bullet::BulletState getBulletState();

//Game Loop Modules
	//function to handle logic for bullet 
	virtual void logic(float& timeStep);
	//function to render bullet
	virtual void render(SDL_Rect& camera,SDL_Renderer* gRenderer);
	
	
	
private:
	//pointer to texture for sprite sheet
	LTexture* bulletSpriteSheet;
	
	//pointer to vector of clips
	std::vector <SDL_Rect> *clipsVector;
	
	//clip to render
	SDL_Rect* spriteClip;
	
	//collision box of bullet
	SDL_Rect collisionBox;
	
	//speed bullet travels
	float bulletSpeed;
	
	float posX;
	float posY;
	
	//state of bullet
	Bullet::BulletState bulletState;
};

#endif
