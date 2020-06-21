#include "Dungeon_Tile.h"



SDL_Rect* getTileBoxPointer(DungeonTile* thisTile){return &thisTile->mBox;}

bool touchesDungeonWallVector( SDL_Rect& box, std::vector<DungeonTile*> &dungeonTiles )
{
    
    //std::cout << "touchesDungeonWall function called! \n";
    //Go through the tiles
    for( size_t i = 0; i < dungeonTiles.size(); ++i )
    {
        //if dungeon tile is a wall tile
        if(dungeonTiles[i]->getTypeWall())
        {
            if(checkCollision(box ,dungeonTiles[i]->getBox() ) )
            {
                return true;
            }
        }

    }

    return false;
}

DungeonTile::TileType touchesDungeonTile(SDL_Rect& box, 
                                        std::vector<DungeonTile*> &dungeonTiles)
{
    
    for( size_t i = 0; i < dungeonTiles.size(); ++i )
    {
        if(checkCollision(box ,dungeonTiles[i]->getBox() ) )
        {
            return dungeonTiles[i]->getType();
        }
    }
}


DungeonTile::DungeonTile( std::int16_t& x, std::int16_t& y, 
                        std::int16_t& width, std::int16_t& height, 
                        std::int16_t& tileNumber )
{

    //Get the offsets
    mBox.x = x;
    mBox.y = y;

    //Set the collision box
    TILE_WIDTH = width;
    TILE_HEIGHT = height;

    mBox.w = TILE_WIDTH ; //Tile_width
    mBox.h = TILE_HEIGHT; //Tile_Height

    //set tile number
    mNumber = tileNumber;

    //initialize tile type
    DungeonTile::setType(DungeonTile::TileType::RED);


    //initialize tile bools
    floorTileBool = false;
    wallTileBool = false;
    exitTileBool = false;
    emptyTileBool = false;
}

DungeonTile::~DungeonTile()
{
    //std::cout<< "Dungeon Tile destructor called! \n";
//    tileTextureMap.free();

    //set dTileClip rectangle to zero
    dTileClip.x=0; dTileClip.y=0; dTileClip.w=0; dTileClip.h=0;

    //set collision box equal to zero
    mBox.x=0; mBox.y=0; mBox.w=0; mBox.h=0;

}



/** Setup Tiles**/


void DungeonTile::setTileClips()
{
    //setup tile rectangle clip

    //for graphic tiles, set door as a red tile in rendering
    switch(DungeonTile::getType())
        {
            case DungeonTile::TileType::RED:{ dTileClip = redTile; break;}
            case DungeonTile::TileType::GREEN:{ dTileClip = greenTile; break;}
            case DungeonTile::TileType::BLUE:{  dTileClip = blueTile; break;}
            case DungeonTile::TileType::TOP_LEFT:{ dTileClip = topLeftTile; break;}
            case DungeonTile::TileType::LEFT: { dTileClip = leftTile; break;}
            case DungeonTile::TileType::BOTTOM_LEFT:{ dTileClip=bottomLeftTile; break;}
            case DungeonTile::TileType::TOP:{ dTileClip = topTile; break;}
            case DungeonTile::TileType::CENTER:{ dTileClip=centerHoleTile; break;}
            case DungeonTile::TileType::BOTTOM:{ dTileClip=bottomTile; break;}
            case DungeonTile::TileType::TOP_RIGHT:{ dTileClip=topRightTile; break;}
            case DungeonTile::TileType::RIGHT: {dTileClip=rightTile; break;}
            case DungeonTile::TileType::BOTTOM_RIGHT:{ dTileClip=bottomRightTile; break;}
            case DungeonTile::TileType::EXIT:{ dTileClip=exitTile; break;}
            case DungeonTile::TileType::DOOR:{ dTileClip = redTile; break;}
            case DungeonTile::TileType::OCCUPIED:{dTileClip = redTile; break;}
            case DungeonTile::TileType::INVISIBLE_WALL:{dTileClip = invisibleWallTile; break;}
            case DungeonTile::TileType::DUNGEON_ENTRANCE:{dTileClip = dungeonEntranceTileClip; break;}
            default:{std::cout<< "Invalid number for tile type! \n";}

        }
}

void DungeonTile::setTileEmpty()
{
	DungeonTile::setType(DungeonTile::TileType::EMPTY);
}


/*
bool DungeonTile::loadMedia(LTexture* ptrToTileMap)
{
    bool success = true;
    
    //load texture for member tileTextureMap
    tileTextureMap = ptrToTileMap;
    if(tileTextureMap == nullptr){success = false;}
    
    return success;
}
*/

/** Make Tiles**/



void DungeonTile::randomGenerateTile(int randomNumber)
{
    //std::cout << "Tile Number: " << DungeonTile::getTileNumber() << " randTileType: " << randomNumber << std::endl;
    //assign random number to tile type member
    DungeonTile::setType( (DungeonTile::TileType)randomNumber);
}





