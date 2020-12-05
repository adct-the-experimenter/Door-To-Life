#include "bullet.h"

bool loadBulletMedia(SDL_Renderer* gRenderer,LTexture* bulletTexture, 
                                std::vector <SDL_Rect> &bullet_clips)
{
	bool success = true;
    
    std::string bulletTexFilePath = DATADIR_STR + std::string("/Graphics/basic-bullets.png");
    //initialize bullet image
    if(!bulletTexture->loadFromFile(bulletTexFilePath.c_str(),gRenderer) )
    {
        success = false;
        std::cout << "bullet image loading failed! \n";
    }
    else
    {
        //8 direction clips,
        bullet_clips.resize(8);

        //direction
        bullet_clips[Bullet::NORTH] = {0,0,8,15};
        bullet_clips[Bullet::NORTHEAST] = {12,0,11,15};
        bullet_clips[Bullet::EAST] = {27,0,15,15};
        bullet_clips[Bullet::SOUTHEAST] = {45,0,12,15};
        
        bullet_clips[Bullet::SOUTH] = {60,0,8,15};
        bullet_clips[Bullet::SOUTHWEST] = {72,0,11,15};
        bullet_clips[Bullet::WEST] = {87,0,15,15};
        bullet_clips[Bullet::NORTHWEST] = {105,0,12,15};
        
        
    
    }
    
    return success;
	
}

Bullet::Bullet()
{
	posX = 0; posY = 0; 
	bulletSpeed = 0; 
	collisionBox = {0,0,0,0};
	bulletSpriteSheet = nullptr;
	spriteClip = nullptr;
}

Bullet::~Bullet(){posX = 0; posY = 0; bulletSpeed = 0; collisionBox = {0,0,0,0};}

//Dimensions

void Bullet::setBulletWidth(std::int8_t& width){collisionBox.w = width;}
void Bullet::setBulletHeight(std::int8_t& height){collisionBox.h = height;}

//Position

SDL_Rect& Bullet::getCollisionBox()
{
	return collisionBox;
}

void Bullet::setBulletPositionX(float& thisX)
{
	posX = thisX;
	collisionBox.x = static_cast<int>(posX);
}

void Bullet::setBulletPositionY(float& thisY)
{
	posY = thisY;
	collisionBox.y = static_cast<int>(posY);
}

void Bullet::resetBulletPosition()
{
	posX = 0;
	posY = 0;
	collisionBox.x = 0;
	collisionBox.y = 0;
}

//functions to move bullet

void Bullet::logic(float& timeStep)
{
	//if bullet is moving
	if(Bullet::getBulletState() != Bullet::BulletState::FIRED || 
		Bullet::getBulletState() != Bullet::BulletState::NONE)
	{
		Bullet::moveInStateDirection(timeStep);
	}
}

void Bullet::moveInStateDirection(float& timeStep)
{
	switch(Bullet::getBulletState())
	{
		case Bullet::BulletState::MOVING_UP:{ Bullet::moveUp(timeStep); break;} 
		case Bullet::BulletState::MOVING_UP_RIGHT:{ Bullet::moveUpRight(timeStep);  break;}
		case Bullet::BulletState::MOVING_RIGHT:{ Bullet::moveRight(timeStep);  break;} 
		case Bullet::BulletState::MOVING_DOWN_RIGHT:{ Bullet::moveDownRight(timeStep);  break;} 
		case Bullet::BulletState::MOVING_DOWN:{ Bullet::moveDown(timeStep);  break;} 
		case Bullet::BulletState::MOVING_DOWN_LEFT:{ Bullet::moveDownLeft(timeStep);  break;}
		case Bullet::BulletState::MOVING_LEFT:{ Bullet::moveLeft(timeStep);;  break;}
		case Bullet::BulletState::MOVING_UP_LEFT:{ Bullet::moveUpLeft(timeStep);  break;}
		default:{break;}
	}
}

void Bullet::moveUp(float& timeStep)
{
	posY -= bulletSpeed*timeStep;
	
	collisionBox.y = static_cast<int>(posY);
	
	Bullet::faceSpriteNorth();
}
void Bullet::moveUpRight(float& timeStep)
{
	posY -= (0.5 * bulletSpeed)*timeStep; 
	posX += (0.5 * bulletSpeed)*timeStep;
	
	collisionBox.x = static_cast<int>(posX);
	collisionBox.y = static_cast<int>(posY);
		
	Bullet::faceSpriteNorthEast();
}

void Bullet::moveRight(float& timeStep)
{
	posX += bulletSpeed*timeStep;
	collisionBox.x = static_cast<int>(posX);
	
		
	Bullet::faceSpriteEast();
}

void Bullet::moveDownRight(float& timeStep)
{
	posY += (0.5 * bulletSpeed)*timeStep; 
	posX += (0.5 * bulletSpeed)*timeStep;
	
	collisionBox.x = static_cast<int>(posX);
	collisionBox.y = static_cast<int>(posY);
	
		
	Bullet::faceSpriteSouthEast();
}

void Bullet::moveDown(float& timeStep)
{
	posY += bulletSpeed*timeStep;
	collisionBox.y = static_cast<int>(posY);
	
		
	Bullet::faceSpriteSouth();
}

