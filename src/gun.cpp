
#include "gun.h"

bool loadGunMedia(SDL_Renderer* gRenderer, LTexture* sTexture, std::vector <SDL_Rect> &s_walk_clips)
{
    bool success = true;
    
    std::string sTexFilePath = DATADIR_STR + std::string("/Graphics/basic-gun.png");
    //initialize gun image
    if(!sTexture->loadFromFile(sTexFilePath.c_str(),gRenderer) )
    {
        success = false;
        std::cout << "gun image loading failed! \n";
    }
    else
    {
        //32 walk clips, 1 ground clip, 32 attack clips
        s_walk_clips.resize(65);
    
        std::int8_t gun_width = 35;
        std::int8_t gun_height = 62;
        //walk
        s_walk_clips[Weapon::DOWN_1] = {7,1,9,22};
        s_walk_clips[Weapon::DOWN_2] = {17,1,9,22};
        s_walk_clips[Weapon::DOWN_3] = {26,1,9,22};
        s_walk_clips[Weapon::DOWN_4] = {35,1,9,22};
        
        s_walk_clips[Weapon::LEFT_1] = {8,35,26,41};
        s_walk_clips[Weapon::LEFT_2] = {34,35,26,41};
        s_walk_clips[Weapon::LEFT_3] = {60,35,26,41};
        s_walk_clips[Weapon::LEFT_4] = {90,35,26,41};
        
        s_walk_clips[Weapon::RIGHT_1] = {8,80,26,41};
        s_walk_clips[Weapon::RIGHT_2] = {34,80,26,41};
        s_walk_clips[Weapon::RIGHT_3] = {60,80,26,41};
        s_walk_clips[Weapon::RIGHT_4] = {90,80,26,41};

        s_walk_clips[Weapon::UP_1] = {8,33,17,19};
        s_walk_clips[Weapon::UP_2] = {8,33,17,19}; 
        s_walk_clips[Weapon::UP_3] = {8,33,17,19}; 
        s_walk_clips[Weapon::UP_4] = {8,33,17,19};

        s_walk_clips[Weapon::DOWN_RIGHT_1] = {8,145,20,27};
        s_walk_clips[Weapon::DOWN_RIGHT_2] = {28,145,20,27};
        s_walk_clips[Weapon::DOWN_RIGHT_3] = {47,145,20,27};
        s_walk_clips[Weapon::DOWN_RIGHT_4] = {67,145,20,27};

        s_walk_clips[Weapon::DOWN_LEFT_1] = {8,185,20,27};
        s_walk_clips[Weapon::DOWN_LEFT_2] = {28,185,20,27};
        s_walk_clips[Weapon::DOWN_LEFT_3] = {48,185,20,27};
        s_walk_clips[Weapon::DOWN_LEFT_4] = {69,185,20,27};

        s_walk_clips[Weapon::UP_LEFT_1] = {7,231,20,28};
        s_walk_clips[Weapon::UP_LEFT_2] = {29,231,20,28};
        s_walk_clips[Weapon::UP_LEFT_3] = {52,231,20,28};
        s_walk_clips[Weapon::UP_LEFT_4] = {74,231,20,28};

        s_walk_clips[Weapon::UP_RIGHT_1] = {12,450,gun_width,gun_height};
        s_walk_clips[Weapon::UP_RIGHT_2] = {76,450,gun_width,gun_height};
        s_walk_clips[Weapon::UP_RIGHT_3] = {140,450,gun_width,gun_height};
        s_walk_clips[Weapon::UP_RIGHT_4] = {204,450,gun_width,gun_height};
        
        //ground
        s_walk_clips[Weapon::GROUND_NORTH] = {16,283,7,26};
        
        //Attack
        s_walk_clips[Weapon::ATTACK_DOWN_1] = {7,1,9,22};
        s_walk_clips[Weapon::ATTACK_DOWN_2] = {17,1,9,22};
        s_walk_clips[Weapon::ATTACK_DOWN_3] = {26,1,9,22};
        s_walk_clips[Weapon::ATTACK_DOWN_4] = {35,1,9,22};
        
        s_walk_clips[Weapon::ATTACK_LEFT_1] = {145,44,26,20};
        s_walk_clips[Weapon::ATTACK_LEFT_2] = {171,44,26,20};
        s_walk_clips[Weapon::ATTACK_LEFT_3] = {197,44,26,20};
        s_walk_clips[Weapon::ATTACK_LEFT_4] = {224,44,26,20};
        
        s_walk_clips[Weapon::ATTACK_RIGHT_1] = {8,80,26,41};
        s_walk_clips[Weapon::ATTACK_RIGHT_2] = {34,80,26,41};
        s_walk_clips[Weapon::ATTACK_RIGHT_3] = {60,80,26,41};
        s_walk_clips[Weapon::ATTACK_RIGHT_4] = {90,80,26,41};

        s_walk_clips[Weapon::ATTACK_UP_1] = {8,33,17,19};
        s_walk_clips[Weapon::ATTACK_UP_2] = {8,33,17,19}; 
        s_walk_clips[Weapon::ATTACK_UP_3] = {8,33,17,19}; 
        s_walk_clips[Weapon::ATTACK_UP_4] = {8,33,17,19};

        s_walk_clips[Weapon::ATTACK_DOWN_RIGHT_1] = {8,145,20,27};
        s_walk_clips[Weapon::ATTACK_DOWN_RIGHT_2] = {28,145,20,27};
        s_walk_clips[Weapon::ATTACK_DOWN_RIGHT_3] = {47,145,20,27};
        s_walk_clips[Weapon::ATTACK_DOWN_RIGHT_4] = {67,145,20,27};

        s_walk_clips[Weapon::ATTACK_DOWN_LEFT_1] = {8,185,20,27};
        s_walk_clips[Weapon::ATTACK_DOWN_LEFT_2] = {28,185,20,27};
        s_walk_clips[Weapon::ATTACK_DOWN_LEFT_3] = {48,185,20,27};
        s_walk_clips[Weapon::ATTACK_DOWN_LEFT_4] = {69,185,20,27};

        s_walk_clips[Weapon::ATTACK_UP_LEFT_1] = {7,231,20,28};
        s_walk_clips[Weapon::ATTACK_UP_LEFT_2] = {29,231,20,28};
        s_walk_clips[Weapon::ATTACK_UP_LEFT_3] = {52,231,20,28};
        s_walk_clips[Weapon::ATTACK_UP_LEFT_4] = {74,231,20,28};

        s_walk_clips[Weapon::ATTACK_UP_RIGHT_1] = {12,450,gun_width,gun_height};
        s_walk_clips[Weapon::ATTACK_UP_RIGHT_2] = {76,450,gun_width,gun_height};
        s_walk_clips[Weapon::ATTACK_UP_RIGHT_3] = {140,450,gun_width,gun_height};
        s_walk_clips[Weapon::ATTACK_UP_RIGHT_4] = {204,450,gun_width,gun_height};
    }
    
    return success;
}


