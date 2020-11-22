#include "labyrinth_dungeon_manager.h"

#include "dungeon_media_loader.h"

LabyrinthDungeonManager::LabyrinthDungeonManager()
{
	
	labyrinthCreated = false;
	m_player_manager_ptr = nullptr;
	
	
}

LabyrinthDungeonManager::~LabyrinthDungeonManager()
{
	m_player_manager_ptr = nullptr;
	
}

void LabyrinthDungeonManager::SetPointerToPlayerManager(PlayerManager* pm){m_player_manager_ptr = pm;}

void LabyrinthDungeonManager::SetPointerToTimer(LTimer* timer){stepTimer = timer;}

void LabyrinthDungeonManager::SetPointerToGameInventory(GameInventory* thisInventory){m_game_inventory_ptr = thisInventory;}

void LabyrinthDungeonManager::setupScreenDimensions(std::int16_t width, std::int16_t height){SCREEN_WIDTH = width; SCREEN_HEIGHT = height;}

void LabyrinthDungeonManager::SetPointerToDungeonXMLRegistry(DungeonXMLRegistry* reg){m_dungeon_xml_reg_ptr = reg;}

bool LabyrinthDungeonManager::setupLabyrinth(PlayerManager* mainPlayerManager, GameInventory* gameInventory,
											DungeonXMLRegistry* dungeon_xml_reg, RNGType& rngSeed,
											LTimer* stepTimer, Dot* mainDotPointer,
											std::int16_t SCREEN_WIDTH , std::int16_t SCREEN_HEIGHT,
											LTexture& keyTexture, ALuint& keySource,ALuint& keyBuffer,
											LTexture& doorTexture, ALuint& doorSource, ALuint& doorBufferOpen, ALuint& doorBufferFail,
											std::vector <SDL_Rect> &doorClips)
{
	std::unique_ptr <Labyrinth> labyrinthUPtr(new Labyrinth() );
	
	Labyrinth& thisLabyrinth = *labyrinthUPtr.get();
	
    thisLabyrinth.setTimerPointer(stepTimer);
    thisLabyrinth.setPointerToMainDot(mainDotPointer);
    m_player_manager_ptr = mainPlayerManager;
    thisLabyrinth.setPointerToPlayerManager(mainPlayerManager);
    thisLabyrinth.setPointersToMedia(&dungeonTilesTexture,&dungeonMusicSource,&dungeonMusicBuffer);
	thisLabyrinth.SetPointerToGameInventory(gameInventory);
	
    //set dimenstions of grid labyrinth will use for generating map
    std::int16_t x = 0;
    std::int16_t y = 0;
    std::int16_t w = 400;
    std::int16_t h = 400;
    thisLabyrinth.setGridDimensions(x,y,w,h);
    thisLabyrinth.randomlySetNumberOfNodesToGenerate(rngSeed);
   
    
    //if able to generate labyrinth
    if( thisLabyrinth.generateLabyrinth(rngSeed) )
    {
		std::unique_ptr <CollisonHandler> ptrToCollisionHandler(new CollisonHandler());
		if(!ptrToCollisionHandler){std::cout << "Failed to initialize main labyrinth collision handler!\n"; return false;}
		else
		{
			mainLabCollisionHandler = std::move(ptrToCollisionHandler);
			
			//add player to collision system
			mainLabCollisionHandler->SetCamerasForCollisionSystem(m_player_manager_ptr->GetPointerToCameraOne(),nullptr,nullptr,nullptr);
			mainLabCollisionHandler->addPlayersToCollisionSystem(m_player_manager_ptr->GetPointerToPlayerOne()->getCollisionObjectPtr(),
																 nullptr,nullptr,nullptr);
																 
			mainLabCollisionHandler->addPlayerEquippedWeaponsToCollisionSystem(m_player_manager_ptr->GetPointerToPlayerOne()->getPointerToEquippedPlayerWeapon(),
																			nullptr,nullptr,nullptr);
			
			//if there is a 2nd player
			if(m_player_manager_ptr->GetNumberOfPlayers() > 1)
			{
				//add player to collision system
				mainLabCollisionHandler->SetCamerasForCollisionSystem(m_player_manager_ptr->GetPointerToCameraOne(),
																	  m_player_manager_ptr->GetPointerToCameraTwo(),
																	  nullptr,nullptr);
																	  
				mainLabCollisionHandler->addPlayersToCollisionSystem(m_player_manager_ptr->GetPointerToPlayerOne()->getCollisionObjectPtr(),
																	 m_player_manager_ptr->GetPointerToPlayerTwo()->getCollisionObjectPtr(),
																	 nullptr,nullptr);
																	 
				mainLabCollisionHandler->addPlayerEquippedWeaponsToCollisionSystem(m_player_manager_ptr->GetPointerToPlayerOne()->getPointerToEquippedPlayerWeapon(),
																				m_player_manager_ptr->GetPointerToPlayerTwo()->getPointerToEquippedPlayerWeapon(),
																				nullptr,nullptr);
			}
			
			//if there is a 3rd player
			if(m_player_manager_ptr->GetNumberOfPlayers() > 2)
			{
				//add player to collision system
				mainLabCollisionHandler->SetCamerasForCollisionSystem(m_player_manager_ptr->GetPointerToCameraOne(),
																	  m_player_manager_ptr->GetPointerToCameraTwo(),
																	  m_player_manager_ptr->GetPointerToCameraThree(),
																	  nullptr);
																	  
				mainLabCollisionHandler->addPlayersToCollisionSystem(m_player_manager_ptr->GetPointerToPlayerOne()->getCollisionObjectPtr(),
																	 m_player_manager_ptr->GetPointerToPlayerTwo()->getCollisionObjectPtr(),
																	 m_player_manager_ptr->GetPointerToPlayerThree()->getCollisionObjectPtr(),
																	 nullptr);
																	 
				mainLabCollisionHandler->addPlayerEquippedWeaponsToCollisionSystem(m_player_manager_ptr->GetPointerToPlayerOne()->getPointerToEquippedPlayerWeapon(),
																				m_player_manager_ptr->GetPointerToPlayerTwo()->getPointerToEquippedPlayerWeapon(),
																				m_player_manager_ptr->GetPointerToPlayerThree()->getPointerToEquippedPlayerWeapon(),
																				nullptr);
			}
			
			//if there is a 4th player
			if(m_player_manager_ptr->GetNumberOfPlayers() > 3)
			{
				//add player to collision system
				mainLabCollisionHandler->SetCamerasForCollisionSystem(m_player_manager_ptr->GetPointerToCameraOne(),
																	  m_player_manager_ptr->GetPointerToCameraTwo(),
																	  m_player_manager_ptr->GetPointerToCameraThree(),
																	  m_player_manager_ptr->GetPointerToCameraFour());
																	  
				mainLabCollisionHandler->addPlayersToCollisionSystem(m_player_manager_ptr->GetPointerToPlayerOne()->getCollisionObjectPtr(),
																	 m_player_manager_ptr->GetPointerToPlayerTwo()->getCollisionObjectPtr(),
																	 m_player_manager_ptr->GetPointerToPlayerThree()->getCollisionObjectPtr(),
																	 m_player_manager_ptr->GetPointerToPlayerFour()->getCollisionObjectPtr());
																	 
				mainLabCollisionHandler->addPlayerEquippedWeaponsToCollisionSystem(m_player_manager_ptr->GetPointerToPlayerOne()->getPointerToEquippedPlayerWeapon(),
																				m_player_manager_ptr->GetPointerToPlayerTwo()->getPointerToEquippedPlayerWeapon(),
																				m_player_manager_ptr->GetPointerToPlayerThree()->getPointerToEquippedPlayerWeapon(),
																				m_player_manager_ptr->GetPointerToPlayerFour()->getPointerToEquippedPlayerWeapon());
			}
			
			
		}
       
        //Setup world of labyrinth
        thisLabyrinth.generateDungeonsInLabyrinth(rngSeed,
                                          keyTexture, keySource,keyBuffer,
                                          doorTexture,doorSource,doorBufferOpen,doorBufferFail, &doorClips);

        thisLabyrinth.setupDotInLabyrinth(SCREEN_WIDTH, SCREEN_HEIGHT);
        
        thisLabyrinth.randomlySetExitForMaze(rngSeed);
        thisLabyrinth.randomlySetLabyrinthDoors(rngSeed);
        
        thisLabyrinth.randomlySetDungeonEntrancesinMaze(rngSeed,dungeon_xml_reg);
        
        thisLabyrinth.setTiles();
        
        m_labyrinth = std::move(labyrinthUPtr);
		labyrinthCreated = true;
		
		if(m_labyrinth)
		{
			for(size_t i = 0; i < m_labyrinth->GetEnemiesInLabyrinthVector()->size(); i++)
			{
				if(mainLabCollisionHandler->repeatPlay)
				{
					std::cout << " repeat!\n";
				}
				Enemy* thisEnemy = m_labyrinth->GetEnemiesInLabyrinthVector()->at(i);
				mainLabCollisionHandler->addObjectToCollisionSystem(thisEnemy->getCollisionObjectPtr());
				mainLabCollisionHandler->addObjectToCollisionSystem(thisEnemy->GetLineOfSightCollisionObject());
			}
			
		}
        
        return true;
    }
    
    std::cout << "Failed to generate labyrinth! \n";
    return false;
}

