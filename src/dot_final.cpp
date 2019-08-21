#include "dot_final.h"


//constructor
Dot::Dot(int x , int y, int width, int height)
{
    //std::cout << "Dot constructor called! \n";

    //Initialize position
	mPosX = 0;
	mPosY = 0;

    //Initialize the velocity
    mVelX = 0;
    mVelY = 0;


   //Initialize the collision box
    mBox.x = x;
    mBox.y = y;
    xClipPosOffset = x;
    yClipPosOffset = y;
	mBox.w = width;
	mBox.h = height;

	//Initialize space box
    spaceBox.x = x - width - xClipPosOffset;
    spaceBox.y = y - height - yClipPosOffset;
    spaceBox.w = 2 * width;
    spaceBox.h = 2 * height;
    
    
    //Initialze collision object rectangle pointer
    dotCollisionObject.ptrToCollisionBox = &mBox;
}

//Destructor
Dot::~Dot()
{
    //std::cout << "Dot destructor called! \n";

    //set collision box to zero
    mBox.x = 0; mPosX = 0;
    mBox.y = 0; mPosY = 0;

	mBox.w = 0;
	mBox.h = 0;

    spaceBox.x=0; spaceBox.y = 0; spaceBox.w=0; spaceBox.h=0;
}

void Dot::setSpeed(float& speed){DOT_VEL = speed;}

void Dot::setPosX(float& x)
{
    int colX = (int)x;
    mPosX = x;
    mBox.x = colX + mBox.w;
    spaceBox.x= colX;
}

void Dot::setPosY(float& y)
{
    int colY = (int)y;
    mPosY = y;
    mBox.y = colY + mBox.h;
    spaceBox.y= colY;
}

void Dot::setVelX(float& dx){mVelX = dx;}

void Dot::setVelY(float& dy){mVelY = dy;}

void Dot::handleEvent(Event& thisEvent)
{
    switch(thisEvent)
    {
        case Event::UP_ARROW:{ mVelY -= DOT_VEL; break;}
        case Event::DOWN_ARROW:{ mVelY += DOT_VEL; break;}
        case Event::LEFT_ARROW:{ mVelX -= DOT_VEL; break;}
        case Event::RIGHT_ARROW:{ mVelX += DOT_VEL; break;}
        
        //if repeating, keep at same velocity
        case Event::UP_ARROW_REPEAT:{ break;}
        case Event::DOWN_ARROW_REPEAT:{ break;}
        case Event::LEFT_ARROW_REPEAT:{ break;}
        case Event::RIGHT_ARROW_REPEAT:{ break;}
        
        //if released, stop
        case Event::UP_ARROW_RELEASE:{ mVelY = 0; break;}
        case Event::DOWN_ARROW_RELEASE:{  mVelY = 0; break;}
        case Event::LEFT_ARROW_RELEASE:{ mVelX = 0; break;}
        case Event::RIGHT_ARROW_RELEASE:{ mVelX = 0; break;}
        
        //if space pressed, keep player moving
        case Event::SPACE:{ break;}
        
        case Event::NONE:{ break;}
        default:{ mVelX = 0; mVelY = 0; break;}
    }
}


void Dot::move(float& timeStep)
{
    
    //Dot::setKeyPress(Dot::KeyPress::NONE);
    
    //Move the dot left or right
    mPosX += mVelX * timeStep; /*This piece of code was originally from Lazy Foo' Productions
(http://lazyfoo.net/)*/

    //update collision box poition x
    int colX = static_cast<int>(mPosX);
    //center collision box on dot
    mBox.x = colX + xClipPosOffset;
    spaceBox.x = colX ;

    //Move the dot up or down
    mPosY += mVelY * timeStep; /*This piece of code was originally from Lazy Foo' Productions
(http://lazyfoo.net/)*/

    //update collision box poition y
    int colY = static_cast<int>(mPosY);
    mBox.y = colY + yClipPosOffset;
    spaceBox.y = colY;

}


