#include "WinnerDecisionRoom.h"

    
bool loadWinnerDecisionRoomMedia(SDL_Renderer* gRenderer,LTexture* tileMap,
LTexture* wnjudge1_texture,LTexture* wnjudge2_texture,LTexture* wnjudge3_texture,LTexture* wnjudge4_texture,
ALuint* source,ALuint* buffer)
{
    bool success = true;
    
    std::string tileFilePath = DATADIR_STR + std::string("/Graphics/tiles-winner-room.png");
    //load texture for member tileTextureMap
    if(!tileMap->loadFromFile(tileFilePath.c_str(), gRenderer))
    {
        std::cout << "Couldn't load tileTextureMap! \n";
        return false;
    }
    else
    {
        //if tileTextureMap loaded successfully
        
        //std::string path = std::string("/Sound/Threshing-Floor-VG-Ambient-Beautiful-Haunting-Remix.ogg");
        //if(!LoadBuffer(buffer,path))
        //{
		//	printf("Failed to load dungeon music! \n");
		//	return false;
		//}
        //else
        //{
            //setup source of dungeon music
            //alGenSources(1, source); //allocate source 

            //alSource3f(*source, AL_POSITION, 0.0f, 1.0f, 0.0f); //source position is above player(origin)
            //alSource3f(*source, AL_VELOCITY, 0.0f, 0.0f, 0.0f); //source is not moving
            
            //attach buffer to source
			//alSourcei(*source, AL_BUFFER, (ALint)(*buffer));
			
			//load textures for winner judges
			
			if(wnjudge1_texture)
			{
				std::string fp = DATADIR_STR + std::string("/Graphics/winner-judge-1player.png");
				wnjudge1_texture->loadFromFile(fp.c_str(), gRenderer);
			}
			
			if(wnjudge2_texture)
			{
				std::string fp = DATADIR_STR + std::string("/Graphics/winner-judge-2player.png");
				wnjudge2_texture->loadFromFile(fp.c_str(), gRenderer);
			}
			
			if(wnjudge3_texture)
			{
				std::string fp = DATADIR_STR + std::string("/Graphics/winner-judge-3player.png");
				wnjudge3_texture->loadFromFile(fp.c_str(), gRenderer);
			}
			
			if(wnjudge4_texture)
			{
				std::string fp = DATADIR_STR + std::string("/Graphics/winner-judge-4player.png");
				wnjudge4_texture->loadFromFile(fp.c_str(), gRenderer);
			}
            
        //}        
    }
    
    return success;
}

void freeWinnerDecisionRoomMedia(LTexture* tileMap,
								LTexture* wnjudge1_texture,LTexture* wnjudge2_texture,LTexture* wnjudge3_texture,LTexture* wnjudge4_texture,
								ALuint* source,ALuint* buffer)
{
    //free source
    alDeleteSources(1, source); // delete source
    
    //free buffer
	alDeleteBuffers(1, buffer); //delete buffer
    
    //free tile texture map
    tileMap->free();
    
    wnjudge1_texture->free();
    wnjudge2_texture->free();
    wnjudge3_texture->free();
    wnjudge4_texture->free();
    
}


WinnerDecisionRoom::WinnerDecisionRoom()
{
    //std::cout << "WinnerDecisionRoom constructor called! \n";
    //start off with running state
    WinnerDecisionRoom::setState(GameState::State::RUNNING);
	
	m_player_manager_ptr = nullptr;
	mainInventoryPtr = nullptr;
	
}

WinnerDecisionRoom::~WinnerDecisionRoom()
{
    //std::cout << "WinnerDecisionRoom destructor called! \n";

    //set main sprite pointer to NULL
    mainPlayer = nullptr;
    
}

void WinnerDecisionRoom::SetPointerToPlayerManager(PlayerManager* pm){m_player_manager_ptr = pm;}

void WinnerDecisionRoom::SetPointerToGameInventory(GameInventory* thisInventory){mainInventoryPtr = thisInventory;}