void LabyrinthDungeonManager::LabyrinthToMiniDungeonTransitionOperations()
{
	bool p1_entered = m_labyrinth->getPlayerHitDungeonEntraceBool(1);
	bool p2_entered = m_labyrinth->getPlayerHitDungeonEntraceBool(2);
	bool p3_entered = m_labyrinth->getPlayerHitDungeonEntraceBool(3);
	bool p4_entered = m_labyrinth->getPlayerHitDungeonEntraceBool(4);
	
	
	//if player 1 entered mini dungeon
	if(p1_entered)
	{
		//get index of mini dungeon entered
		std::int16_t num_mini_dungeon_entered = m_player_manager_ptr->GetDungeonIndexForThisPlayerInDungeon(1);
		
		//get position in labyrinth near mini dungeon entrance
		player1PosX_beforedungeon = m_player_manager_ptr->GetPointerToPlayerOne()->getPosX() + 80;
		player1PosY_beforedungeon = m_player_manager_ptr->GetPointerToPlayerOne()->getPosY() + 80;
		
		//load mini dungeon
		LabyrinthDungeonManager::SetupMiniDungeon(1,num_mini_dungeon_entered);
		
		//reset player hit entrance bool
		m_labyrinth->setPlayerHitDungeonEntranceBool(false,1);
	}
	
	int num_players = m_player_manager_ptr->GetNumberOfPlayers();
	
	if(p2_entered && num_players > 1)
	{
		//get index of mini dungeon entered
		std::int16_t num_mini_dungeon_entered = m_player_manager_ptr->GetDungeonIndexForThisPlayerInDungeon(2);
		
		//get position in labyrinth near mini dungeon entrance
		player2PosX_beforedungeon = m_player_manager_ptr->GetPointerToPlayerTwo()->getPosX() + 80;
		player2PosY_beforedungeon = m_player_manager_ptr->GetPointerToPlayerTwo()->getPosY() + 80;
		
		//load mini dungeon
		LabyrinthDungeonManager::SetupMiniDungeon(2,num_mini_dungeon_entered);
		
		//reset player hit entrance bool
		m_labyrinth->setPlayerHitDungeonEntranceBool(false,2);
	}
	
	if(p3_entered && num_players > 2)
	{
		//get index of mini dungeon entered
		std::int16_t num_mini_dungeon_entered = m_player_manager_ptr->GetDungeonIndexForThisPlayerInDungeon(3);
		
		//get position in labyrinth near mini dungeon entrance
		player3PosX_beforedungeon = m_player_manager_ptr->GetPointerToPlayerThree()->getPosX() + 80;
		player3PosY_beforedungeon = m_player_manager_ptr->GetPointerToPlayerThree()->getPosY() + 80;
		
		//load mini dungeon
		LabyrinthDungeonManager::SetupMiniDungeon(3,num_mini_dungeon_entered);
		
		//reset player hit entrance bool
		m_labyrinth->setPlayerHitDungeonEntranceBool(false,3);
	}
	
	if(p4_entered && num_players > 3)
	{
		//get index of mini dungeon entered
		std::int16_t num_mini_dungeon_entered = m_player_manager_ptr->GetDungeonIndexForThisPlayerInDungeon(4);
		
		//get position in labyrinth near mini dungeon entrance
		player4PosX_beforedungeon = m_player_manager_ptr->GetPointerToPlayerFour()->getPosX() + 80;
		player4PosY_beforedungeon = m_player_manager_ptr->GetPointerToPlayerFour()->getPosY() + 80;
		
		//load mini dungeon
		//player automatically placed near entrance
		LabyrinthDungeonManager::SetupMiniDungeon(4,num_mini_dungeon_entered);
		
		//reset player hit entrance bool
		m_labyrinth->setPlayerHitDungeonEntranceBool(false,4);
	}
}

