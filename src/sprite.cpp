#include "sprite.h"



//constructor
Sprite::Sprite(int x,int y,int width,int height) : Dot(x,y,width,height)
{

    //std::cout << "\n Sprite constructor called! \n";

    //std::cout << "SpaceBox width and height:" << Sprite::getSpaceBox().w << Sprite::getSpaceBox().h;

    
    //initialize sprite state
    Sprite::setSpriteState(Sprite::State::STAND);
    
    //initialize frame offset
    frameOffset = 0;
    
    //initialize frames passed count 
    framesPassedCount = 0;
}

Sprite::~Sprite()
{
    //std::cout << "\n Sprite destructor called! \n";

    clipPtr = nullptr;
}

void Sprite::setSpeed(float& speed){Dot::setSpeed(speed);}

void Sprite::setPosX(float& x){Dot::setPosX(x);}

void Sprite::setPosY(float& y){Dot::setPosY(y);}

void Sprite::setVelX(float& dx){Dot::setVelX(dx);}

void Sprite::setVelY(float& dy){Dot::setVelY(dy);}

bool Sprite::loadMedia(LTexture* thisTex, std::string path,SDL_Renderer* gRenderer)
{
    return Dot::loadMedia(thisTex,path,gRenderer);
}

void Sprite::setPointerToTexture(LTexture* thisTex){Dot::setPointerToTexture(thisTex);}
LTexture* Sprite::getPointerToTexture(){return Dot::getPointerToTexture();}

void Sprite::setSpriteClips(std::vector <SDL_Rect> *this_clips)
{
    //set vector of clips equal to clip boxes
    clips = this_clips;

    //set address of clip pointer to nullptr
    clipPtr = nullptr;
}

std::vector <SDL_Rect> *Sprite::getSpriteClips(){return clips;}

void Sprite::handleEvent(Event& thisEvent)
{

    Dot::handleEvent(thisEvent);

    switch(thisEvent)
    {
        case Event::UP_ARROW:{ Sprite::setSpriteState(Sprite::State::WALK); break;}
        case Event::DOWN_ARROW:{ Sprite::setSpriteState(Sprite::State::WALK); break;}
        case Event::LEFT_ARROW:{ Sprite::setSpriteState(Sprite::State::WALK); break;}
        case Event::RIGHT_ARROW:{ Sprite::setSpriteState(Sprite::State::WALK); break;}
        
        case Event::UP_ARROW_REPEAT:{ Sprite::setSpriteState(Sprite::State::WALK); break;}
        case Event::DOWN_ARROW_REPEAT:{ Sprite::setSpriteState(Sprite::State::WALK); break;}
        case Event::LEFT_ARROW_REPEAT:{ Sprite::setSpriteState(Sprite::State::WALK); break;}
        case Event::RIGHT_ARROW_REPEAT:{ Sprite::setSpriteState(Sprite::State::WALK); break;}
        
        case Event::NONE:{ Sprite::setSpriteState(Sprite::State::STAND); break;}
        default:{ Sprite::setSpriteState(Sprite::State::STAND); break;}
    }

}

void Sprite::setPlace(std::int16_t& screenWidth, std::int16_t& screenHeight)
{
    Dot::setPlace(screenWidth,screenHeight);
}

void Sprite::setCamera( SDL_Rect& camera  ) //set camera relative to dot and intialize screen and level dimensions
{
	Dot::setCamera(camera);
}

void Sprite::move(float& timeStep)
{
    
    Dot::move(timeStep);
    
}


bool Sprite::moveOnTiles(float& timeStep, std::vector<DungeonTile*> &dungeonTiles)
{
    bool wallCollide = Dot::moveOnTiles(timeStep, dungeonTiles);
    Sprite::setDirection();
    Sprite::setMoveClip();
    Sprite::setFrame();
    
    return wallCollide;
}