void Bullet::moveDownLeft(float& timeStep)
{
	posY += (0.5 * bulletSpeed)*timeStep; 
	posX -= (0.5 * bulletSpeed)*timeStep;
	
	collisionBox.x = static_cast<int>(posX);
	collisionBox.y = static_cast<int>(posY);
	
		
	Bullet::faceSpriteSouthWest();
}

void Bullet::moveLeft(float& timeStep)
{
	posX -= bulletSpeed*timeStep;
	
	collisionBox.x = static_cast<int>(posX);
	
	Bullet::faceSpriteWest();
}

void Bullet::moveUpLeft(float& timeStep)
{
	posY -= (0.5 * bulletSpeed)*timeStep; 
	posX -= (0.5 * bulletSpeed)*timeStep;
	
	collisionBox.x = static_cast<int>(posX);
	collisionBox.y = static_cast<int>(posY);
		
	Bullet::faceSpriteNorthWest();
}

void Bullet::setBulletSpeed(float& thisSpeed){bulletSpeed = thisSpeed;}
float Bullet::getBulletSpeed(){return bulletSpeed;}

//Animation

void Bullet::render(SDL_Rect& camera,SDL_Renderer* gRenderer)
{
	
	if(bulletSpriteSheet != nullptr && Bullet::getSpriteClip() != nullptr)
	{		
		std::int16_t x = Bullet::getCollisionBox().x - camera.x;
		std::int16_t y = Bullet::getCollisionBox().y - camera.y;
		
		//render if x is more than or equal to zero and y is more than or equal to zero
		if(x >= 0 && y >= 0)
		{
			bulletSpriteSheet->render( x, y, gRenderer,Bullet::getSpriteClip());
		}
		
		//render collision box
		/*
		SDL_SetRenderDrawColor(gRenderer,
                           200,
                           0,
                           0,
                           50);
    
		SDL_Rect pBox = {  x ,
							 y ,
							Bullet::getCollisionBox().w,
							Bullet::getCollisionBox().h };
							
		SDL_RenderDrawRect(gRenderer,&pBox);
		*/
	}
}

//functions to determine which direction bullet faces
void Bullet::faceSpriteNorth()
{
	if(Bullet::getBulletSpriteClips() != nullptr)
	{
		SDL_Rect* thisClip = &((*Bullet::getBulletSpriteClips())[BulletFrame::NORTH]) ;
		Bullet::setSpriteClip(thisClip);
	}
	
}

void Bullet::faceSpriteNorthEast()
{
	if(Bullet::getBulletSpriteClips() != nullptr)
	{
		SDL_Rect* thisClip = &((*Bullet::getBulletSpriteClips())[BulletFrame::NORTHEAST]) ;
		Bullet::setSpriteClip(thisClip);
	}
}

void Bullet::faceSpriteEast()
{
	if(Bullet::getBulletSpriteClips() != nullptr)
	{
		SDL_Rect* thisClip = &((*Bullet::getBulletSpriteClips())[BulletFrame::EAST]) ;
		Bullet::setSpriteClip(thisClip);
	}
}

void Bullet::faceSpriteSouthEast()
{
	if(Bullet::getBulletSpriteClips() != nullptr)
	{
		SDL_Rect* thisClip = &((*Bullet::getBulletSpriteClips())[BulletFrame::SOUTHEAST]) ;
		Bullet::setSpriteClip(thisClip);
	}
}

void Bullet::faceSpriteSouth()
{
	if(Bullet::getBulletSpriteClips() != nullptr)
	{
		SDL_Rect* thisClip = &((*Bullet::getBulletSpriteClips())[BulletFrame::SOUTH]) ;
		Bullet::setSpriteClip(thisClip);
	}
}

void Bullet::faceSpriteSouthWest()
{
	if(Bullet::getBulletSpriteClips() != nullptr)
	{
		SDL_Rect* thisClip = &((*Bullet::getBulletSpriteClips())[BulletFrame::SOUTHWEST]) ;
		Bullet::setSpriteClip(thisClip);
	}
}

void Bullet::faceSpriteWest()
{
	if(Bullet::getBulletSpriteClips() != nullptr)
	{
		SDL_Rect* thisClip = &((*Bullet::getBulletSpriteClips())[BulletFrame::WEST]) ;
		Bullet::setSpriteClip(thisClip);
	}
}

void Bullet::faceSpriteNorthWest()
{
	if(Bullet::getBulletSpriteClips() != nullptr)
	{
		SDL_Rect* thisClip = &((*Bullet::getBulletSpriteClips())[BulletFrame::NORTHWEST]) ;
		Bullet::setSpriteClip(thisClip);
	}
}

void Bullet::setSpriteClip(SDL_Rect* thisClip){spriteClip = thisClip;}
SDL_Rect* Bullet::getSpriteClip(){return spriteClip;}

void Bullet::setSpriteTexture(LTexture* thisTexture){bulletSpriteSheet = thisTexture;}
LTexture* Bullet::getSpriteTexture(){return bulletSpriteSheet;}
	
void Bullet::setBulletSpriteClips(std::vector <SDL_Rect> *thisClips){clipsVector = thisClips;}
std::vector <SDL_Rect> *Bullet::getBulletSpriteClips(){return clipsVector;}

void Bullet::setBulletState(Bullet::BulletState state){bulletState = state;}
Bullet::BulletState Bullet::getBulletState(){return bulletState;}