void LabyrinthDungeonManager::SetupMiniDungeon(int num_player, std::int16_t& num_mini_dungeon_entered)
{	
	//initialize dungeon
	
	std::unique_ptr <Dungeon> dungeonUPtr(new Dungeon() );
	
	Dungeon* dungeonPtr = nullptr;
	
	switch(num_player)
	{
		case 1:{ m_mini_dungeon_p1 = std::move(dungeonUPtr); dungeonPtr = m_mini_dungeon_p1.get(); break;}
		case 2:{ m_mini_dungeon_p2 = std::move(dungeonUPtr); dungeonPtr = m_mini_dungeon_p2.get(); break;}
		case 3:{ m_mini_dungeon_p3 = std::move(dungeonUPtr); dungeonPtr = m_mini_dungeon_p3.get(); break;}
		case 4:{ m_mini_dungeon_p4 = std::move(dungeonUPtr); dungeonPtr = m_mini_dungeon_p4.get(); break;}
	}
	
	if(dungeonPtr)
	{
		switch(num_player)
		{
			case 1:{dungeonPtr->SetPointerToMainPlayer(m_player_manager_ptr->GetPointerToPlayerOne()); break;}
			case 2:{dungeonPtr->SetPointerToMainPlayer(m_player_manager_ptr->GetPointerToPlayerTwo()); break;}
			case 3:{dungeonPtr->SetPointerToMainPlayer(m_player_manager_ptr->GetPointerToPlayerThree()); break;}
			case 4:{dungeonPtr->SetPointerToMainPlayer(m_player_manager_ptr->GetPointerToPlayerFour()); break;}
		}
		
		dungeonPtr->setPointerToTimer(stepTimer);
		
		dungeonPtr->SetPointerToPlayerManager(m_player_manager_ptr);
		dungeonPtr->setPointersToMedia(&dungeonTilesTexture,&dungeonMusicSource,&dungeonMusicBuffer);
		dungeonPtr->SetPointerToGameInventory(m_game_inventory_ptr);
		
		dungeonPtr->SetMainPlayerNumber(num_player);
		
		SDL_Rect* camera = nullptr;
		switch(num_player)
		{
			case 1:{ camera = m_player_manager_ptr->GetPointerToCameraOne(); break;}
			case 2:{ camera = m_player_manager_ptr->GetPointerToCameraTwo(); break;}
			case 3:{ camera = m_player_manager_ptr->GetPointerToCameraThree(); break;}
			case 4:{ camera = m_player_manager_ptr->GetPointerToCameraFour(); break;}
		}
		
		dungeonPtr->setDungeonCameraForDot(SCREEN_WIDTH,SCREEN_HEIGHT,camera);
		
		std::int16_t LEVEL_WIDTH = SCREEN_WIDTH * 10;
		std::int16_t LEVEL_HEIGHT = SCREEN_HEIGHT * 10;

		dungeonPtr->setLevelDimensions(LEVEL_WIDTH,LEVEL_HEIGHT);
		
		//generate an empty dungeon
		dungeonPtr->GenerateEmptyDungeonForXMLLoad();
		
		std::unique_ptr <DungeonXMLReader> dungeonXMLReaderUPtr(new DungeonXMLReader() );
		
		//get dungeon file 
		std::string dungeon_file = m_dungeon_xml_reg_ptr->GetXMLDungeonFilePathFromIndex(num_mini_dungeon_entered);
		
		//if dungeon file exists, set the tiles    
		std::ifstream ifile(dungeon_file);
		if((bool)ifile)
		{
			std::cout << "Reading " << dungeon_file << std::endl;
			
			dungeonPtr->SetDungeonIndex(num_mini_dungeon_entered);
			dungeonXMLReaderUPtr->SetDungeonTilesFromXML(dungeon_file,dungeonPtr);
			dungeonPtr->SetupDungeonParametersAfterXMLRead();
			dungeonPtr->PlacePlayerInLocationNearEntrance();
		}
		else
		{		
			std::cout << "Error: " + dungeon_file + " does not exist!\n";
		}
		
		
		std::unique_ptr <CollisonHandler> ptrToCollisionHandler(new CollisonHandler());
		if(!ptrToCollisionHandler){std::cout << "Failed to initialize collision handler for mini dungeon!\n";}
		else
		{
			//Setup camera for collision system
			
			
			switch(num_player)
			{
				case 1:
				{
					ptrToCollisionHandler->setCameraForCollisionSystem(m_player_manager_ptr->GetPointerToCameraOne());
					miniCollisionHandler_d1 = std::move(ptrToCollisionHandler);
					break;
				}
				case 2:
				{
					ptrToCollisionHandler->setCameraForCollisionSystem(m_player_manager_ptr->GetPointerToCameraTwo()); 
					miniCollisionHandler_d2 = std::move(ptrToCollisionHandler);
					break;
				}
				case 3:
				{
					ptrToCollisionHandler->setCameraForCollisionSystem(m_player_manager_ptr->GetPointerToCameraThree()); 
					miniCollisionHandler_d3 = std::move(ptrToCollisionHandler); 
					break;
				}
				case 4:
				{
					ptrToCollisionHandler->setCameraForCollisionSystem(m_player_manager_ptr->GetPointerToCameraFour()); 
					miniCollisionHandler_d4 = std::move(ptrToCollisionHandler); 
					break;
				}
			}
			
			
		}
	}
	else
	{
		std::cout << "Failed to initialize mini dungeon!\n";
	}
	
}

