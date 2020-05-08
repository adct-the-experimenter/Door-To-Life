#include "weapon.h"

Weapon::Weapon()
{
    //make collider object collision box pointer point to weapon collision box
    weapon_ColliderObject.ptrToCollisionBox = &weapon_collisionBox;
    
    //initialize handler box pointer
    handlerBox = nullptr;
    
    xWeaponPos = 0;
    yWeaponPos = 0;
    handlerWidth = 0;
    handlerHeight = 0;
    
    heightFromGround = 0;
    
    //initialize ground box dimensions
    weaponGroundWidth = 0; weaponGroundHeight = 0;
    
    //initialize attack box dimensions
    attackBoxWidth = 0; attackBoxHeight = 0;
    
    //initialize walk clips vector pointer
    Weapon::setWalkClips(nullptr);
    
    //initialize Ltexture pointer
    Weapon::setSpriteSheetTexture(nullptr);
    
    //initialize weapon to face right
    //Weapon::faceWeaponEast();
}

Weapon::~Weapon()
{
    //set handler box pointer to nullptr
    handlerBox = nullptr;
    
     //set walk clips vector pointer to point to nullptr
    Weapon::setWalkClips(nullptr);
    
    //set Ltexture pointer to point to nullptr
    Weapon::setSpriteSheetTexture(nullptr);
}

void Weapon::setWeaponState(Weapon::WeaponState state){weaponState = state;}
Weapon::WeaponState Weapon::getWeaponState(){return weaponState;}



void Weapon::faceWeaponSouth()
{
	Weapon::faceSpriteSouth(); 
	Weapon::faceBoxDown(); 
	Weapon::setDirectionOfCollision(CollisionDirection::SOUTH); 
}

void Weapon::faceWeaponNorth()
{
	Weapon::faceSpriteNorth(); 
	Weapon::faceBoxUp(); 
	Weapon::setDirectionOfCollision(CollisionDirection::NORTH);
}

void Weapon::faceWeaponWest()
{
	Weapon::faceSpriteWest(); 
	Weapon::faceBoxLeft(); 
	Weapon::setDirectionOfCollision(CollisionDirection::WEST);
}

void Weapon::faceWeaponEast()
{
	Weapon::faceSpriteEast(); 
	Weapon::faceBoxRight(); 
	Weapon::setDirectionOfCollision(CollisionDirection::EAST);
}

void Weapon::faceWeaponNorthEast()
{
	Weapon::faceSpriteNorthEast(); 
	Weapon::faceBoxUpRight(); 
	Weapon::setDirectionOfCollision(CollisionDirection::NORTHEAST);
}

void Weapon::faceWeaponSouthEast()
{
	Weapon::faceSpriteSouthEast(); 
	Weapon::faceBoxDownRight(); 
	Weapon::setDirectionOfCollision(CollisionDirection::SOUTHEAST);
}

void Weapon::faceWeaponSouthWest()
{
	Weapon::faceSpriteSouthWest(); 
	Weapon::faceBoxDownLeft();
	Weapon::setDirectionOfCollision(CollisionDirection::SOUTHWEST);
}

void Weapon::faceWeaponNorthWest()
{
	Weapon::faceSpriteNorthWest(); 
	Weapon::faceBoxUpLeft();
	Weapon::setDirectionOfCollision(CollisionDirection::NORTHWEST);
}

void Weapon::faceWeaponGroundNorth()
{
    //set face direction to ground north
    Weapon::faceSpriteGroundNorth();
    //set collision box to ground location and dimensions
    Weapon::faceBoxGround();
    Weapon::setDirectionOfCollision(CollisionDirection::NONE);
}

//Sprite of Weapon

void Weapon::setSpriteSheetTexture(LTexture* thisTexPtr){weapon_sprite_sheet_ptr = thisTexPtr;}
LTexture* Weapon::getSpriteSheetTexture(){return weapon_sprite_sheet_ptr;}
void Weapon::setWalkClips(std::vector <SDL_Rect> *walk_clips){weapon_clips = walk_clips;}
std::vector <SDL_Rect> *Weapon::getWalkClips(){return weapon_clips;}

void Weapon::setFaceDirection(Weapon::FaceDirection dir){faceDirection = dir;}
Weapon::FaceDirection Weapon::getFaceDirection(){return faceDirection;}

void Weapon::faceSpriteSouth()
{
    Weapon::setFaceDirection(Weapon::FaceDirection::SOUTH);
    
    //move render position left of handler
    xRenderPos = xWeaponPos - (handlerWidth / 2);
    //move render position below handler
    yRenderPos = yWeaponPos + handlerWidth - heightFromGround;
}