void WinnerDecisionRoom::GenerateBaseRoom()
{
	std::int16_t startX = 0;
    std::int16_t startY = 0;
    
    std::int16_t numTiles = 0;
    
    std::int16_t tileWidth = globalTileWidth;
    std::int16_t tileHeight = globalTileHeight;
    
	
    //calculate number of tiles in dungeon
    numTiles = (LEVEL_WIDTH / tileWidth) * (LEVEL_HEIGHT / tileHeight);
    
    //create blank tiles
    WinnerDecisionRoom::createBlankTiles(startX,startY,
                            tileWidth,tileHeight,
                            numTiles);
    
    //set tile types
    for(size_t i = 0; i < dungeonTileSet.size(); i++)
    {
		DungeonTile::TileType type = DungeonTile::TileType::RED;
		
		if(i % 2 == 0){type = DungeonTile::TileType::BLUE;}
		
		if(i % 4 == 0){type = DungeonTile::TileType::GREEN;}
		
		if(i == dungeonTileSet.size() / 2)
		{
			exitTilePtr = dungeonTileSet[i];
			type = DungeonTile::TileType::DUNGEON_ENTRANCE;
		}
		
		dungeonTileSet[i]->setType(type);
	}
	
    //set tile clips for each tile based on tile type
    WinnerDecisionRoom::setTiles();
    
}

void WinnerDecisionRoom::PlaceWinnerJudges(int num_players)
{
	
	//set winner judge position for 1 player win
	
	if(LEVEL_WIDTH > 0 && LEVEL_HEIGHT > 0)
	{
		std::int16_t x = 0;
		std::int16_t y = 0;
		
		x = LEVEL_WIDTH / 4;
		y = LEVEL_HEIGHT / 4;
		
		one_player_winner_judge.SetNumberOfPlayersToWin(1);
		one_player_winner_judge.SetPosition(x,y);
		
		//set for 2 player win
		if(num_players > 1)
		{
			x = (3*LEVEL_WIDTH) / 4;
			y = LEVEL_HEIGHT / 4;
			
			two_player_winner_judge.SetNumberOfPlayersToWin(2);
			two_player_winner_judge.SetPosition(x,y);
		}
		
		if(num_players > 2)
		{
			x = LEVEL_WIDTH / 4;
			y = (3*LEVEL_HEIGHT) / 4;
			
			three_player_winner_judge.SetNumberOfPlayersToWin(3);
			three_player_winner_judge.SetPosition(x,y);
		}
		
		if(num_players > 3)
		{
			x = (3*LEVEL_WIDTH) / 4;
			y = (3*LEVEL_HEIGHT) / 4;
		
			four_player_winner_judge.SetNumberOfPlayersToWin(4);
			four_player_winner_judge.SetPosition(x,y);
		}
	}
	
	
}

void WinnerDecisionRoom::setLevelDimensions(std::int16_t& levelWidth, std::int16_t& levelHeight)
{
	LEVEL_WIDTH = levelWidth;
	LEVEL_HEIGHT = levelHeight;
}
    
void WinnerDecisionRoom::setPointerToTimer(LTimer* thisTimer){timer = thisTimer;}

void WinnerDecisionRoom::setPointersToMedia(LTexture* tileMap,
											LTexture* winner_judge1,LTexture* winner_judge2,LTexture* winner_judge3,LTexture* winner_judge4,
											ALuint* source,ALuint* buffer)
{
    tileTextureMap = tileMap;
    roomSource = source;
    roomBuffer = buffer;
    
    one_player_winner_judge.SetPointerToTexture(winner_judge1);
    two_player_winner_judge.SetPointerToTexture(winner_judge2);
    three_player_winner_judge.SetPointerToTexture(winner_judge3);
    four_player_winner_judge.SetPointerToTexture(winner_judge4);
}

