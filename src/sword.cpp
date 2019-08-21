
#include "sword.h"

bool loadSwordMedia(SDL_Renderer* gRenderer, LTexture* sTexture, std::vector <SDL_Rect> &s_walk_clips)
{
    bool success = true;
    
    std::string sTexFilePath = DATADIR_STR + std::string("/Graphics/sword-alt.png");
    //initialize cockroach image
    if(!sTexture->loadFromFile(sTexFilePath.c_str(),gRenderer) )
    {
        success = false;
        std::cout << "sword image loading failed! \n";
    }
    else
    {
        //32 walk clips, 1 ground clip, 32 attack clips
        s_walk_clips.resize(65);
    
        std::int8_t sword_width = 35;
        std::int8_t sword_height = 62;
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

        s_walk_clips[Weapon::UP_RIGHT_1] = {12,450,sword_width,sword_height};
        s_walk_clips[Weapon::UP_RIGHT_2] = {76,450,sword_width,sword_height};
        s_walk_clips[Weapon::UP_RIGHT_3] = {140,450,sword_width,sword_height};
        s_walk_clips[Weapon::UP_RIGHT_4] = {204,450,sword_width,sword_height};
        
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

        s_walk_clips[Weapon::ATTACK_UP_RIGHT_1] = {12,450,sword_width,sword_height};
        s_walk_clips[Weapon::ATTACK_UP_RIGHT_2] = {76,450,sword_width,sword_height};
        s_walk_clips[Weapon::ATTACK_UP_RIGHT_3] = {140,450,sword_width,sword_height};
        s_walk_clips[Weapon::ATTACK_UP_RIGHT_4] = {204,450,sword_width,sword_height};
    }
    
    return success;
}


void freeSwordMedia(LTexture* sTexture)
{
     if(sTexture != nullptr)
    {
        sTexture = nullptr;
    }
}

Sword::Sword()
{
    //make collider object owner type sword
    CollisionBoxOwnerType oType = CollisionBoxOwnerType::SWORD;
    Sword::setOwnerTypeOfCollisionObject(oType);
}

Sword::~Sword()
{
    
}

void Sword::setWeaponState(Weapon::WeaponState state){Weapon::setWeaponState(state);}
Weapon::WeaponState Sword::getWeaponState(){return Weapon::getWeaponState();}

void Sword::faceWeaponSouth(){Weapon::faceWeaponSouth();}
void Sword::faceWeaponNorth(){Weapon::faceWeaponNorth();}
void Sword::faceWeaponWest(){Weapon::faceWeaponWest();}
void Sword::faceWeaponEast(){Weapon::faceWeaponEast();}

void Sword::faceWeaponNorthEast(){Weapon::faceWeaponNorthEast();}
void Sword::faceWeaponSouthEast(){Weapon::faceWeaponSouthEast();}
void Sword::faceWeaponSouthWest(){Weapon::faceWeaponSouthWest();}
void Sword::faceWeaponNorthWest(){Weapon::faceWeaponNorthWest();}

void Sword::faceWeaponGroundNorth(){Weapon::faceWeaponGroundNorth();}

//Sprite of Weapon

void Sword::setSpriteSheetTexture(LTexture* thisTexPtr){Weapon::setSpriteSheetTexture(thisTexPtr);}
LTexture* Sword::getSpriteSheetTexture(){return Weapon::getSpriteSheetTexture();}
void Sword::setWalkClips(std::vector <SDL_Rect> *walk_clips){Weapon::setWalkClips(walk_clips);}
std::vector <SDL_Rect> *Sword::getWalkClips(){return Weapon::getWalkClips();}

void Sword::setFaceDirection(Weapon::FaceDirection dir){Weapon::setFaceDirection(dir);}
Weapon::FaceDirection Sword::getFaceDirection(){return Weapon::getFaceDirection();}

void Sword::faceSpriteSouth(){Weapon::faceSpriteSouth();}
void Sword::faceSpriteNorth(){Weapon::faceSpriteNorth();}
void Sword::faceSpriteWest(){Weapon::faceSpriteWest();}
void Sword::faceSpriteEast(){Weapon::faceSpriteEast();}

void Sword::faceSpriteNorthEast(){Weapon::faceSpriteNorthEast();}
void Sword::faceSpriteSouthEast(){Weapon::faceSpriteSouthEast();}
void Sword::faceSpriteSouthWest(){Weapon::faceSpriteSouthWest();}
void Sword::faceSpriteNorthWest(){Weapon::faceSpriteNorthWest();}

void Sword::faceSpriteGroundNorth(){Weapon::faceSpriteGroundNorth();}

//Shows the sprite on screen
void Sword::render(SDL_Rect& camera, SDL_Renderer* gRenderer, SDL_Rect* clip)
{
   Weapon::render(camera,gRenderer,clip);
} 

