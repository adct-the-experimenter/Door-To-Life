#include "Dungeon.h"

    
bool loadDungeonMedia(SDL_Renderer* gRenderer,LTexture* tileMap,
ALuint* source,ALuint* buffer)
{
    bool success = true;
    
    std::string tileFilePath = DATADIR_STR + std::string("/Graphics/tiles-alt.png");
    //load texture for member tileTextureMap
    if(!tileMap->loadFromFile(tileFilePath.c_str(), gRenderer))
    {
        std::cout << "Couldn't load tileTextureMap! \n";
        return false;
    }
    else
    {
        //if tileTextureMap loaded successfully
        
        std::string path = std::string("/Sound/Threshing-Floor-VG-Ambient-Beautiful-Haunting-Remix.ogg");
        if(!LoadBuffer(buffer,path))
        {
			printf("Failed to load dungeon music! \n");
			return false;
		}
        else
        {
            //setup source of dungeon music
            alGenSources(1, source); //allocate source 

            alSource3f(*source, AL_POSITION, 0.0f, 1.0f, 0.0f); //source position is above player(origin)
            alSource3f(*source, AL_VELOCITY, 0.0f, 0.0f, 0.0f); //source is not moving
            
            //attach buffer to source
			alSourcei(*source, AL_BUFFER, (ALint)(*buffer));
            
        }        
    }
    
    return success;
}

void freeDungeonMedia(LTexture* tileMap,
                        ALuint* source,ALuint* buffer)
{
    //free source
    alDeleteSources(1, source); // delete source
    
    //free buffer
	alDeleteBuffers(1, buffer); //delete buffer
    
    //free tile texture map
    tileMap->free();
}


Dungeon::Dungeon()
{
    //std::cout << "Dungeon constructor called! \n";
    //start off with running state
    Dungeon::setState(GameState::State::RUNNING);
	
	m_player_manager_ptr = nullptr;
	mainInventoryPtr = nullptr;
	
	exitTilePtr = nullptr;

}

Dungeon::~Dungeon()
{
    //std::cout << "Dungeon destructor called! \n";

     //Set lCamera values to zero
    lCamera.x =0; lCamera.y=0; lCamera.w=0; lCamera.h=0;

    //set main sprite pointer to NULL
    mainDotPointer = nullptr;
    

}

void Dungeon::SetPointerToPlayerManager(PlayerManager* pm){m_player_manager_ptr = pm;}

void Dungeon::SetPointerToGameInventory(GameInventory* thisInventory){mainInventoryPtr = thisInventory;}

void Dungeon::GenerateEmptyDungeonForXMLLoad()
{
	std::int16_t startX = 0;
    std::int16_t startY = 0;
    
    std::int16_t numTiles = 0;
    
    std::int16_t tileWidth = globalTileWidth;
    std::int16_t tileHeight = globalTileHeight;

    //calculate number of tiles in dungeon
    numTiles = (LEVEL_WIDTH / tileWidth) * (LEVEL_HEIGHT / tileHeight);
    
    Dungeon::createBlankTiles(startX,startY,
                            tileWidth,tileHeight,
                            numTiles);
}

void Dungeon::GenerateBaseDungeon()
{
	std::int16_t startX = 0;
    std::int16_t startY = 0;
    
    std::int16_t numTiles = 0;
    
    std::int16_t tileWidth = globalTileWidth;
    std::int16_t tileHeight = globalTileHeight;

    //calculate number of tiles in dungeon
    numTiles = (LEVEL_WIDTH / tileWidth) * (LEVEL_HEIGHT / tileHeight);
    
    Dungeon::createBlankTiles(startX,startY,
                            tileWidth,tileHeight,
                            numTiles);
    
    //set tile clips
    Dungeon::setTiles();
}

void Dungeon::setLevelDimensions(std::int16_t& levelWidth, std::int16_t& levelHeight)
{
 LEVEL_WIDTH = levelWidth;
 LEVEL_HEIGHT = levelHeight;
}
    
void Dungeon::setPointerToMainDot(Dot* thisDot){mainDotPointer = thisDot;}
void Dungeon::setPointerToTimer(LTimer* thisTimer){timer = thisTimer;}