DungeonTile::TileType Sprite::moveOnTiles_TileType(float& timeStep, std::vector<DungeonTile*> &dungeonTiles)
{
    
    //return tile type dot touches
    DungeonTile::TileType tileType = Dot::moveOnTiles_TileType(timeStep, dungeonTiles);
    Sprite::setDirection();
    Sprite::setMoveClip();
    Sprite::setFrame();
    
    return tileType;
}


void Sprite::moveBack(float& timeStep)
{
    Dot::moveBack(timeStep);
}

void Sprite::setFaceDirection(Sprite::FaceDirection dir){faceDirection = dir;}
Sprite::FaceDirection Sprite::getFaceDirection(){return faceDirection;}

void Sprite::setDirection()
{
    // std::cout << "new x:" << mVelX << " new y:" << mVelY << std::endl;
    
    //directional bools, show which direction sprite is currently facing
    bool north;
    bool south;
    bool west;
    bool east;
    
    //west or east
    if(Sprite::getVelX() < 0){ west=true; east=false;}
    else if(Sprite::getVelX() > 0){ west=false; east=true;}
    else if( Sprite::getVelX() == 0){ west=false; east=false;}

   // std::cout << "west:" << west << "east:" << east << std::endl;

    //north or south
    if(Sprite::getVelY() < 0){north=true; south=false;}
    else if(Sprite::getVelY() > 0){north=false; south=true;}
    else if(Sprite::getVelY() == 0){north=false; south=false;}

    //std::cout << "north:" << north << "south:" << south << std::endl;
    
    // if facing north
    if(north)
    {
        //if also facing west
        if(west){Sprite::setFaceDirection(Sprite::FaceDirection::NORTHWEST);}
        //else if also facing east
        else if(east){Sprite::setFaceDirection(Sprite::FaceDirection::NORTHEAST);}
        //else if only facing north
        else{Sprite::setFaceDirection(Sprite::FaceDirection::NORTH);}
    }
    //if facing south
    else if(south)
    {
        //if also facing west
        if(west){Sprite::setFaceDirection(Sprite::FaceDirection::SOUTHWEST);}
        //else if also facing east
        else if(east){Sprite::setFaceDirection(Sprite::FaceDirection::SOUTHEAST);}
        //else if only facing south
        else{Sprite::setFaceDirection(Sprite::FaceDirection::SOUTH);}
    }
    //else if only facing east
    else if(east){Sprite::setFaceDirection(Sprite::FaceDirection::EAST);}
    //else if only facing west
    else if(west){Sprite::setFaceDirection(Sprite::FaceDirection::WEST);}
}

void Sprite::faceNorth(){Sprite::setFaceDirection(Sprite::FaceDirection::NORTH);}

void Sprite::faceSouth(){Sprite::setFaceDirection(Sprite::FaceDirection::SOUTH);}

void Sprite::faceWest(){Sprite::setFaceDirection(Sprite::FaceDirection::WEST);}

void Sprite::faceEast(){Sprite::setFaceDirection(Sprite::FaceDirection::EAST);}


void Sprite::setMoveClip()
{
    switch(Sprite::getFaceDirection())
    {
        case Sprite::FaceDirection::NORTH:{ clipPtr = &((*clips)[UP_1]); break;}
        case Sprite::FaceDirection::NORTHEAST:{ clipPtr = &((*clips)[UP_RIGHT_1]); break;}
        case Sprite::FaceDirection::EAST:{ clipPtr = &((*clips)[RIGHT_1]); break;}
        case Sprite::FaceDirection::SOUTHEAST:{ clipPtr = &((*clips)[DOWN_RIGHT_1]); break;}
        case Sprite::FaceDirection::SOUTH:{ clipPtr = &((*clips)[DOWN_1]); break;}
        case Sprite::FaceDirection::SOUTHWEST:{ clipPtr = &((*clips)[DOWN_LEFT_1]); break;}
        case Sprite::FaceDirection::WEST:{ clipPtr = &((*clips)[LEFT_1]); break;}
        case Sprite::FaceDirection::NORTHWEST:{ clipPtr = &((*clips)[UP_LEFT_1]); break;}
    }
}