void freeGunMedia(LTexture* sTexture)
{
     if(sTexture != nullptr)
    {
        sTexture = nullptr;
    }
}

Gun::Gun()
{
    //make collider object owner type sword
    CollisionBoxOwnerType oType = CollisionBoxOwnerType::BULLET;
    Gun::setOwnerTypeOfCollisionObject(oType);
    Gun::setDirectionOfCollision(CollisionDirection::NONE);
    
}

Gun::~Gun()
{
    
}

void Gun::setWeaponState(Weapon::WeaponState state){Weapon::setWeaponState(state);}
Weapon::WeaponState Gun::getWeaponState(){return Weapon::getWeaponState();}

void Gun::faceWeaponSouth(){Weapon::faceWeaponSouth();}
void Gun::faceWeaponNorth(){Weapon::faceWeaponNorth();}
void Gun::faceWeaponWest(){Weapon::faceWeaponWest();}
void Gun::faceWeaponEast(){Weapon::faceWeaponEast();}

void Gun::faceWeaponNorthEast(){Weapon::faceWeaponNorthEast();}
void Gun::faceWeaponSouthEast(){Weapon::faceWeaponSouthEast();}
void Gun::faceWeaponSouthWest(){Weapon::faceWeaponSouthWest();}
void Gun::faceWeaponNorthWest(){Weapon::faceWeaponNorthWest();}

void Gun::faceWeaponGroundNorth(){Weapon::faceWeaponGroundNorth();}

//Sprite of Weapon

void Gun::setSpriteSheetTexture(LTexture* thisTexPtr){Weapon::setSpriteSheetTexture(thisTexPtr);}
LTexture* Gun::getSpriteSheetTexture(){return Weapon::getSpriteSheetTexture();}
void Gun::setWalkClips(std::vector <SDL_Rect> *walk_clips){Weapon::setWalkClips(walk_clips);}
std::vector <SDL_Rect> *Gun::getWalkClips(){return Weapon::getWalkClips();}