void Dungeon::setPointersToMedia(LTexture* tileMap,ALuint* source,ALuint* buffer)
{
    tileTextureMap = tileMap;
    dgmSource = source;
    dgmBuffer = buffer;
}

void Dungeon::createBlankTiles(std::int16_t &start_x, std::int16_t& start_y,
                                    std::int16_t& tileWidth, std::int16_t& tileHeight,
                                    std::int16_t& numTiles)
{
    //resize dungeonTileSet vector to number of tiles
    dungeonTileSet.resize(numTiles);
    
    //Starting position of tiles for mapping
    std::int16_t dTile_X = start_x; 
    std::int16_t dTile_Y = start_y;
    
    NODE_X = start_x;
    NODE_Y = start_y;
    
    TILE_WIDTH = tileWidth;
    TILE_HEIGHT = tileHeight;
    
    numXNodeColumns = LEVEL_WIDTH / tileWidth;
    numYNodeRows = LEVEL_HEIGHT / tileHeight;
   
   //resize node look up vector
   
    //resize node look up x divisions columns
    dungeon_tile_look_up.resize(numXNodeColumns);
    
    for(size_t xCol=0; xCol < numXNodeColumns; xCol++)
    {
        dungeon_tile_look_up[xCol].resize(numYNodeRows);
    }

    size_t xCol = 0;
    size_t yRow = 0;

    for(size_t i = 0; i < dungeonTileSet.size(); ++i)
    {
        std::int16_t tileNumber = i;
        dungeonTileSet[i] = new DungeonTile(dTile_X,dTile_Y,tileWidth,tileHeight,tileNumber);
		
		//dungeonTileSet[i]->setType(DungeonTile::TileType::GREEN);
        
        dungeon_tile_look_up [xCol] [yRow] = dungeonTileSet[i];
        
        //move to next tile spot
        dTile_X += tileWidth;
        xCol += 1;
        
        //if dTile_x is at end of level width
        if(dTile_X > (start_x + LEVEL_WIDTH ) - tileWidth)
        {
            //move to next row
            dTile_Y += tileHeight;
            yRow += 1;
            //start from beginning
            dTile_X = start_x;
            xCol = 0;
        }
    }

}

void Dungeon::setTiles()
{
    //std::cout << "set tile clips called! \n";
    //Set tile clips
    for(size_t i = 0; i < dungeonTileSet.size(); ++i)
    {
        dungeonTileSet[i]->setTileClips();
    }
}

void Dungeon::deleteTiles()
{
        //free the tiles allocated in bool setTiles
        for(size_t i=0; i < dungeonTileSet.size(); ++i)
        {
            //std::cout << " \n Delete tileSet element:" << i <<" Address:" << &tileSet[i];
            delete dungeonTileSet[i];
        }
}

/** Dot Functions**/

void Dungeon::setDungeonCameraForDot(std::int16_t& screenWidth, std::int16_t& screenHeight,
                            SDL_Rect& camera)
{
    //set place for dot to move in
    mainDotPointer->setPlace(screenWidth,screenHeight);

    lCamera = camera;
}


void Dungeon::moveMainDot(float& timeStep)
{
  //  std::cout << "timestep: " << timeStep <<std::endl;

    //set camera over dot
    mainDotPointer->setCamera(lCamera);

    //move dot independent of frames, but rather dependent on time. includes collision detection
    mainDotPointer->moveOnTiles(timeStep, dungeonTileSet );

    //Restart timer
    timer->start();

}

void Dungeon::PlaceDotInThisLocation(float& x, float& y)
{
	mainDotPointer->setPosX(x);
    mainDotPointer->setPosY(y);
}


void  Dungeon::PlacePlayerInLocationNearEntrance()
{
	if(exitTilePtr)
	{
		
		float x = exitTilePtr->getBox().x + 80;
		float y = exitTilePtr->getBox().y + 80;
		
		mainDotPointer->setPosX(x);
		mainDotPointer->setPosY(y);
	}
	
    
}
/** Item Functions**/