void Sprite::setFrame()
{
    int fCount = Sprite::getFrameCount();
    
    //if frame count is more than 2, reset
    //divide frame count by 3 frames of animation to slow down animation
    // How integers work: 0/4 == 0 1/4 == 0 2/4 == 0 3/4 = 0 4/4 = 0
    //after 4th frame, reset frame count
    if(fCount/4 > 3){Sprite::resetFrameCount();}
    
    if(Sprite::getSpriteState() == Sprite::State::STAND){frameOffset = 2;}
    else if(Sprite::getSpriteState() == Sprite::State::WALK)
    {
        //stand
        if(fCount/4 == 0){frameOffset = 0;}
        //step with left
        else if(fCount/4 == 1){frameOffset = 1;}
        //stand
        else if(fCount/4 == 2){frameOffset = 2;}
        //step with right
        else if(fCount/4 == 3){frameOffset = 3;}
    }
    
}

void Sprite::incrementFrameCount(){framesPassedCount++;}
std::int8_t Sprite::getFrameCount(){return framesPassedCount;}
void Sprite::resetFrameCount(){framesPassedCount = 0;}

void Sprite::setFrameOffset(std::int8_t& thisOffset){frameOffset = thisOffset;}
std::int8_t Sprite::getFrameOffset(){return frameOffset;}

void Sprite::setNumberOfAnimationFrames(std::int8_t& numFrames){numberOfFramesOfAnimation = numFrames;}
std::int8_t Sprite::getNumberOfFramesOfAnimation(){return numberOfFramesOfAnimation;}

void Sprite::setClipToShow(SDL_Rect* clip){ clipPtr = clip;}
SDL_Rect* Sprite::getClipToShow(){return clipPtr;}

void Sprite::setSpriteState(Sprite::State state){spriteState = state;}
Sprite::State Sprite::getSpriteState(){return spriteState;}

void Sprite::render(SDL_Rect& camera, SDL_Renderer* gRenderer, SDL_Rect* clip)
{
    //increment frame count
    Sprite::incrementFrameCount();
    
    //std::cout << "sprite render called! \n";
    //std::cout << "clipPtr:" << clipPtr << std::endl;
    //At beginning, if clipPtr is not set.
    if(clipPtr == nullptr)
    {
        //face down
        clipPtr = &((*clips)[DOWN_1]);
    }
    
    //render dot
    Dot::render(camera,gRenderer,clipPtr + frameOffset );
}

float Sprite::getPosX()
{
    return Dot::getPosX();
}

float Sprite::getPosY()
{
    return Dot::getPosY();
}

int Sprite::getHeight()
{
    return Dot::getHeight();
}

int Sprite::getWidth()
{
    return Dot::getWidth();
}

float Sprite::getVelX()
{
    return Dot::getVelX();
}

float Sprite::getVelY()
{
    return Dot::getVelY();
}

float Sprite::getSpeed()
{
    return Dot::getSpeed();
}

void Sprite::placeChar(int x, int y)
{
    Dot::placeChar(x,y);
}

//set dot's collision box
void Sprite::setCollisionBox(SDL_Rect& box){Dot::setCollisionBox(box);}

SDL_Rect& Sprite::getCollisionBox(){return Dot::getCollisionBox();}

SDL_Rect& Sprite::getSpaceBox()
{
    return Dot::getSpaceBox();
}

//Collision object Functions

void Sprite::setOwnerTypeOfCollisionObject(CollisionBoxOwnerType& oType)
{
    Dot::setOwnerTypeOfCollisionObject(oType);
}

CollisionType Sprite::getCollisionType(){return Dot::getCollisionType();}

void Sprite::resetCollisionType(){Dot::resetCollisionType();}

CollisionObject* Sprite::getCollisionObjectPtr(){return Dot::getCollisionObjectPtr();}