void WinnerDecisionRoom::createBlankTiles(std::int16_t &start_x, std::int16_t& start_y,
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

void WinnerDecisionRoom::setTiles()
{
    //std::cout << "set tile clips called! \n";
    //Set tile clips
    for(size_t i = 0; i < dungeonTileSet.size(); ++i)
    {
        dungeonTileSet[i]->setTileClips();
    }
}

void WinnerDecisionRoom::deleteTiles()
{
        //free the tiles allocated in bool setTiles
        for(size_t i=0; i < dungeonTileSet.size(); ++i)
        {
            //std::cout << " \n Delete tileSet element:" << i <<" Address:" << &tileSet[i];
            delete dungeonTileSet[i];
        }
}

/** Dot Functions**/

void WinnerDecisionRoom::SetPointerToMainPlayer(Player* player){mainPlayer = player;}


void WinnerDecisionRoom::moveMainDot(float& timeStep)
{
  //  std::cout << "timestep: " << timeStep <<std::endl;

    //set camera over dot
    //mainPlayer->setCamera(*lCamera);

    //move dot independent of frames, but rather dependent on time. includes collision detection
    mainPlayer->moveOnTiles(timeStep, dungeonTileSet );

    //Restart timer
    timer->start();

}


void WinnerDecisionRoom::moveMainDot(Player* thisDot,float &timeStep,SDL_Rect* thisCamera)
{
    //set camera over dot
    //Center the camera over the dot
	thisCamera->x = ( (int)thisDot->getPosX() + thisDot->getWidth() / 2  ) - thisCamera->w / 2;
	thisCamera->y = ( (int)thisDot->getPosY() + thisDot->getHeight() / 2  ) - thisCamera->h / 2;
	
	//Keep the camera in bounds
	if( thisCamera->x < 1 )
	{
		thisCamera->x = 1;
	}
	if( thisCamera->y < 1 )
	{
		thisCamera->y = 1;
	}

    //move dot independent of frames, but rather dependent on time. includes collision detection
    thisDot->moveOnTiles_TileType(timeStep, dungeonTileSet );
		
}

void WinnerDecisionRoom::PlaceDotInThisLocation(float& x, float& y)
{
	mainPlayer->setPosX(x);
    mainPlayer->setPosY(y);
}

void WinnerDecisionRoom::PlacePlayerInThisLocation(Player* thisPlayer, float& x, float& y)
{
	thisPlayer->setPosX(x);
    thisPlayer->setPosY(y);
}

void WinnerDecisionRoom::PlacePlayerInLocationNearEntrance(Player* thisPlayer)
{
	if(exitTilePtr)
	{
		float x = exitTilePtr->getBox().x + 80;
		float y = exitTilePtr->getBox().y + 80;
				
		thisPlayer->setPosX(x);
		thisPlayer->setPosY(y);
	}
    
}



/** Game Loop Functions**/

void WinnerDecisionRoom::handle_events(Event& thisEvent)
{
   // std::cout << "Handle events called! \n";

    //User requests pause by pressing escape
    if( thisEvent.event_id == Event_ID::ESCAPE )
    {
        //set pause state
        WinnerDecisionRoom::setState(GameState::State::PAUSE);
    }
    //User requests quit by X out window
    else if(thisEvent.event_id == Event_ID::QUIT_WINDOW)
    {
        WinnerDecisionRoom::setState(GameState::State::EXIT);
    }

    //mainPlayer->handleEvent(thisEvent);
    
    if(m_player_manager_ptr)
    {
		m_player_manager_ptr->handleEvent(thisEvent);
	}

}

void WinnerDecisionRoom::handle_events_RNG(RNGType& rngSeed){}

void WinnerDecisionRoom::logic()
{
    //std::cout << "Logic called! \n";
    float timeStep = timer->getTicks() / 1000.f; //frame rate
	
	WinnerDecisionRoom::logic_alt(timeStep);
    
    //Restart timer
    timer->start();
    
}

void WinnerDecisionRoom::logic_alt(float& timeStep)
{
	//logic for player
    if(m_player_manager_ptr != nullptr)
    {
        
        PlayerManager::PlayerLocation p1_loc, p2_loc, p3_loc, p4_loc;
		m_player_manager_ptr->GetLocationEnumOfPlayers(&p1_loc,&p2_loc,&p3_loc,&p4_loc);
		
		
		//do logic of other players if they are in the same dungeon
		
		if(p1_loc == PlayerManager::PlayerLocation::WINNER_ROOM  
			&& m_player_manager_ptr->GetPointerToPlayerOne() )
		{
			WinnerDecisionRoom::moveMainDot(m_player_manager_ptr->GetPointerToPlayerOne(),timeStep,
								m_player_manager_ptr->GetPointerToCameraOne());
			
			//if player 1 hits dungeon entrance/exit
			if( checkCollision(exitTilePtr->getBox(),m_player_manager_ptr->GetPointerToPlayerOne()->getCollisionBox() ) )
			{ 
				m_player_manager_ptr->SetLocationEnumOfPlayer(PlayerManager::PlayerLocation::WINNER_ROOM_2_LABYRINTH,1);
			}
		}
		if(p2_loc == PlayerManager::PlayerLocation::WINNER_ROOM
			&& m_player_manager_ptr->GetPointerToPlayerTwo() )
		{
			WinnerDecisionRoom::moveMainDot(m_player_manager_ptr->GetPointerToPlayerTwo(),timeStep,
								m_player_manager_ptr->GetPointerToCameraTwo());
			
			//if player 2 hits dungeon entrance/exit
			if( checkCollision(exitTilePtr->getBox(),m_player_manager_ptr->GetPointerToPlayerTwo()->getCollisionBox() ) )
			{ 
				m_player_manager_ptr->SetLocationEnumOfPlayer(PlayerManager::PlayerLocation::WINNER_ROOM_2_LABYRINTH,2);
			}
		}
		if(p3_loc == PlayerManager::PlayerLocation::WINNER_ROOM  
			&& m_player_manager_ptr->GetPointerToPlayerThree() )
		{
			WinnerDecisionRoom::moveMainDot(m_player_manager_ptr->GetPointerToPlayerThree(),timeStep,
								m_player_manager_ptr->GetPointerToCameraThree());
			
			//if player 3 hits dungeon entrance/exit
			if( checkCollision(exitTilePtr->getBox(),m_player_manager_ptr->GetPointerToPlayerThree()->getCollisionBox() ) )
			{ 
				m_player_manager_ptr->SetLocationEnumOfPlayer(PlayerManager::PlayerLocation::WINNER_ROOM_2_LABYRINTH,3);
			}
		}
		if(p4_loc == PlayerManager::PlayerLocation::WINNER_ROOM 
			&& m_player_manager_ptr->GetPointerToPlayerFour() )
		{
			WinnerDecisionRoom::moveMainDot(m_player_manager_ptr->GetPointerToPlayerFour(),timeStep,
								m_player_manager_ptr->GetPointerToCameraFour());
			
			//if player 4 hits dungeon entrance/exit
			if( checkCollision(exitTilePtr->getBox(),m_player_manager_ptr->GetPointerToPlayerFour()->getCollisionBox() ) )
			{ 
				m_player_manager_ptr->SetLocationEnumOfPlayer(PlayerManager::PlayerLocation::WINNER_ROOM_2_LABYRINTH,4);
			}
		}
		
		//do logic for winner judges
		WinnerDecisionRoom::logic_winner_judges();
        
    }
}


//play sounds
void WinnerDecisionRoom::sound(AudioRenderer* gAudioRenderer)
{
    
    //play dungeon music
    //play sound from dgmSource
    alGetSourcei(*roomSource, AL_SOURCE_STATE, &musicState);
    if (musicState == AL_STOPPED || musicState == AL_INITIAL){ alSourcePlay(*roomSource);}

}

void WinnerDecisionRoom::render(SDL_Renderer* gRenderer)
{
    /*
    //Render level
    for( size_t i = 0; i < dungeonTileSet.size(); ++i )
    {
        dungeonTileSet[i]->render(tileTextureMap,*lCamera,gRenderer);
    }

    //render dot
    mainPlayer->render(*lCamera,gRenderer);
	*/

}

void WinnerDecisionRoom::render(DrawingManager* gDrawManager)
{
	
	PlayerManager::PlayerLocation p1_loc, p2_loc, p3_loc, p4_loc;
	m_player_manager_ptr->GetLocationEnumOfPlayers(&p1_loc,&p2_loc,&p3_loc,&p4_loc);	
	
	bool player1_active = false;
	bool player2_active = false;
	bool player3_active = false;
	bool player4_active = false;
	

	if(m_player_manager_ptr->GetPointerToPlayerOne())
	{
		if(m_player_manager_ptr->GetPointerToPlayerOne()->getHealth() > 0
			&& p1_loc == PlayerManager::PlayerLocation::WINNER_ROOM)
		{
			player1_active = true;
		}
	}
	
	if(m_player_manager_ptr->GetPointerToPlayerTwo())
	{
		if(m_player_manager_ptr->GetPointerToPlayerTwo()->getHealth() > 0
			&& p2_loc == PlayerManager::PlayerLocation::WINNER_ROOM)
		{
			player2_active = true;
		}
	}
	
	if(m_player_manager_ptr->GetPointerToPlayerThree())
	{
		if(m_player_manager_ptr->GetPointerToPlayerThree()->getHealth() > 0
		&& p3_loc == PlayerManager::PlayerLocation::WINNER_ROOM)
		{
			player3_active = true;
		}
	}
	
	if(m_player_manager_ptr->GetPointerToPlayerFour())
	{
		if(m_player_manager_ptr->GetPointerToPlayerFour()->getHealth() > 0
		&& p4_loc == PlayerManager::PlayerLocation::WINNER_ROOM)
		{
			player4_active = true;
		}
	}
	
	//render sprites of other players if they are in the same dungeon
	
	if(player1_active)
	{
		gDrawManager->SetToRenderViewPortPlayer1();
				
		for( size_t i = 0; i < dungeonTileSet.size(); i++ )
		{
			dungeonTileSet[i]->render(tileTextureMap,*m_player_manager_ptr->GetPointerToCameraOne(),gDrawManager->GetPointerToRenderer());		
		}
		
		m_player_manager_ptr->GetPointerToPlayerOne()->render(*m_player_manager_ptr->GetPointerToCameraOne(),gDrawManager->GetPointerToRenderer());
		
		if(player2_active){m_player_manager_ptr->GetPointerToPlayerTwo()->render(*m_player_manager_ptr->GetPointerToCameraOne(),gDrawManager->GetPointerToRenderer());}
		if(player3_active){m_player_manager_ptr->GetPointerToPlayerThree()->render(*m_player_manager_ptr->GetPointerToCameraOne(),gDrawManager->GetPointerToRenderer());}
		if(player4_active){m_player_manager_ptr->GetPointerToPlayerFour()->render(*m_player_manager_ptr->GetPointerToCameraOne(),gDrawManager->GetPointerToRenderer());}
	}
	
	if(player2_active)
	{
		gDrawManager->SetToRenderViewPortPlayer2();
		
		for( size_t i = 0; i < dungeonTileSet.size(); ++i )
		{
			dungeonTileSet[i]->render(tileTextureMap,*m_player_manager_ptr->GetPointerToCameraTwo(),gDrawManager->GetPointerToRenderer());		
		}
		
		m_player_manager_ptr->GetPointerToPlayerTwo()->render(*m_player_manager_ptr->GetPointerToCameraTwo(),gDrawManager->GetPointerToRenderer());
		
		if(player1_active){m_player_manager_ptr->GetPointerToPlayerOne()->render(*m_player_manager_ptr->GetPointerToCameraTwo(),gDrawManager->GetPointerToRenderer());}
		if(player3_active){m_player_manager_ptr->GetPointerToPlayerThree()->render(*m_player_manager_ptr->GetPointerToCameraTwo(),gDrawManager->GetPointerToRenderer());}
		if(player4_active){m_player_manager_ptr->GetPointerToPlayerFour()->render(*m_player_manager_ptr->GetPointerToCameraTwo(),gDrawManager->GetPointerToRenderer());}
	}
	
	if(player3_active)
	{
		gDrawManager->SetToRenderViewPortPlayer3();
				
		for( size_t i = 0; i < dungeonTileSet.size(); ++i )
		{
			dungeonTileSet[i]->render(tileTextureMap,*m_player_manager_ptr->GetPointerToCameraThree(),gDrawManager->GetPointerToRenderer());		
		}
		
		m_player_manager_ptr->GetPointerToPlayerThree()->render(*m_player_manager_ptr->GetPointerToCameraThree(),gDrawManager->GetPointerToRenderer());
		
		if(player2_active){m_player_manager_ptr->GetPointerToPlayerTwo()->render(*m_player_manager_ptr->GetPointerToCameraThree(),gDrawManager->GetPointerToRenderer());}
		if(player1_active){m_player_manager_ptr->GetPointerToPlayerOne()->render(*m_player_manager_ptr->GetPointerToCameraThree(),gDrawManager->GetPointerToRenderer());}
		if(player4_active){m_player_manager_ptr->GetPointerToPlayerFour()->render(*m_player_manager_ptr->GetPointerToCameraThree(),gDrawManager->GetPointerToRenderer());}
	}
	
	if(player4_active)
	{
		gDrawManager->SetToRenderViewPortPlayer4();
		
		for( size_t i = 0; i < dungeonTileSet.size(); ++i )
		{
			dungeonTileSet[i]->render(tileTextureMap,*m_player_manager_ptr->GetPointerToCameraFour(),gDrawManager->GetPointerToRenderer());		
		}
		
		m_player_manager_ptr->GetPointerToPlayerFour()->render(*m_player_manager_ptr->GetPointerToCameraFour(),gDrawManager->GetPointerToRenderer());
		
		if(player2_active){m_player_manager_ptr->GetPointerToPlayerTwo()->render(*m_player_manager_ptr->GetPointerToCameraFour(),gDrawManager->GetPointerToRenderer());}
		if(player3_active){m_player_manager_ptr->GetPointerToPlayerThree()->render(*m_player_manager_ptr->GetPointerToCameraFour(),gDrawManager->GetPointerToRenderer());}
		if(player1_active){m_player_manager_ptr->GetPointerToPlayerOne()->render(*m_player_manager_ptr->GetPointerToCameraFour(),gDrawManager->GetPointerToRenderer());}
	}
    
    //render winner judges
    WinnerDecisionRoom::render_winner_judges(gDrawManager);
    
}

void WinnerDecisionRoom::render_winner_judges(DrawingManager* gDrawManager)
{

	int num_players = m_player_manager_ptr->GetNumberOfPlayers();
	
	PlayerManager::PlayerLocation p1_loc, p2_loc, p3_loc, p4_loc;
	m_player_manager_ptr->GetLocationEnumOfPlayers(&p1_loc,&p2_loc,&p3_loc,&p4_loc);	
    
    //render on player 1 viewport if player in winner room
    if(p1_loc == PlayerManager::PlayerLocation::WINNER_ROOM)
    {
		gDrawManager->SetToRenderViewPortPlayer1();
		
		
		SDL_Rect* camera_ptr = gDrawManager->GetPointerToCameraOne();
		
		if(checkCollision(*camera_ptr,*one_player_winner_judge.getCollisionBoxPtr()) )
		{
			one_player_winner_judge.render(gDrawManager->GetPointerToRenderer(),*camera_ptr);
		}
		
		if(num_players > 1 )
		{
			if(checkCollision(*camera_ptr,*two_player_winner_judge.getCollisionBoxPtr()) )
			{
				two_player_winner_judge.render(gDrawManager->GetPointerToRenderer(),*camera_ptr);
			}
		}

		if(num_players > 2 )
		{
		   if(checkCollision(*camera_ptr,*three_player_winner_judge.getCollisionBoxPtr()) )
			{
				three_player_winner_judge.render(gDrawManager->GetPointerToRenderer(),*camera_ptr);
			}
		}

		if(num_players > 3 )
		{
			if(checkCollision(*camera_ptr,*four_player_winner_judge.getCollisionBoxPtr()) )
			{
				four_player_winner_judge.render(gDrawManager->GetPointerToRenderer(),*camera_ptr);
			}
		}
	}
	
	//render on player 2 viewport if player in winner room
    if(p2_loc == PlayerManager::PlayerLocation::WINNER_ROOM)
    {
		gDrawManager->SetToRenderViewPortPlayer2();
		
		
		SDL_Rect* camera_ptr = gDrawManager->GetPointerToCameraTwo();
		
		if(checkCollision(*camera_ptr,*one_player_winner_judge.getCollisionBoxPtr()) )
		{
			one_player_winner_judge.render(gDrawManager->GetPointerToRenderer(),*camera_ptr);
		}
		
		if(num_players > 1 )
		{
			if(checkCollision(*camera_ptr,*two_player_winner_judge.getCollisionBoxPtr()) )
			{
				two_player_winner_judge.render(gDrawManager->GetPointerToRenderer(),*camera_ptr);
			}
		}

		if(num_players > 2 )
		{
		   if(checkCollision(*camera_ptr,*three_player_winner_judge.getCollisionBoxPtr()) )
			{
				three_player_winner_judge.render(gDrawManager->GetPointerToRenderer(),*camera_ptr);
			}
		}

		if(num_players > 3 )
		{
			if(checkCollision(*camera_ptr,*four_player_winner_judge.getCollisionBoxPtr()) )
			{
				four_player_winner_judge.render(gDrawManager->GetPointerToRenderer(),*camera_ptr);
			}
		}
	}
	
	//render on player 3 viewport if player in winner room
    if(p3_loc == PlayerManager::PlayerLocation::WINNER_ROOM)
    {
		gDrawManager->SetToRenderViewPortPlayer3();
		
		
		SDL_Rect* camera_ptr = gDrawManager->GetPointerToCameraThree();
		
		if(checkCollision(*camera_ptr,*one_player_winner_judge.getCollisionBoxPtr()) )
		{
			one_player_winner_judge.render(gDrawManager->GetPointerToRenderer(),*camera_ptr);
		}
		
		if(num_players > 1 )
		{
			if(checkCollision(*camera_ptr,*two_player_winner_judge.getCollisionBoxPtr()) )
			{
				two_player_winner_judge.render(gDrawManager->GetPointerToRenderer(),*camera_ptr);
			}
		}

		if(num_players > 2 )
		{
		   if(checkCollision(*camera_ptr,*three_player_winner_judge.getCollisionBoxPtr()) )
			{
				three_player_winner_judge.render(gDrawManager->GetPointerToRenderer(),*camera_ptr);
			}
		}

		if(num_players > 3 )
		{
			if(checkCollision(*camera_ptr,*four_player_winner_judge.getCollisionBoxPtr()) )
			{
				four_player_winner_judge.render(gDrawManager->GetPointerToRenderer(),*camera_ptr);
			}
		}
	}
	
	//render on player 4 viewport if player in winner room
    if(p4_loc == PlayerManager::PlayerLocation::WINNER_ROOM)
    {
		gDrawManager->SetToRenderViewPortPlayer4();
		
		SDL_Rect* camera_ptr = gDrawManager->GetPointerToCameraFour();
		
		if(checkCollision(*camera_ptr,*one_player_winner_judge.getCollisionBoxPtr()) )
		{
			one_player_winner_judge.render(gDrawManager->GetPointerToRenderer(),*camera_ptr);
		}
		
		if(num_players > 1 )
		{
			if(checkCollision(*camera_ptr,*two_player_winner_judge.getCollisionBoxPtr()) )
			{
				two_player_winner_judge.render(gDrawManager->GetPointerToRenderer(),*camera_ptr);
			}
		}

		if(num_players > 2 )
		{
		   if(checkCollision(*camera_ptr,*three_player_winner_judge.getCollisionBoxPtr()) )
			{
				three_player_winner_judge.render(gDrawManager->GetPointerToRenderer(),*camera_ptr);
			}
		}

		if(num_players > 3 )
		{
			if(checkCollision(*camera_ptr,*four_player_winner_judge.getCollisionBoxPtr()) )
			{
				four_player_winner_judge.render(gDrawManager->GetPointerToRenderer(),*camera_ptr);
			}
		}
	}
	
}

void WinnerDecisionRoom::logic_winner_judges()
{
	int num_players = m_player_manager_ptr->GetNumberOfPlayers();
	
	PlayerManager::PlayerLocation p1_loc, p2_loc, p3_loc, p4_loc;
	m_player_manager_ptr->GetLocationEnumOfPlayers(&p1_loc,&p2_loc,&p3_loc,&p4_loc);
	
	//collision check for one player winner judge
	one_player_winner_judge.CheckPlayerandJudgeCollisions(m_player_manager_ptr,PlayerManager::PlayerLocation::WINNER_ROOM);
	
	//collision check for two player winner judge
	if(num_players > 1)
	{
		two_player_winner_judge.CheckPlayerandJudgeCollisions(m_player_manager_ptr,PlayerManager::PlayerLocation::WINNER_ROOM);
	}
	
	//collision check for three player winner judge
	if(num_players > 2)
	{
		three_player_winner_judge.CheckPlayerandJudgeCollisions(m_player_manager_ptr,PlayerManager::PlayerLocation::WINNER_ROOM);
	}
	
	//collision check for four player winner judge
	if(num_players > 3)
	{
		four_player_winner_judge.CheckPlayerandJudgeCollisions(m_player_manager_ptr,PlayerManager::PlayerLocation::WINNER_ROOM);
	}
}

WinnerJudge::WinningPlayers WinnerDecisionRoom::GetOneWinnersResult()
{
	return one_player_winner_judge.GetPlayersWon();
}

WinnerJudge::WinningPlayers WinnerDecisionRoom::GetTwoWinnersResult()
{
	return two_player_winner_judge.GetPlayersWon();
}

WinnerJudge::WinningPlayers WinnerDecisionRoom::GetThreeWinnersResult()
{
	return three_player_winner_judge.GetPlayersWon();
}

WinnerJudge::WinningPlayers WinnerDecisionRoom::GetFourWinnersResult()
{
	return four_player_winner_judge.GetPlayersWon();
}

//Set States
void WinnerDecisionRoom::setState(GameState::State thisState){GameState::setState(thisState);}
GameState::State WinnerDecisionRoom::getState(){return GameState::getState();}

int WinnerDecisionRoom::getDotTileNumber()
{
    for(size_t i=0; i < dungeonTileSet.size(); ++i )
    {
        if(checkCollision(mainPlayer->getCollisionBox(), dungeonTileSet[i]->getBox() ) == true)
        {
            return dungeonTileSet[i]->getTileNumber();
        }
    }

}

int WinnerDecisionRoom::getTileNumberFromPosition(int x, int y)
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


SDL_Rect WinnerDecisionRoom::getTileBox_under_dot()
{
    for(size_t i=0; i < dungeonTileSet.size(); ++i )
    {
        if( checkCollision(mainPlayer->getCollisionBox(), dungeonTileSet[i]->getBox() ) == true)
        {
            return dungeonTileSet[i]->getBox();
        }
    }

}

DungeonTile* WinnerDecisionRoom::getDungeonTileFromPosition(int x, int y) 
{
    size_t xCol = ( x - NODE_X ) / TILE_WIDTH;
    size_t yRow = ( y - NODE_Y ) / TILE_HEIGHT;
    
    if(xCol >= numXNodeColumns || yRow >= numYNodeRows){return nullptr;}
    else{ return dungeon_tile_look_up [xCol] [yRow];}
}

void WinnerDecisionRoom::getXColYRowFromPosition(int x, int y,size_t& xCol, size_t& yRow)
{
     xCol= ( x - NODE_X ) / TILE_WIDTH;
     yRow = ( y - NODE_Y   ) / TILE_HEIGHT;
}


void WinnerDecisionRoom::freeResources()
{
	//Set the pointers' adressses to nullptr
    for(size_t i = 0; i < dungeonTileSet.size(); ++i)
    {
		delete dungeonTileSet[i];
        dungeonTileSet[i] = nullptr;
    }
}