void Dungeon::setTilesAroundCenterToFloor(size_t& xCol,size_t& yRow,size_t& xEndCol, size_t& yEndRow)
{
    //make tiles left,right,above,and below it floor tiles
    //left
    if(xCol - 1 <= xEndCol)
    {
        //if tile isn't wall and is a hole
        if( !dungeon_tile_look_up [xCol - 1][yRow]->getTypeWall() 
            && dungeon_tile_look_up [xCol - 1][yRow]->getType() == DungeonTile::TileType::CENTER)
            {
                dungeon_tile_look_up [xCol - 1][yRow]->setType(DungeonTile::TileType::RED);
            }
    }
    //down left
    if(xCol - 1 <= xEndCol && yRow + 1 <= yEndRow)
    {
        //if tile isn't wall and is a hole
        if( !dungeon_tile_look_up [xCol - 1][yRow + 1]->getTypeWall() 
            && dungeon_tile_look_up [xCol - 1][yRow + 1]->getType() == DungeonTile::TileType::CENTER)
            {
                dungeon_tile_look_up [xCol - 1][yRow + 1]->setType(DungeonTile::TileType::RED);
            }
    }
    //right
    if(xCol + 1 <= xEndCol)
    {
        //if tile right of door is center tile
        if( dungeon_tile_look_up [xCol + 1][yRow]->getType() == DungeonTile::TileType::CENTER)
            {
                dungeon_tile_look_up [xCol + 1][yRow]->setType(DungeonTile::TileType::RED);
            }
    }
    //down right
    if(xCol + 1 <= xEndCol && yRow + 1 <= yEndRow)
    {
        //if tile isn't wall and is a hole
        if( !dungeon_tile_look_up [xCol + 1][yRow + 1]->getTypeWall() 
            && dungeon_tile_look_up [xCol + 1][yRow + 1]->getType() == DungeonTile::TileType::CENTER)
            {
                dungeon_tile_look_up [xCol + 1][yRow + 1]->setType(DungeonTile::TileType::RED);
            }
    }
    //above
    if(yRow - 1 <= yEndRow)
    {
         if(!dungeon_tile_look_up [xCol ][yRow - 1]->getTypeWall() 
            && dungeon_tile_look_up [xCol][yRow - 1]->getType() == DungeonTile::TileType::CENTER)
            {
                dungeon_tile_look_up [xCol][yRow - 1]->setType(DungeonTile::TileType::RED);
            }
    }
    //up left
    if(xCol - 1 <= xEndCol && yRow - 1 <= yEndRow)
    {
        //if tile isn't wall and is a hole
        if( !dungeon_tile_look_up [xCol - 1][yRow - 1]->getTypeWall() 
            && dungeon_tile_look_up [xCol - 1][yRow - 1]->getType() == DungeonTile::TileType::CENTER)
            {
                dungeon_tile_look_up [xCol - 1][yRow - 1]->setType(DungeonTile::TileType::RED);
            }
    }
    //up right
    if(xCol + 1 <= xEndCol && yRow - 1 <= yEndRow)
    {
        //if tile isn't wall and is a hole
        if( !dungeon_tile_look_up [xCol + 1][yRow - 1]->getTypeWall() 
            && dungeon_tile_look_up [xCol + 1][yRow - 1]->getType() == DungeonTile::TileType::CENTER)
            {
                dungeon_tile_look_up [xCol + 1][yRow - 1]->setType(DungeonTile::TileType::RED);
            }
    }
    //below
    if(yRow + 1 <= yEndRow)
    {
        if(!dungeon_tile_look_up [xCol ][yRow + 1]->getTypeWall() 
            && dungeon_tile_look_up [xCol][yRow + 1]->getType() == DungeonTile::TileType::CENTER)
            {
                dungeon_tile_look_up [xCol][yRow + 1]->setType(DungeonTile::TileType::RED);
            }
    }
}


void Dungeon::checkKeyAndDot()
{

}



/** Game Loop Functions**/

void Dungeon::handle_events(Event& thisEvent)
{
   // std::cout << "Handle events called! \n";

    //User requests pause by pressing escape
    if( thisEvent == Event::ESCAPE )
    {
        //set pause state
        Dungeon::setState(GameState::State::PAUSE);
    }
    //User requests quit by X out window
    else if(thisEvent == Event::QUIT_WINDOW)
    {
        Dungeon::setState(GameState::State::EXIT);
    }

    mainDotPointer->handleEvent(thisEvent);

/*
    for(size_t i=0; i < (*dungeonDoorsVector).size(); ++i)
    {
        (*dungeonDoorsVector)[i]->handle_event(*event);
    }
*/
}

