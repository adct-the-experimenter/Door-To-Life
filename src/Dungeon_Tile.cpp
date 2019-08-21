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
            default:{std::cout<< "Invalid number for tile type! \n";}

        }
}

void DungeonTile::setTileEmpty()
{
	DungeonTile::setType(DungeonTile::TileType::EMPTY);
}

bool readLoadTiles(std::string path,int numberBytes, int totalTiles)
{
    /*
      //This piece of code was originally from Lazy Foo' Productions
//(http://lazyfoo.net/)
    //std::cout << "readLoadTiles function called! \n";

    bool tilesLoaded = true;

    //Open the map file
    std::ifstream map(path);

    //If the map couldn't be loaded
    if( map == NULL )
    {
		std::cout << "Unable to load map file!\n";
		std::cerr<< "File could not be opened! \n";
		tilesLoaded = false;

    }
    //Initialize the tile type
	else
	{
            long int location = (numberBytes/totalTiles) * ( DungeonTile::getTileNumber());
            std::cout << "location:"<<location<<std::endl;

            //set next position of bytes to read file from
            map.seekg( location ,std::ios::beg);


            //Determines what kind of tile will be made
			int tileType = -1;

			//Read tile from map file
			map >> tileType;


            std::cout <<"Tile Number: " << DungeonTile::getTileNumber() << " TileType: " << tileType << " address: "<< map << tileType << std::endl;


			//If there was a problem in reading the map
			if( map.fail() )
			{
				//Stop loading map
				std::cout << "Error loading map: Unexpected end of file!\n";
				tilesLoaded= false;
			}


            //If the number is a valid tile number
            if( ( tileType >= 0 ) && ( tileType < TOTAL_TILE_SPRITES + 1  ) )
            {
                //assign tile type read from map file to tile's private member mType
                DungeonTile::setType((DungeonTile::TileType)tileType);

            }

            //If we don't recognize the tile type
            else
            {
                //Stop loading map
                std::cout <<"Error loading map: Invalid tile type at !\n";
                tilesLoaded = false;
            }
    }

    //Close the file
    map.close();

    return tilesLoaded;
     * 
*/
	return false;
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

/** Save Function**/
bool DungeonTile::writeSaveTiles(std::string path,int numberBytes, int totalTiles)
{
    /*
      
    // This piece of code was originally from Lazy Foo' Productions
//(http://lazyfoo.net/)

    bool tilesSaved = true;

    //write the map file
    std::ofstream mapOutput(path);

    //If the map couldn't be written
    if( mapOutput == NULL )
    {
		std::cout << "Unable to load map file!\n";
		std::cerr<< "File could not be opened! \n";
		tilesSaved = false;
    }
    //Initialize the tile type
	else
	{

        long int location = (numberBytes/totalTiles) * ( DungeonTile::getTileNumber());

        //set next position of bytes to write to file
        mapOutput.seekp( location ,std::ios::beg);

        //Determines what kind of tile will be made
        int tileType = -1;
        tileType = (int)DungeonTile::getType();

        //write tile type to map file

        mapOutput << tileType;


        std::cout <<"Tile Number: " << DungeonTile::getTileNumber() << " TileType: " << tileType << " address: "<< mapOutput << tileType << std::endl;

    }

    //Close the file
    mapOutput.close();

    return tilesSaved;
    */

	return false;
}

bool writeSaveTiles_SDLRW()
{
	return false;
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