void LabyrinthDungeonManager::CloseMiniDungeon(int num_player)
{
	switch(num_player)
	{
		case 1:{ m_mini_dungeon_p1->freeResources(); break;}
		case 2:{ m_mini_dungeon_p2->freeResources(); break;}
		case 3:{ m_mini_dungeon_p3->freeResources(); break;}
		case 4:{ m_mini_dungeon_p4->freeResources();; break;}
	}
	
}

void LabyrinthDungeonManager::MiniDungeonToLabyrinthTransitionOperations()
{
	if(m_mini_dungeon_p1)
	{
		if(m_mini_dungeon_p1->getState() == GameState::State::NEXT)
		{
			m_player_manager_ptr->GetPointerToPlayerOne()->setPosX(player1PosX_beforedungeon);
			m_player_manager_ptr->GetPointerToPlayerOne()->setPosY(player1PosY_beforedungeon);
			
			//reset to running
			m_mini_dungeon_p1->setState(GameState::State::RUNNING);
		}
	}
	
	if(m_mini_dungeon_p2)
	{
		if(m_mini_dungeon_p2->getState() == GameState::State::NEXT)
		{
			m_player_manager_ptr->GetPointerToPlayerTwo()->setPosX(player2PosX_beforedungeon);
			m_player_manager_ptr->GetPointerToPlayerTwo()->setPosY(player2PosY_beforedungeon);
			
			//reset to running
			m_mini_dungeon_p2->setState(GameState::State::RUNNING);
		}
	}
	
	if(m_mini_dungeon_p3)
	{
		if(m_mini_dungeon_p3->getState() == GameState::State::NEXT)
		{
			m_player_manager_ptr->GetPointerToPlayerThree()->setPosX(player3PosX_beforedungeon);
			m_player_manager_ptr->GetPointerToPlayerThree()->setPosY(player3PosY_beforedungeon);
			
			//reset to running
			m_mini_dungeon_p3->setState(GameState::State::RUNNING);
		}
	}
	
	if(m_mini_dungeon_p4)
	{
		if(m_mini_dungeon_p4->getState() == GameState::State::NEXT)
		{
			m_player_manager_ptr->GetPointerToPlayerFour()->setPosX(player4PosX_beforedungeon);
			m_player_manager_ptr->GetPointerToPlayerFour()->setPosY(player4PosY_beforedungeon);
			
			//reset to running
			m_mini_dungeon_p4->setState(GameState::State::RUNNING);
		}
	}
	
}