void Gun::setFaceDirection(Weapon::FaceDirection dir){Weapon::setFaceDirection(dir);}
Weapon::FaceDirection Gun::getFaceDirection(){return Weapon::getFaceDirection();}

void Gun::faceSpriteSouth(){Weapon::faceSpriteSouth();}
void Gun::faceSpriteNorth(){Weapon::faceSpriteNorth();}
void Gun::faceSpriteWest(){Weapon::faceSpriteWest();}
void Gun::faceSpriteEast(){Weapon::faceSpriteEast();}

void Gun::faceSpriteNorthEast(){Weapon::faceSpriteNorthEast();}
void Gun::faceSpriteSouthEast(){Weapon::faceSpriteSouthEast();}
void Gun::faceSpriteSouthWest(){Weapon::faceSpriteSouthWest();}
void Gun::faceSpriteNorthWest(){Weapon::faceSpriteNorthWest();}

void Gun::faceSpriteGroundNorth(){Weapon::faceSpriteGroundNorth();}

void Gun::logic(float& timeStep)
{
	//move weapon collision box with player collision box
    Gun::moveWeaponWithHandler();
    
    //if weapon is not activated, suppress weapon state
    if(Gun::getWeaponState() != Weapon::WeaponState::STAND_WITH_HANDLER_ACTIVATED){Gun::suppressWeapon();}
    //else if weapon is activated
    else if(Gun::getWeaponState() == Weapon::WeaponState::STAND_WITH_HANDLER_ACTIVATED)
    {
		//set bullet at weapon's position
		float x = Gun::getCollisionObjectPtr()->ptrToCollisionBox->x;
		float y = Gun::getCollisionObjectPtr()->ptrToCollisionBox->y;
		gunBullet->setBulletPositionX(x);
		gunBullet->setBulletPositionY(y);
		
		//set bullet state to fired
		gunBullet->setBulletState(Bullet::BulletState::FIRED);
		
		//set direction for bullet to move in based on direction gun is pointing
		switch(Gun::getFaceDirection())
		{
			case Weapon::FaceDirection::NORTH:{ gunBullet->setBulletState(Bullet::BulletState::MOVING_UP); break;} 
			case Weapon::FaceDirection::NORTHEAST:{ gunBullet->setBulletState(Bullet::BulletState::MOVING_UP_RIGHT);  break;}
			case Weapon::FaceDirection::EAST:{ gunBullet->setBulletState(Bullet::BulletState::MOVING_RIGHT);  break;} 
			case Weapon::FaceDirection::SOUTHEAST:{ gunBullet->setBulletState(Bullet::BulletState::MOVING_DOWN_RIGHT);  break;} 
			case Weapon::FaceDirection::SOUTH:{ gunBullet->setBulletState(Bullet::BulletState::MOVING_DOWN);  break;} 
			case Weapon::FaceDirection::SOUTHWEST:{ gunBullet->setBulletState(Bullet::BulletState::MOVING_DOWN_LEFT);  break;}
			case Weapon::FaceDirection::WEST:{ gunBullet->setBulletState(Bullet::BulletState::MOVING_LEFT);  break;}
            case Weapon::FaceDirection::NORTHWEST:{ gunBullet->setBulletState(Bullet::BulletState::MOVING_UP_LEFT);  break;}
            default:{break;}
		}
	}
	gunBullet->logic(timeStep);
	
    //set new move clip for player weapon
    Gun::setMoveClip();
    
    //set frame of weapon clip
    Gun::setFrame();
}

//Shows the sprite on screen
void Gun::render(SDL_Rect& camera, SDL_Renderer* gRenderer, SDL_Rect* clip)
{
   Weapon::render(camera,gRenderer,clip);
   gunBullet->render(camera,gRenderer);
} 

//Frame animation 

void Gun::setMoveClip()
{
    Weapon::setMoveClip();
}

void Gun::setFrame()
{
    Weapon::setFrame();
}

void Gun::incrementFrameCount(){Weapon::incrementFrameCount();}
std::int8_t Gun::getFrameCount(){return Weapon::getFrameCount();}
void Gun::resetFrameCount(){Weapon::resetFrameCount();}

void Gun::setFrameOffset(std::int8_t& thisOffset){Weapon::setFrameOffset(thisOffset);}
std::int8_t Gun::getFrameOffset(){return Weapon::getFrameOffset();}