void Weapon::faceSpriteNorth()
{
    Weapon::setFaceDirection(Weapon::FaceDirection::NORTH);
    
}

void Weapon::faceSpriteWest()
{
    Weapon::setFaceDirection(Weapon::FaceDirection::WEST);
    
    //move render position left of handler
    xRenderPos = xWeaponPos - handlerWidth;
    //keep at same y position
    yRenderPos = yWeaponPos - heightFromGround;
}

void Weapon::faceSpriteEast()
{
    Weapon::setFaceDirection(Weapon::FaceDirection::EAST);
    
    //move render x position right of handler
    xRenderPos = xWeaponPos + handlerWidth;
    //keep at same y position
    yRenderPos = yWeaponPos  - heightFromGround;
}

void Weapon::faceSpriteNorthEast()
{
    Weapon::setFaceDirection(Weapon::FaceDirection::NORTHEAST);
}

void Weapon::faceSpriteSouthEast()
{
    Weapon::setFaceDirection(Weapon::FaceDirection::SOUTHEAST);
    
    //move render x position right of handler
    xRenderPos = xWeaponPos + handlerWidth;
    //move render y position below handler
    yRenderPos = yWeaponPos + handlerHeight - heightFromGround;
}

void Weapon::faceSpriteSouthWest()
{
    Weapon::setFaceDirection(Weapon::FaceDirection::SOUTHWEST);
    
    //move render x position left of handler
    xRenderPos = xWeaponPos - (handlerWidth / 2);
    //move render y position below handler
    yRenderPos = yWeaponPos + handlerHeight - heightFromGround;
}

void Weapon::faceSpriteNorthWest()
{
    Weapon::setFaceDirection(Weapon::FaceDirection::NORTHWEST);
    
    //move render x position left of handler
    xRenderPos = xWeaponPos - (3 * handlerWidth / 2);
    //move render y position above handler
    yRenderPos = yWeaponPos - heightFromGround;
}

void Weapon::faceSpriteGroundNorth()
{
    Weapon::setFaceDirection(Weapon::FaceDirection::GROUND_NORTH);
    
    xRenderPos = xWeaponPos;
    yRenderPos = yWeaponPos;
}






void Weapon::setMoveClip()
{
     //if weapon is not in action state
    if(Weapon::getWeaponState() == Weapon::WeaponState::MOVING_WITH_HANDLER_NO_ACTION ||
        Weapon::getWeaponState() == Weapon::WeaponState::STAND_WITH_HANDLER_NO_ACTION)
    {
        switch(Weapon::getFaceDirection())
        {
            case Weapon::FaceDirection::NORTH:{ Weapon::setClipToShow(&(*weapon_clips)[Weapon::UP_1]); break;}
            case Weapon::FaceDirection::NORTHEAST:{ Weapon::setClipToShow(&(*weapon_clips)[Weapon::UP_RIGHT_1]);  break;}
            case Weapon::FaceDirection::EAST:{ Weapon::setClipToShow(&(*weapon_clips)[Weapon::RIGHT_1]); break;}
            case Weapon::FaceDirection::SOUTHEAST:{ Weapon::setClipToShow(&(*weapon_clips)[Weapon::DOWN_RIGHT_1]);  break;}
            case Weapon::FaceDirection::SOUTH:{ Weapon::setClipToShow(&(*weapon_clips)[Weapon::DOWN_1]); break;}
            case Weapon::FaceDirection::SOUTHWEST:{ Weapon::setClipToShow(&(*weapon_clips)[Weapon::DOWN_LEFT_1]);  break;}
            case Weapon::FaceDirection::WEST:{ Weapon::setClipToShow(&(*weapon_clips)[Weapon::LEFT_1]); break;}
            case Weapon::FaceDirection::NORTHWEST:{ Weapon::setClipToShow(&(*weapon_clips)[Weapon::UP_LEFT_1]);  break;}
            case Weapon::FaceDirection::GROUND_NORTH:{ Weapon::setClipToShow(&(*weapon_clips)[Weapon::GROUND_NORTH]); break;}
            default:{ break;}
        }
    }
    //else if weapon is in action state
    else if(Weapon::getWeaponState() == Weapon::WeaponState::STAND_WITH_HANDLER_ACTIVATED)
    {
        switch(Weapon::getFaceDirection())
        {
            case Weapon::FaceDirection::NORTH:{ break;}
            case Weapon::FaceDirection::NORTHEAST:{ break;}
            case Weapon::FaceDirection::EAST:{ break;}
            case Weapon::FaceDirection::SOUTHEAST:{ break;}
            case Weapon::FaceDirection::SOUTH:{ break;}
            case Weapon::FaceDirection::SOUTHWEST:{ break;}
            case Weapon::FaceDirection::WEST:{ Weapon::setClipToShow(&(*weapon_clips)[Weapon::ATTACK_LEFT_1]); break;}
            case Weapon::FaceDirection::NORTHWEST:{ break;}
            case Weapon::FaceDirection::GROUND_NORTH:{ break;}
            default:{ break;}
        }
    }
}