//Game loop

void LabyrinthDungeonManager::setState(GameState::State thisState){GameState::setState(thisState);}
GameState::State LabyrinthDungeonManager::getState(){return GameState::getState();}


void LabyrinthDungeonManager::handle_events(Event& thisEvent)
{
	if( thisEvent.event_id == Event_ID::QUIT_WINDOW || thisEvent.event_id == Event_ID::ESCAPE )
	{
		LabyrinthDungeonManager::setState(GameState::State::PAUSE);
	}
	
	if(m_player_manager_ptr)
	{
		int num_players = m_player_manager_ptr->GetNumberOfPlayers();
		
		bool p1_in_dungeon,p2_in_dungeon,p3_in_dungeon,p4_in_dungeon;
		std::int16_t p1_index_dungeon,p2_index_dungeon,p3_index_dungeon,p4_index_dungeon;
		
		m_player_manager_ptr->GetBoolsForPlayersInDungeon(&p1_in_dungeon,&p2_in_dungeon,&p3_in_dungeon,&p4_in_dungeon);
		m_player_manager_ptr->GetDungeonIndexesForPlayersInDungeon(&p1_index_dungeon,&p2_index_dungeon,&p3_index_dungeon,&p4_index_dungeon);
		
		bool one_player_in_lab = true;
		
		if(num_players > 1)
		{
			if(p1_in_dungeon && p2_in_dungeon){one_player_in_lab = false;}
		}
		
		if(num_players > 2)
		{
			if(p1_in_dungeon && p2_in_dungeon && p3_in_dungeon){one_player_in_lab = false;}
		}
		
		if(num_players > 3)
		{
			if(p1_in_dungeon && p2_in_dungeon && p3_in_dungeon && p4_in_dungeon){one_player_in_lab = false;}
		}
		
		//handle events for labyrinth if any of the players are in labyrinth
		if(one_player_in_lab)
		{
			m_labyrinth->handle_events(thisEvent);
		}
		
		
		//handle events for mini dungeon for player 1 if player 1 is in mini dungeon
		if(m_mini_dungeon_p1 && p1_in_dungeon)
		{
			m_mini_dungeon_p1->handle_events(thisEvent);
		}
		//handle events for mini dungeon for player 2 if player 2 is in mini dungeon
		if(m_mini_dungeon_p2 && p2_in_dungeon)
		{
			m_mini_dungeon_p2->handle_events(thisEvent);
		}
		//handle events for mini dungeon for player 3 if player 3 is in mini dungeon
		if(m_mini_dungeon_p3 && p3_in_dungeon)
		{
			m_mini_dungeon_p3->handle_events(thisEvent);
		}
		//handle events for mini dungeon for player 4 if player 4 is in mini dungeon
		if(m_mini_dungeon_p4 && p4_in_dungeon)
		{
			m_mini_dungeon_p4->handle_events(thisEvent);
		}
	}
	
}