void DungeonTile::genRuleAllowExit( int randomNumber)
{
    if(DungeonTile::getTypeExit() == true)
    {
        if(randomNumber >= 5 )
        {
            exitAllowed = true;
        }
        else
        {
            exitAllowed = false;
        }

    }
    else {exitAllowed = false;}

}

void DungeonTile::genRuleChangeExitTile()
{
    //if tile is an exit tile and not allowed
    if(!DungeonTile::exitAllowed  && DungeonTile::getTypeExit() )
    {
        DungeonTile::setType(DungeonTile::TileType::CENTER);
      //  std::cout << "Exit tile changed to wall tile! \n";
    }
    else {}

}


/**Render Tiles **/
void DungeonTile::render( LTexture* tileTextureMap,SDL_Rect& camera, SDL_Renderer* gRenderer )
{
    //If the tile is on screen
    if( checkCollision( camera, mBox ) )
    {
        if(tileTextureMap != nullptr)
        {
            int renderX; int renderY; 
            renderX = mBox.x - camera.x;
            renderY = mBox.y - camera.y;
            
            //Show the tile
            tileTextureMap->render( renderX  , renderY , gRenderer, &dTileClip );
        }
        
    }
}

/** Tile atrributes **/
void DungeonTile::setType( DungeonTile::TileType tileType)
{
 //set bools for what tile type is for future reference
    switch(tileType)
    {
        //floor
        case DungeonTile::TileType::RED:{floorTileBool = true; exitTileBool = false; wallTileBool = false; emptyTileBool = false; break;}
        case DungeonTile::TileType::GREEN:{floorTileBool = true; exitTileBool = false; wallTileBool = false; emptyTileBool = false; break;}
        case DungeonTile::TileType::BLUE:{floorTileBool = true; exitTileBool = false; wallTileBool = false; emptyTileBool = false; break;}
        //wall
        case DungeonTile::TileType::TOP_LEFT:{floorTileBool = false; exitTileBool = false; wallTileBool = true; emptyTileBool = false; break;}
        case DungeonTile::TileType::LEFT:{floorTileBool = false; exitTileBool = false; wallTileBool = true; emptyTileBool = false; break;}
        case DungeonTile::TileType::BOTTOM_LEFT:{floorTileBool = false; exitTileBool = false; wallTileBool = true; emptyTileBool = false; break;}
        case DungeonTile::TileType::TOP:{floorTileBool = false; exitTileBool = false; wallTileBool = true; emptyTileBool = false; break;}
        case DungeonTile::TileType::CENTER:{floorTileBool = false; exitTileBool = false; wallTileBool = false; emptyTileBool = false; break;}
        case DungeonTile::TileType::BOTTOM:{floorTileBool = false; exitTileBool = false; wallTileBool = true; emptyTileBool = false; break;}
        case DungeonTile::TileType::TOP_RIGHT:{floorTileBool = false; exitTileBool = false; wallTileBool = true; emptyTileBool = false; break;}
        case DungeonTile::TileType::RIGHT:{floorTileBool = false; exitTileBool = false; wallTileBool = true; emptyTileBool = false; break;}
        case DungeonTile::TileType::BOTTOM_RIGHT:{floorTileBool = false; exitTileBool = false; wallTileBool = true; emptyTileBool = false; break;}
        case DungeonTile::TileType::INVISIBLE_WALL:{floorTileBool = false; exitTileBool = false; wallTileBool = true; emptyTileBool = false; break;}
        //exit
        case DungeonTile::TileType::EXIT:{floorTileBool = false; exitTileBool = true; wallTileBool = false; emptyTileBool = false; break;}
        //empty
        case DungeonTile::TileType::EMPTY:{floorTileBool = false; exitTileBool = false; wallTileBool = false; emptyTileBool = true; break;}
        //door
        case DungeonTile::TileType::DOOR:{ floorTileBool = false; exitTileBool = false; wallTileBool = false; emptyTileBool = false; break;}
        case DungeonTile::TileType::OCCUPIED:{ floorTileBool = false; exitTileBool = false; wallTileBool = false; emptyTileBool = false; break;}
        case DungeonTile::TileType::DUNGEON_ENTRANCE:{ floorTileBool = true; exitTileBool = false; wallTileBool = false; emptyTileBool = false; break;}
    }
    
    //set tile type
    mType = tileType;

}

DungeonTile::TileType DungeonTile::getType(){return mType;}

bool DungeonTile::getTypeFloor(){return floorTileBool;}

bool DungeonTile::getTypeWall(){return wallTileBool;}

bool DungeonTile::getTypeExit(){return exitTileBool;}

bool DungeonTile::getTypeEmpty(){return emptyTileBool;}

SDL_Rect& DungeonTile::getBox(){return mBox;}

int DungeonTile::getXPosition(){return (int)mBox.x;}

int DungeonTile::getYPosition(){return (int)mBox.y;}

int DungeonTile::getTileNumber(){return mNumber;}