//function to determine which frame to use
void Weapon::setFrame()
{
    std::int8_t localFrameOffset = 0;
    
    //frame count
    int fCount = Weapon::getFrameCount();
    
    int animFrames = Weapon::getNumberOfFramesOfAnimation();
    
    //if frame count is more than 2, reset
    //divide frame count by 4 frames of animation to slow down animation
    // How integers work: 0/4 == 0 1/4 == 0 2/4 == 0 3/4 = 0 4/4 = 0
    if(fCount/animFrames > animFrames){Weapon::resetFrameCount();}
    
    //if weapon is on ground or 
    //if weapon is with handler and handler isn't moving
    if(Weapon::getWeaponState() == Weapon::WeaponState::STAND_WITH_HANDLER_NO_ACTION)
    {
        localFrameOffset = 0;
    }
    //if weapon is moving with handler
    else if(Weapon::getWeaponState() == Weapon::WeaponState::MOVING_WITH_HANDLER_NO_ACTION)
    {
        //stand
        if(fCount/animFrames == 0){localFrameOffset = 0;}
        //step with left
        else if(fCount/animFrames == 1){localFrameOffset = 1;}
        //stand
        else if(fCount/animFrames == 2){localFrameOffset = 2;}
        //step with right
        else if(fCount/animFrames == 3){localFrameOffset = 3;}
    }
    //set frame offset
    Weapon::setFrameOffset(localFrameOffset);
}

void Weapon::incrementFrameCount(){framesPassedCount++;}
std::int8_t Weapon::getFrameCount(){return framesPassedCount;}
void Weapon::resetFrameCount(){framesPassedCount = 0;}

void Weapon::setFrameOffset(std::int8_t& thisOffset){frameOffset = thisOffset;}
std::int8_t Weapon::getFrameOffset(){return frameOffset;}

void Weapon::setNumberOfAnimationFrames(std::int8_t& numFrames){numberOfFramesOfAnimation = numFrames;}
std::int8_t Weapon::getNumberOfFramesOfAnimation(){return numberOfFramesOfAnimation;}

void Weapon::setClipToShow(SDL_Rect* clip){ clipPtr = clip;}

//Collision Box of Weapon

void Weapon::addWeaponToCollisionHandler(){/*addObjectToCollisionSystem(&weapon_ColliderObject);*/}
void Weapon::removeWeaponFromCollisionHandler(){/*removeObjectFromCollisionSystem(&weapon_ColliderObject);*/}

void Weapon::setWeaponGroundBoxWidth(std::int16_t& width){weaponGroundWidth = width;}
void Weapon::setWeaponGroundBoxHeight(std::int16_t& height){weaponGroundHeight = height;}


void Weapon::setWeaponAttackBoxWidth(std::int16_t& width){attackBoxWidth = width;}
void Weapon::setWeaponAttackBoxHeight(std::int16_t& height){attackBoxHeight = height;}

void Weapon::setGroundLocation(std::int16_t& x, std::int16_t& y)
{
    //change position
    xWeaponPos = x;
    yWeaponPos = y;
    
    //face it in the current direction with new location
    switch(Weapon::getFaceDirection())
    {
        case Weapon::FaceDirection::NORTH:{ Weapon::faceWeaponNorth(); break;}
        case Weapon::FaceDirection::NORTHEAST:{ Weapon::faceWeaponNorthEast(); break;}
        case Weapon::FaceDirection::EAST:{ Weapon::faceWeaponEast(); break;}
        case Weapon::FaceDirection::SOUTHEAST:{ Weapon::faceWeaponSouthEast(); break;}
        case Weapon::FaceDirection::SOUTH:{ Weapon::faceWeaponSouth(); break;}
        case Weapon::FaceDirection::SOUTHWEST:{ Weapon::faceWeaponSouthWest(); break;}
        case Weapon::FaceDirection::WEST:{ Weapon::faceWeaponWest(); break;}
        case Weapon::FaceDirection::NORTHWEST:{ Weapon::faceWeaponNorthWest(); break;}
        case Weapon::FaceDirection::GROUND_NORTH:{ Weapon::faceWeaponGroundNorth(); break;}
    }
}