void LabyrinthDungeonManager::handle_events_RNG(RNGType& rngSeed)
{
	if(m_player_manager_ptr)
	{
		
		int num_players = m_player_manager_ptr->GetNumberOfPlayers();
		
		bool p1_in_dungeon,p2_in_dungeon,p3_in_dungeon,p4_in_dungeon;
		std::int16_t p1_index_dungeon,p2_index_dungeon,p3_index_dungeon,p4_index_dungeon;
		
		m_player_manager_ptr->GetBoolsForPlayersInDungeon(&p1_in_dungeon,&p2_in_dungeon,&p3_in_dungeon,&p4_in_dungeon);
		m_player_manager_ptr->GetDungeonIndexesForPlayersInDungeon(&p1_index_dungeon,&p2_index_dungeon,&p3_index_dungeon,&p4_index_dungeon);
		
		bool one_player_in_lab = true;
		
		if(num_players > 1)
		{
			if(p1_in_dungeon && p2_in_dungeon){one_player_in_lab = false;}
		}
		
		if(num_players > 2)
		{
			if(p1_in_dungeon && p2_in_dungeon && p3_in_dungeon){one_player_in_lab = false;}
		}
		
		if(num_players > 3)
		{
			if(p1_in_dungeon && p2_in_dungeon && p3_in_dungeon && p4_in_dungeon){one_player_in_lab = false;}
		}
		
		//handle events for labyrinth if any of the players are in labyrinth
		if(one_player_in_lab)
		{
			m_labyrinth->handle_events_RNG(rngSeed);
		}
		
		//handle events for mini dungeon for player 1 if player 1 is in mini dungeon
		if(m_mini_dungeon_p1 && p1_in_dungeon)
		{
			m_mini_dungeon_p1->handle_events_RNG(rngSeed);
		}
		//handle events for mini dungeon for player 2 if player 2 is in mini dungeon
		if(m_mini_dungeon_p2 && p2_in_dungeon)
		{
			m_mini_dungeon_p2->handle_events_RNG(rngSeed);
		}
		//handle events for mini dungeon for player 3 if player 3 is in mini dungeon
		if(m_mini_dungeon_p3 && p3_in_dungeon)
		{
			m_mini_dungeon_p3->handle_events_RNG(rngSeed);
		}
		//handle events for mini dungeon for player 4 if player 4 is in mini dungeon
		if(m_mini_dungeon_p4 && p4_in_dungeon)
		{
			m_mini_dungeon_p4->handle_events_RNG(rngSeed);
		}
		
	}
	
}