void Dungeon::handle_events_RNG(RNGType& rngSeed){}

void Dungeon::logic()
{
    //std::cout << "Logic called! \n";
    float timeStep = timer->getTicks() / 1000.f; //frame rate
	
	//logic for player
    if(m_player_manager_ptr != nullptr)
    {
        m_player_manager_ptr->logic(timeStep);
        //if(mainPlayerPointer->getHealth() <= 0 ){Dungeon::setState(GameState::State::GAME_OVER);}
        
        //if player hits dungeon entrance/exit
        if( checkCollision(exitTilePtr->getBox(),m_player_manager_ptr->GetPointerToPlayerOne()->getCollisionBox() ) )
        { 
			Dungeon::setState(GameState::State::NEXT);
		}
        
    }
    
    //move main dot
    Dungeon::moveMainDot(timeStep);
	
	
}

void Dungeon::exitByTile()
{
    //if dot collides with an exit tile
    for(size_t i =0; i < dungeonTileSet.size(); ++i)
        {
            if( dungeonTileSet[i]->getTypeExit() == true )
            {
                //make smaller rectangle copy of exit tile
                SDL_Rect smallerExitBox;
                smallerExitBox = dungeonTileSet[i]->getBox();

                smallerExitBox.x= dungeonTileSet[i]->getBox().x + 40; smallerExitBox.y= dungeonTileSet[i]->getBox().y + 40;
                smallerExitBox.w=10; smallerExitBox.h=10;

                if( checkCollision(mainDotPointer->getCollisionBox(), smallerExitBox ) == true 
                /*|| Dungeon::getExitState() == true */)
                {
                    //go to next state
                    Dungeon::setState(GameState::State::NEXT);
                }
            }
        }

}

void Dungeon::exitByDoor()
{
    for(size_t i=0; i < dungeonDoorsVector.size(); ++i)
    {

        //run open door logic
        dungeonDoorsVector[i].openDoorLogic();

            if( dungeonDoorsVector[i].getDoorState() == Door::State::DOOR_OPEN)
            {
                //go to next state
                Dungeon::setState(GameState::State::NEXT);
            }
    }

}

void Dungeon::checkWrongDoor()
{
    
}

void Dungeon::doorCollision(float timeStep)
{
    
    if( dungeonDoorsVector.size() == 0)
    {
        //if dot collides with door
        if( checkCollision( mainDotPointer->getCollisionBox(), 
                        dungeonDoorsVector[0].getCollisionBoxDoor1()) )
        {
            //move dot back
            mainDotPointer->moveBack(timeStep);
        }
        else if(checkCollision( mainDotPointer->getCollisionBox(), 
                        dungeonDoorsVector[0].getCollisionBoxDoor2()))
        {
            //move dot back
            mainDotPointer->moveBack(timeStep);
        }

    }
    else
    {
        for(size_t i=0;i < dungeonDoorsVector.size(); ++i)
        {
            //if dot collides with a door
            if( checkCollision( mainDotPointer->getCollisionBox(), 
                                dungeonDoorsVector[i].getCollisionBoxDoor1() ) )
            {

                //move dot back
                mainDotPointer->moveBack(timeStep);
            }
            else if(checkCollision( mainDotPointer->getCollisionBox(), 
                                dungeonDoorsVector[i].getCollisionBoxDoor2() ))
            {
                //move dot back
                mainDotPointer->moveBack(timeStep);
            }
        }
    }
     
}

//play sounds
void Dungeon::sound(AudioRenderer* gAudioRenderer)
{
    
    //play dungeon music
    //play sound from dgmSource
    alGetSourcei(*dgmSource, AL_SOURCE_STATE, &musicState);
    if (musicState == AL_STOPPED || musicState == AL_INITIAL){ alSourcePlay(*dgmSource);}

}