void Gun::setNumberOfAnimationFrames(std::int8_t& numFrames){Weapon::setNumberOfAnimationFrames(numFrames);}
std::int8_t Gun::getNumberOfFramesOfAnimation(){return Weapon::getNumberOfFramesOfAnimation();}

void Gun::setClipToShow(SDL_Rect* clip){ Weapon::setClipToShow(clip);}

//Collision Box of Weapon

void Gun::addWeaponToCollisionHandler(){Weapon::addWeaponToCollisionHandler();}
void Gun::removeWeaponFromCollisionHandler(){Weapon::removeWeaponFromCollisionHandler();}

void Gun::setWeaponGroundBoxWidth(std::int16_t& width){Weapon::setWeaponGroundBoxWidth(width);}
void Gun::setWeaponGroundBoxHeight(std::int16_t& height){Weapon::setWeaponGroundBoxHeight(height);}

void Gun::setWeaponAttackBoxWidth(std::int16_t& width){Weapon::setWeaponAttackBoxWidth(width);}
void Gun::setWeaponAttackBoxHeight(std::int16_t& height){Weapon::setWeaponAttackBoxHeight(height);}

void Gun::setGroundLocation(std::int16_t& x, std::int16_t& y){Weapon::setGroundLocation(x,y);}

void Gun::setWeaponPosX(std::int16_t& x){Weapon::setWeaponPosX(x);}
void Gun::setWeaponPosY(std::int16_t& y){Weapon::setWeaponPosY(y);}
std::int16_t& Gun::getWeaponPosX(){return Weapon::getWeaponPosX();}
std::int16_t& Gun::getWeaponPosY(){return Weapon::getWeaponPosY();}

void Gun::setWeaponRenderPosX(std::int16_t& x){Weapon::setWeaponRenderPosX(x);}
void Gun::setWeaponRenderPosY(std::int16_t& y){Weapon::setWeaponRenderPosY(y);}
std::int16_t& Gun::getWeaponRenderPosX(){return Weapon::getWeaponRenderPosX();}
std::int16_t& Gun::getWeaponRenderPosY(){return Weapon::getWeaponRenderPosY();}

void Gun::attachWeaponToHandlerBox(SDL_Rect* box){Weapon::attachWeaponToHandlerBox(box);}

SDL_Rect* Gun::getHandlerBox(){return Weapon::getHandlerBox();}
    
void Gun::moveWeaponWithHandler(){Weapon::moveWeaponWithHandler();}

void Gun::faceBoxUp(){Weapon::faceBoxUp();}

void Gun::faceBoxDown(){Weapon::faceBoxDown();}

void Gun::faceBoxLeft(){Weapon::faceBoxLeft();}

void Gun::faceBoxRight(){Weapon::faceBoxRight();}


void Gun::faceBoxUpLeft(){Weapon::faceBoxUpLeft();}
void Gun::faceBoxUpRight(){Weapon::faceBoxUpRight();}
void Gun::faceBoxDownLeft(){Weapon::faceBoxDownLeft();}
void Gun::faceBoxDownRight(){Weapon::faceBoxDownRight();}

void Gun::faceBoxGround(){Weapon::faceBoxGround();}

void Gun::renderWeaponBox(SDL_Rect& camera,SDL_Renderer* gRenderer)
{
    Weapon::renderWeaponBox(camera,gRenderer);
}

void Gun::suppressWeapon(){Weapon::suppressWeapon();}

//Collision object Functions

void Gun::setOwnerTypeOfCollisionObject(CollisionBoxOwnerType& oType){Weapon::setOwnerTypeOfCollisionObject(oType);}

CollisionType Gun::getCollisionType(){return Weapon::getCollisionType();}

void Gun::resetCollisionType(){Weapon::resetCollisionType();}

CollisionObject* Gun::getCollisionObjectPtr(){return Weapon::getCollisionObjectPtr();}

void Gun::setDirectionOfCollision(CollisionDirection thisDirection){Weapon::setDirectionOfCollision(thisDirection);}

bool Gun::getBool_HeroTouchedWeaponOnGround(){return Weapon::getBool_HeroTouchedWeaponOnGround();}

bool Gun::checkCollisionWithWeapon(SDL_Rect& thisBox)
{
	//if gun bullet collides with object
	if(checkCollision(gunBullet->getCollisionBox(),thisBox))
	{
		//reset position of bullet and return true
		//gunBullet->resetBulletPosition();
		return true;
	}
	else{return false;}
}

//Bullet Specific functions
void Gun::setPointerToBullet(Bullet* thisBullet){gunBullet = thisBullet;}