//Frame animation 

void Sword::setMoveClip()
{
    Weapon::setMoveClip();
}

void Sword::setFrame()
{
    Weapon::setFrame();
}

void Sword::incrementFrameCount(){Weapon::incrementFrameCount();}
std::int8_t Sword::getFrameCount(){return Weapon::getFrameCount();}
void Sword::resetFrameCount(){Weapon::resetFrameCount();}

void Sword::setFrameOffset(std::int8_t& thisOffset){Weapon::setFrameOffset(thisOffset);}
std::int8_t Sword::getFrameOffset(){return Weapon::getFrameOffset();}

void Sword::setNumberOfAnimationFrames(std::int8_t& numFrames){Weapon::setNumberOfAnimationFrames(numFrames);}
std::int8_t Sword::getNumberOfFramesOfAnimation(){return Weapon::getNumberOfFramesOfAnimation();}

void Sword::setClipToShow(SDL_Rect* clip){ Weapon::setClipToShow(clip);}

//Collision Box of Weapon

void Sword::addWeaponToCollisionHandler(){Weapon::addWeaponToCollisionHandler();}
void Sword::removeWeaponFromCollisionHandler(){Weapon::removeWeaponFromCollisionHandler();}

void Sword::setWeaponGroundBoxWidth(std::int16_t& width){Weapon::setWeaponGroundBoxWidth(width);}
void Sword::setWeaponGroundBoxHeight(std::int16_t& height){Weapon::setWeaponGroundBoxHeight(height);}

void Sword::setWeaponAttackBoxWidth(std::int16_t& width){Weapon::setWeaponAttackBoxWidth(width);}
void Sword::setWeaponAttackBoxHeight(std::int16_t& height){Weapon::setWeaponAttackBoxHeight(height);}

void Sword::setGroundLocation(std::int16_t& x, std::int16_t& y){Weapon::setGroundLocation(x,y);}

void Sword::setWeaponPosX(std::int16_t& x){Weapon::setWeaponPosX(x);}
void Sword::setWeaponPosY(std::int16_t& y){Weapon::setWeaponPosY(y);}
std::int16_t& Sword::getWeaponPosX(){return Weapon::getWeaponPosX();}
std::int16_t& Sword::getWeaponPosY(){return Weapon::getWeaponPosY();}

void Sword::setWeaponRenderPosX(std::int16_t& x){Weapon::setWeaponRenderPosX(x);}
void Sword::setWeaponRenderPosY(std::int16_t& y){Weapon::setWeaponRenderPosY(y);}
std::int16_t& Sword::getWeaponRenderPosX(){return Weapon::getWeaponRenderPosX();}
std::int16_t& Sword::getWeaponRenderPosY(){return Weapon::getWeaponRenderPosY();}

void Sword::attachWeaponToHandlerBox(SDL_Rect* box){Weapon::attachWeaponToHandlerBox(box);}

SDL_Rect* Sword::getHandlerBox(){return Weapon::getHandlerBox();}
    
void Sword::moveWeaponWithHandler(){Weapon::moveWeaponWithHandler();}

void Sword::faceBoxUp(){Weapon::faceBoxUp();}

void Sword::faceBoxDown(){Weapon::faceBoxDown();}

void Sword::faceBoxLeft(){Weapon::faceBoxLeft();}

void Sword::faceBoxRight(){Weapon::faceBoxRight();}


void Sword::faceBoxUpLeft(){Weapon::faceBoxUpLeft();}
void Sword::faceBoxUpRight(){Weapon::faceBoxUpRight();}
void Sword::faceBoxDownLeft(){Weapon::faceBoxDownLeft();}
void Sword::faceBoxDownRight(){Weapon::faceBoxDownRight();}

void Sword::faceBoxGround(){Weapon::faceBoxGround();}

void Sword::renderWeaponBox(SDL_Rect& camera,SDL_Renderer* gRenderer)
{
    Weapon::renderWeaponBox(camera,gRenderer);
}

void Sword::suppressWeapon(){Weapon::suppressWeapon();}

//Collision object Functions

void Sword::setOwnerTypeOfCollisionObject(CollisionBoxOwnerType& oType){Weapon::setOwnerTypeOfCollisionObject(oType);}

CollisionType Sword::getCollisionType(){return Weapon::getCollisionType();}

void Sword::resetCollisionType(){Weapon::resetCollisionType();}

CollisionObject* Sword::getCollisionObjectPtr(){return Weapon::getCollisionObjectPtr();}

void Sword::setDirectionOfCollision(CollisionDirection thisDirection){Weapon::setDirectionOfCollision(thisDirection);}

bool Sword::getBool_HeroTouchedWeaponOnGround(){return Weapon::getBool_HeroTouchedWeaponOnGround();}