void Weapon::setWeaponPosX(std::int16_t& x){xWeaponPos = x;}
void Weapon::setWeaponPosY(std::int16_t& y){yWeaponPos = y;}
std::int16_t& Weapon::getWeaponPosX(){return xWeaponPos;}
std::int16_t& Weapon::getWeaponPosY(){return yWeaponPos;}

void Weapon::setWeaponRenderPosX(std::int16_t& x){xRenderPos = x;}
void Weapon::setWeaponRenderPosY(std::int16_t& y){yRenderPos = y;}

std::int16_t& Weapon::getWeaponRenderPosX(){return xRenderPos;}
std::int16_t& Weapon::getWeaponRenderPosY(){return yRenderPos;}

void Weapon::attachWeaponToHandlerBox(SDL_Rect* box){handlerBox = box;}

SDL_Rect* Weapon::getHandlerBox(){return handlerBox;}

void Weapon::moveWeaponWithHandler()
{
    if(handlerBox != nullptr)
    {
        xWeaponPos = handlerBox->x;
        yWeaponPos = handlerBox->y;
        handlerWidth = handlerBox->w;
        handlerHeight = handlerBox->h;
    }
}

void Weapon::faceBoxUp()
{
    //keep at same x position
    weapon_collisionBox.x = xWeaponPos;
    //move up collision box by attackBoxHeight
    weapon_collisionBox.y = yWeaponPos - attackBoxHeight;
    
    //width and height of collision box when facing up
    weapon_collisionBox.h = attackBoxWidth;
    weapon_collisionBox.w = attackBoxHeight;
}

void Weapon::faceBoxDown()
{
    //keep x position of enemy
    weapon_collisionBox.x = xWeaponPos;
    //move down collision box by line height and handler height
    weapon_collisionBox.y = yWeaponPos + handlerHeight;
    
    //width and height of collision box when facing down
    weapon_collisionBox.h = attackBoxWidth;
    weapon_collisionBox.w = attackBoxHeight;
}

void Weapon::faceBoxLeft()
{
     //keep at same y position
    weapon_collisionBox.y = yWeaponPos;
    //move collision box to the left by width of handler
    weapon_collisionBox.x = xWeaponPos - handlerWidth;
    
    //width and height of collision box when facing left
    //long side horizontal
    weapon_collisionBox.h = attackBoxHeight;
    weapon_collisionBox.w = attackBoxWidth;
}

void Weapon::faceBoxRight()
{
     //keep at same y position
    weapon_collisionBox.y = yWeaponPos;
    //move collision box to the right by height of collision box and handler width
    weapon_collisionBox.x = xWeaponPos + handlerWidth;
    //width and height of collision box when facing left
    //long side horizontal
    weapon_collisionBox.h = attackBoxHeight;
    weapon_collisionBox.w = attackBoxWidth;
}


void Weapon::faceBoxUpLeft()
{
    //move up collision box by attackBoxHeight
    weapon_collisionBox.y = yWeaponPos - attackBoxHeight;
    
    //move collision box to the left by handler width
    weapon_collisionBox.x = xWeaponPos - handlerWidth;
    //width and height of collision box when facing left
    //long side horizontal
    weapon_collisionBox.h = attackBoxWidth;
    weapon_collisionBox.w = attackBoxHeight;
}

void Weapon::faceBoxUpRight()
{
    //move up collision box by attackBoxHeight
    weapon_collisionBox.y = yWeaponPos - attackBoxHeight;
    
    //move collision box to the right by height of collision box and handler width
    weapon_collisionBox.x = xWeaponPos + handlerWidth;
    //width and height of collision box when facing left
    //long side horizontal
    weapon_collisionBox.h = attackBoxWidth;
    weapon_collisionBox.w = attackBoxHeight;
}

void Weapon::faceBoxDownLeft()
{
    //move down collision box by handler height
    weapon_collisionBox.y = yWeaponPos + handlerHeight;
    //move collision box to the left by  handler width
    weapon_collisionBox.x = xWeaponPos - handlerWidth;
    //width and height of collision box when facing left
    //long side horizontal
    weapon_collisionBox.h = attackBoxWidth;
    weapon_collisionBox.w = attackBoxHeight;
}