void Dungeon::render(SDL_Renderer* gRenderer)
{
  //  std::cout << "render called! \n";

    
    //Render level
    for( size_t i = 0; i < dungeonTileSet.size(); ++i )
    {
        dungeonTileSet[i]->render(tileTextureMap,lCamera,gRenderer);
    }

    //render dot
    mainDotPointer->render(lCamera,gRenderer);


}

void Dungeon::render(DrawingManager* gDrawManager)
{
	//Render level
    for( size_t i = 0; i < dungeonTileSet.size(); ++i )
    {
        dungeonTileSet[i]->render(tileTextureMap,*gDrawManager->GetPointerToCameraOne(),gDrawManager->GetPointerToRendererOne());
        //dungeonTileSet[i]->render(tileTextureMap,gDrawManager->GetPointerToCameraTwo(),gDrawManager->GetPointerToRendererTwo());
        //dungeonTileSet[i]->render(tileTextureMap,gDrawManager->GetPointerToCameraThree(),gDrawManager->GetPointerToRendererThree());
        //dungeonTileSet[i]->render(tileTextureMap,gDrawManager->GetPointerToCameraFour(),gDrawManager->GetPointerToRendererFour());
    }

    //render dot
    mainDotPointer->render(*gDrawManager->GetPointerToCameraOne(),gDrawManager->GetPointerToRendererOne());
}

//Set States
void Dungeon::setState(GameState::State thisState){GameState::setState(thisState);}
GameState::State Dungeon::getState(){return GameState::getState();}

int Dungeon::getDotTileNumber()
{
    for(size_t i=0; i < dungeonTileSet.size(); ++i )
    {
        if(checkCollision(mainDotPointer->getCollisionBox(), dungeonTileSet[i]->getBox() ) == true)
        {
            return dungeonTileSet[i]->getTileNumber();
        }
    }

}

int Dungeon::getTileNumberFromPosition(int x, int y)
{
    int tileNumber =0;

    std::cout << "previous x:" << x << "previous y:" << y << std::endl;

    if( x % 80 != 0 ){ x = x - (x % 80);}
    if( y % 80 != 0){ y = y  - (y % 80); }


    std::cout << "rounded x:" << x << "rounded  y:" << y << std::endl;
    
    size_t dotXCol = ( x - NODE_X ) / TILE_WIDTH;
    size_t dotYRow = ( y - NODE_Y ) / TILE_HEIGHT;
    
    if(dotXCol >= numXNodeColumns || dotYRow >= numYNodeRows){return 0;}
    else
    {
        tileNumber = dungeon_tile_look_up [dotXCol][dotYRow]->getTileNumber();
        return tileNumber;
    }
}


SDL_Rect Dungeon::getTileBox_under_dot()
{
    for(size_t i=0; i < dungeonTileSet.size(); ++i )
    {
        if( checkCollision(mainDotPointer->getCollisionBox(), dungeonTileSet[i]->getBox() ) == true)
        {
            return dungeonTileSet[i]->getBox();
        }
    }

}

DungeonTile* Dungeon::getDungeonTileFromPosition(int x, int y) 
{
    size_t xCol = ( x - NODE_X ) / TILE_WIDTH;
    size_t yRow = ( y - NODE_Y ) / TILE_HEIGHT;
    
    if(xCol >= numXNodeColumns || yRow >= numYNodeRows){return nullptr;}
    else{ return dungeon_tile_look_up [xCol] [yRow];}
}

void Dungeon::getXColYRowFromPosition(int x, int y,size_t& xCol, size_t& yRow)
{
     xCol= ( x - NODE_X ) / TILE_WIDTH;
     yRow = ( y - NODE_Y   ) / TILE_HEIGHT;
}


void Dungeon::freeResources()
{
	//Set the pointers' adressses to nullptr
    for(size_t i = 0; i < dungeonTileSet.size(); ++i)
    {
		delete dungeonTileSet[i];
        dungeonTileSet[i] = nullptr;
    }
}

void Dungeon::SetupDungeonParametersAfterXMLRead()
{
	for(size_t i = 0; i < dungeonTileSet.size(); i++)
	{
		if(dungeonTileSet[i]->getType() == DungeonTile::TileType::DUNGEON_ENTRANCE)
		{
			exitTilePtr = dungeonTileSet[i];
		}
		
	}
}