void LabyrinthDungeonManager::logic()
{
	
	if(m_player_manager_ptr)
	{
		//do logic for labyrinth if any of the players are in labyrinth
		int num_players = m_player_manager_ptr->GetNumberOfPlayers();
		
		bool p1_in_dungeon,p2_in_dungeon,p3_in_dungeon,p4_in_dungeon;
		std::int16_t p1_index_dungeon,p2_index_dungeon,p3_index_dungeon,p4_index_dungeon;
		
		m_player_manager_ptr->GetBoolsForPlayersInDungeon(&p1_in_dungeon,&p2_in_dungeon,&p3_in_dungeon,&p4_in_dungeon);
		m_player_manager_ptr->GetDungeonIndexesForPlayersInDungeon(&p1_index_dungeon,&p2_index_dungeon,&p3_index_dungeon,&p4_index_dungeon);
		
		bool one_player_in_lab = true;
		
		if(num_players > 1)
		{
			if(p1_in_dungeon && p2_in_dungeon){one_player_in_lab = false;}
		}
		
		if(num_players > 2)
		{
			if(p1_in_dungeon && p2_in_dungeon && p3_in_dungeon){one_player_in_lab = false;}
		}
		
		if(num_players > 3)
		{
			if(p1_in_dungeon && p2_in_dungeon && p3_in_dungeon && p4_in_dungeon){one_player_in_lab = false;}
		}
		
		//render for labyrinth if any of the players are in labyrinth
		if(one_player_in_lab)
		{
			m_labyrinth->logic();
		}
		
		//do logic for mini dungeon for player 1 if player 1 is in mini dungeon
		if(m_mini_dungeon_p1 && p1_in_dungeon)
		{
			m_mini_dungeon_p1->logic();
		}
		//do logic for mini dungeon for player 2 if player 2 is in mini dungeon
		if(m_mini_dungeon_p2 && p2_in_dungeon)
		{
			m_mini_dungeon_p2->logic();
		}
		//do logic for mini dungeon for player 3 if player 3 is in mini dungeon
		if(m_mini_dungeon_p3 && p3_in_dungeon)
		{
			m_mini_dungeon_p3->logic();
		}
		//do logic for mini dungeon for player 4 if player 4 is in mini dungeon
		if(m_mini_dungeon_p4 && p4_in_dungeon)
		{
			m_mini_dungeon_p4->logic();
		}
		
	}
	
}