void Weapon::faceBoxDownRight()
{
    //move down collision box by weapon height and handler height
    weapon_collisionBox.y = yWeaponPos + handlerHeight;
    //move collision box to the right by height of collision box and handler width
    weapon_collisionBox.x = xWeaponPos + handlerWidth;
    //width and height of collision box when facing left
    //long side horizontal
    weapon_collisionBox.h = attackBoxWidth;
    weapon_collisionBox.w = attackBoxHeight;
}

void Weapon::faceBoxGround()
{
    //keep at same x position
    weapon_collisionBox.x = xWeaponPos;
    //keep at same y position
    weapon_collisionBox.y = yWeaponPos;
    
    
    //width and height of collision box when facing up
    weapon_collisionBox.h = weaponGroundHeight;
    weapon_collisionBox.w = weaponGroundWidth;
}

void Weapon::renderWeaponBox(SDL_Rect& camera,SDL_Renderer* gRenderer)
{
     SDL_SetRenderDrawColor(gRenderer,
                           200,
                           0,
                           0,
                           50);
    /*
    std::cout << "Weapon box :" << "x: " << weapon_collisionBox.x << " " 
                                << "y: " << weapon_collisionBox.y << " "
                                << "w: " << weapon_collisionBox.w << " "
                                << "h: " << weapon_collisionBox.h << std::endl;
    */
    
    SDL_Rect renderRect = {weapon_collisionBox.x - camera.x, weapon_collisionBox.y - camera.y, 
                            weapon_collisionBox.w, weapon_collisionBox.h};
                            
    SDL_RenderDrawRect(gRenderer,&renderRect);
}

void Weapon::suppressWeapon()
{
    weapon_collisionBox.x = 0;
    weapon_collisionBox.y = 0;
    weapon_collisionBox.w = 0; 
    weapon_collisionBox.h = 0;
}

//Collision object Functions

void Weapon::setOwnerTypeOfCollisionObject(CollisionBoxOwnerType& oType){weapon_ColliderObject.ownerType = oType;}

CollisionType Weapon::getCollisionType(){return weapon_ColliderObject.typeOfCollision;}

void Weapon::resetCollisionType(){weapon_ColliderObject.typeOfCollision = CollisionType::NONE;}

CollisionObject* Weapon::getCollisionObjectPtr(){return &weapon_ColliderObject;}

void Weapon::setDirectionOfCollision(CollisionDirection thisDirection){weapon_ColliderObject.directionOfCollision = thisDirection;}

bool Weapon::getBool_HeroTouchedWeaponOnGround()
{
    //if weapon is on ground
    if(Weapon::getWeaponState() == Weapon::WeaponState::ON_GROUND)
    {
        //if weapon collision object had collision with player
        if(Weapon::getCollisionObjectPtr()->typeOfCollision == CollisionType::HIT_PLAYER)
        {
            return true;
        }
    }
    
    return false;
}

void Weapon::logic(float& timeStep)
{
	
}

//Shows the sprite on screen
void Weapon::render(SDL_Rect& camera, SDL_Renderer* gRenderer, SDL_Rect* clip)
{
     //render weapon collision box
    //Weapon::renderWeaponBox(camera,gRenderer);
    
    //render weapon sprite with animation
    //increment frame count
    Weapon::incrementFrameCount();
    
    //std::cout << "sprite render called! \n";
    //std::cout << "clipPtr:" << clipPtr << std::endl;
    //At beginning, if clipPtr is not set.
    if(clipPtr == nullptr)
    {
        if( weapon_clips != nullptr)
        {
            //face right
            clipPtr = &(*weapon_clips)[Weapon::RIGHT_1];
        }
        
    }
    
    if(weapon_sprite_sheet_ptr != nullptr)
    {
        std::int16_t x = Weapon::getWeaponRenderPosX() - camera.x;
        std::int16_t y = Weapon::getWeaponRenderPosY() - camera.y;
        //std::cout << "Coordinates: " << Sword::getCollisionObjectPtr()->ptrToCollisionBox->x
        //<< ", " << Sword::getCollisionObjectPtr()->ptrToCollisionBox->y  << std::endl;
        weapon_sprite_sheet_ptr->render( x, y, gRenderer, clipPtr + frameOffset );
    }
}

bool Weapon::checkCollisionWithWeapon(SDL_Rect& thisBox)
{
	return checkCollision(weapon_collisionBox,thisBox);
} 

void Weapon::SetHeightFromGround(std::int16_t height)
{
	heightFromGround = height;
}