#ifdef DUNGEON_TILE_H

bool Dot::moveOnTiles(float& timeStep, std::vector<DungeonTile*> &dungeonTiles ) //dot checks collision against tiles now
{
    Dot::move(timeStep);

    //if dot touches a wall tile
    if(touchesDungeonWallVector( Dot::getCollisionBox(), dungeonTiles ) )
    {
        //return false to indicate dot is not moving on tiles
        return false;
    }
    //return true to indicate dot is moving on tiles
    else{return true;}
}

DungeonTile::TileType Dot::moveOnTiles_TileType(float& timeStep, std::vector<DungeonTile*> &dungeonTiles)
{
    Dot::move(timeStep);

    //return tile type dot touches
    return touchesDungeonTile(Dot::getCollisionBox(),dungeonTiles); 
}

#endif

void Dot::moveBack(float& timeStep)
{
    mPosX -= mVelX * timeStep;
    mPosY -= mVelY * timeStep;
}


void Dot::setPlace(std::int16_t& screenWidth, std::int16_t& screenHeight)
{
    SCREEN_WIDTH = screenWidth;
    SCREEN_HEIGHT = screenHeight;
}


void Dot::setCamera( SDL_Rect& camera  ) //set camera relative to dot and intialize screen and level dimensions
{
	//Center the camera over the dot
	camera.x = ( (int)mPosX + mBox.w / 2  ) - (SCREEN_WIDTH / 2) ;
	camera.y = ( (int)mPosY + mBox.h / 2 ) - (SCREEN_HEIGHT / 2);

	//Keep the camera in bounds
	if( camera.x < 0 )
	{
		camera.x = 0;
	}
	if( camera.y < 0 )
	{
		camera.y = 0;
	}
}


float Dot::getPosX(){return mPosX;}

float Dot::getPosY(){return mPosY;}

int Dot::getHeight(){return mBox.h;}

int Dot::getWidth(){return mBox.w;}

float Dot::getVelX(){return mVelX;}

float Dot::getVelY(){return mVelY;}

float Dot::getSpeed(){return DOT_VEL;}

void Dot::render(SDL_Rect& camera, SDL_Renderer* lRenderer, SDL_Rect* clip )
{
    //std::cout << "clip:" << clip << std::endl;
    //Show the dot
    if(dotImage != nullptr)
    {
        dotImage->render( (int)mPosX - camera.x , (int)mPosY - camera.y , lRenderer, clip );
    }
	
}

void Dot::setCollisionBox(SDL_Rect& box){mBox = box;}

SDL_Rect& Dot::getCollisionBox()
{
    return mBox;
}

SDL_Rect& Dot::getSpaceBox()
{
    return spaceBox;
}

void Dot::placeChar(int x, int y)
{
    mPosX = (float)x; mPosY = (float)y;

    mBox.x = x; mBox.y = y;

    spaceBox.x = x; spaceBox.y = y;

}

bool Dot::loadMedia(LTexture* thisTex, std::string path,SDL_Renderer* gRenderer)
{
    bool success = true;
    
    //Load texture of the dot
    if(!thisTex->loadFromFile(path,gRenderer))
    {
        success = false;
        //std::cout << "Dot image loading failed! \n";
    }
    else
    { 
        //std::cout << "dot image loaded! \n";
        Dot::setPointerToTexture(thisTex);
    }
    
    return success;
}

void Dot::setPointerToTexture(LTexture* thisTex){dotImage = thisTex;}
LTexture* Dot::getPointerToTexture(){return dotImage;}

//Collision object Functions

void Dot::setOwnerTypeOfCollisionObject(CollisionBoxOwnerType& oType)
{
    dotCollisionObject.ownerType = oType;
}

CollisionType Dot::getCollisionType(){return dotCollisionObject.typeOfCollision;}

void Dot::resetCollisionType(){dotCollisionObject.typeOfCollision = CollisionType::NONE;}

CollisionObject* Dot::getCollisionObjectPtr(){return &dotCollisionObject;}