void LabyrinthDungeonManager::sound(AudioRenderer* gAudioRenderer)
{
	if(m_player_manager_ptr)
	{
		int num_players = m_player_manager_ptr->GetNumberOfPlayers();
		
		bool p1_in_dungeon,p2_in_dungeon,p3_in_dungeon,p4_in_dungeon;
		std::int16_t p1_index_dungeon,p2_index_dungeon,p3_index_dungeon,p4_index_dungeon;
		
		m_player_manager_ptr->GetBoolsForPlayersInDungeon(&p1_in_dungeon,&p2_in_dungeon,&p3_in_dungeon,&p4_in_dungeon);
		m_player_manager_ptr->GetDungeonIndexesForPlayersInDungeon(&p1_index_dungeon,&p2_index_dungeon,&p3_index_dungeon,&p4_index_dungeon);
		
		bool one_player_in_lab = true;
		
		if(num_players > 1)
		{
			if(p1_in_dungeon && p2_in_dungeon){one_player_in_lab = false;}
		}
		
		if(num_players > 2)
		{
			if(p1_in_dungeon && p2_in_dungeon && p3_in_dungeon){one_player_in_lab = false;}
		}
		
		if(num_players > 3)
		{
			if(p1_in_dungeon && p2_in_dungeon && p3_in_dungeon && p4_in_dungeon){one_player_in_lab = false;}
		}
		
		//render for labyrinth if any of the players are in labyrinth
		if(one_player_in_lab)
		{
			m_labyrinth->sound(gAudioRenderer);
		}
		
		//play sound in mini dungeon for player 1 if player 1 is in mini dungeon
		//play sound in mini dungeon for player 2 if player 2 is in mini dungeon
		//play sound in mini dungeon for player 3 if player 3 is in mini dungeon
		//play sound in mini dungeon for player 4 if player 4 is in mini dungeon
		
	}
}

void LabyrinthDungeonManager::render(SDL_Renderer* gRenderer)
{
	
}

void LabyrinthDungeonManager::render(DrawingManager* gDrawManager)
{
	if(m_player_manager_ptr)
	{
		int num_players = m_player_manager_ptr->GetNumberOfPlayers();
		
		bool p1_in_dungeon,p2_in_dungeon,p3_in_dungeon,p4_in_dungeon;
		std::int16_t p1_index_dungeon,p2_index_dungeon,p3_index_dungeon,p4_index_dungeon;
		
		m_player_manager_ptr->GetBoolsForPlayersInDungeon(&p1_in_dungeon,&p2_in_dungeon,&p3_in_dungeon,&p4_in_dungeon);
		m_player_manager_ptr->GetDungeonIndexesForPlayersInDungeon(&p1_index_dungeon,&p2_index_dungeon,&p3_index_dungeon,&p4_index_dungeon);
		
		bool one_player_in_lab = true;
		
		if(num_players > 1)
		{
			if(p1_in_dungeon && p2_in_dungeon){one_player_in_lab = false;}
		}
		
		if(num_players > 2)
		{
			if(p1_in_dungeon && p2_in_dungeon && p3_in_dungeon){one_player_in_lab = false;}
		}
		
		if(num_players > 3)
		{
			if(p1_in_dungeon && p2_in_dungeon && p3_in_dungeon && p4_in_dungeon){one_player_in_lab = false;}
		}
		
		//render for labyrinth if any of the players are in labyrinth
		if(one_player_in_lab)
		{
			m_labyrinth->render(gDrawManager);
		}
		
		//render mini dungeon for player 1 if player 1 is in mini dungeon
		if(m_mini_dungeon_p1 && p1_in_dungeon)
		{
			gDrawManager->SetToRenderViewPortPlayer1();
			m_mini_dungeon_p1->render(gDrawManager);
		}
		//render mini dungeon for player 2 if player 2 is in mini dungeon
		if(m_mini_dungeon_p2 && p2_in_dungeon)
		{
			gDrawManager->SetToRenderViewPortPlayer2();
			m_mini_dungeon_p2->render(gDrawManager);
		}
		//render mini dungeon for player 3 if player 3 is in mini dungeon
		if(m_mini_dungeon_p3 && p3_in_dungeon)
		{
			gDrawManager->SetToRenderViewPortPlayer3();
			m_mini_dungeon_p3->render(gDrawManager);
		}
		//render mini dungeon for player 4 if player 4 is in mini dungeon
		if(m_mini_dungeon_p4 && p4_in_dungeon)
		{
			gDrawManager->SetToRenderViewPortPlayer4();
			m_mini_dungeon_p4->render(gDrawManager);
		}
	}
	
}

Labyrinth* LabyrinthDungeonManager::GetPointerToLabyrinth(){return m_labyrinth.get();}

bool LabyrinthDungeonManager::GetLabyrinthCreatedBool(){return labyrinthCreated;}

void LabyrinthDungeonManager::RunCollisionHandlersOps()
{
	int num_players = m_player_manager_ptr->GetNumberOfPlayers();
	
	if(mainLabCollisionHandler)
	{
		mainLabCollisionHandler->run_collision_handler(num_players);
	}
	
	
}
