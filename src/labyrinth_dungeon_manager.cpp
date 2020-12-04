#include "labyrinth_dungeon_manager.h"

#include "dungeon_media_loader.h"

#include "winner_media_loader.h"

LabyrinthDungeonManager::LabyrinthDungeonManager()
{
	
	labyrinthCreated = false;
	m_player_manager_ptr = nullptr;
	
	player1_win = false;
	player2_win = false;
	player3_win = false;
	player4_win = false;
	
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

        thisLabyrinth.setupDotInLabyrinth(SCREEN_WIDTH, SCREEN_HEIGHT,rngSeed);
        
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
	
	PlayerManager::PlayerLocation p1_loc, p2_loc, p3_loc, p4_loc;
	m_player_manager_ptr->GetLocationEnumOfPlayers(&p1_loc,&p2_loc,&p3_loc,&p4_loc);
	
	
	int num_player_entered = 0;
	std::int16_t num_mini_dungeon_entered = 0;
	int mini_dungeon_to_enter = 0; //used to indicate if should enter mini dungeon mini_dungeon_1 member, 2, 3 or 4
	
	//if player 1 entered mini dungeon
	if(p1_loc == PlayerManager::PlayerLocation::LABYRINTH_2_DUNGEON)
	{
		
		//get position in labyrinth near mini dungeon entrance
		player1PosX_beforedungeon = m_player_manager_ptr->GetPointerToPlayerOne()->getPosX() + 80;
		player1PosY_beforedungeon = m_player_manager_ptr->GetPointerToPlayerOne()->getPosY() + 80;
		
		//get index of mini dungeon entered
		num_mini_dungeon_entered = m_player_manager_ptr->GetDungeonIndexForThisPlayerInDungeon(1);
		
		num_player_entered = 1;
				
	}
	
	int num_players = m_player_manager_ptr->GetNumberOfPlayers();
	
	if(p2_loc == PlayerManager::PlayerLocation::LABYRINTH_2_DUNGEON && num_players > 1)
	{
		
		//get position in labyrinth near mini dungeon entrance
		player2PosX_beforedungeon = m_player_manager_ptr->GetPointerToPlayerTwo()->getPosX() + 80;
		player2PosY_beforedungeon = m_player_manager_ptr->GetPointerToPlayerTwo()->getPosY() + 80;
		
		//get index of mini dungeon entered
		num_mini_dungeon_entered = m_player_manager_ptr->GetDungeonIndexForThisPlayerInDungeon(2);
		
		num_player_entered = 2;
		
	}
	
	if(p3_loc == PlayerManager::PlayerLocation::LABYRINTH_2_DUNGEON && num_players > 2)
	{
		//get index of mini dungeon entered
		num_mini_dungeon_entered = m_player_manager_ptr->GetDungeonIndexForThisPlayerInDungeon(3);
		
		//get position in labyrinth near mini dungeon entrance
		player3PosX_beforedungeon = m_player_manager_ptr->GetPointerToPlayerThree()->getPosX() + 80;
		player3PosY_beforedungeon = m_player_manager_ptr->GetPointerToPlayerThree()->getPosY() + 80;
		
		num_player_entered = 3;
	}
	
	if(p4_loc == PlayerManager::PlayerLocation::LABYRINTH_2_DUNGEON && num_players > 3)
	{
		//get index of mini dungeon entered
		num_mini_dungeon_entered = m_player_manager_ptr->GetDungeonIndexForThisPlayerInDungeon(4);
		
		//get position in labyrinth near mini dungeon entrance
		player4PosX_beforedungeon = m_player_manager_ptr->GetPointerToPlayerFour()->getPosX() + 80;
		player4PosY_beforedungeon = m_player_manager_ptr->GetPointerToPlayerFour()->getPosY() + 80;
		
		num_player_entered = 4;
	}
	
	bool loadNewDungeon = true;
	
	if(m_mini_dungeon_1)
	{
		if(m_mini_dungeon_1->GetDungeonIndex() == num_mini_dungeon_entered)
		{
			loadNewDungeon = false;
			mini_dungeon_to_enter = 1;
		}
	}
	
	if(m_mini_dungeon_2)
	{
		if(m_mini_dungeon_2->GetDungeonIndex() == num_mini_dungeon_entered)
		{
			loadNewDungeon = false;
			mini_dungeon_to_enter = 2;
		}
	}
	
	if(m_mini_dungeon_3)
	{
		if(m_mini_dungeon_3->GetDungeonIndex() == num_mini_dungeon_entered)
		{
			loadNewDungeon = false;
			mini_dungeon_to_enter = 3;
		}
	}
	
	if(m_mini_dungeon_4)
	{
		if(m_mini_dungeon_4->GetDungeonIndex() == num_mini_dungeon_entered)
		{
			loadNewDungeon = false;
			mini_dungeon_to_enter = 4;
		}
	}
	
	//if need to load new dungeon for player entered to mini dungeon entered
	if(loadNewDungeon && num_player_entered != 0 && num_mini_dungeon_entered != 0)
	{
		std::cout << "loading dungeon index " << num_mini_dungeon_entered << std::endl;
		//load mini dungeon
		LabyrinthDungeonManager::SetupMiniDungeon(num_player_entered,num_mini_dungeon_entered);
		
		//reset player hit entrance bool
		m_labyrinth->setPlayerHitDungeonEntranceBool(false,num_player_entered);
	}
	//else if need to put a player in already initialized and running dungeon
	else if(!loadNewDungeon && num_player_entered != 0 && num_mini_dungeon_entered != 0
			&& mini_dungeon_to_enter != 0)
	{
		std::cout << "Placing player in dungeon index " << num_mini_dungeon_entered << std::endl;
		
		Player* thisPlayer = nullptr;
		switch(num_player_entered)
		{
			case 1:{thisPlayer = m_player_manager_ptr->GetPointerToPlayerOne(); break;}
			case 2:{thisPlayer = m_player_manager_ptr->GetPointerToPlayerTwo(); break;}
			case 3:{thisPlayer = m_player_manager_ptr->GetPointerToPlayerThree(); break;}
			case 4:{thisPlayer = m_player_manager_ptr->GetPointerToPlayerFour(); break;}
		}
		
		Dungeon* thisDungeon = nullptr;
		
		//put player in this dungeon
		switch(mini_dungeon_to_enter)
		{
			case 1:{ thisDungeon = m_mini_dungeon_1.get(); break;}
			case 2:{ thisDungeon = m_mini_dungeon_2.get(); break;}
			case 3:{ thisDungeon = m_mini_dungeon_3.get(); break;}
			case 4:{ thisDungeon = m_mini_dungeon_4.get(); break;}
		}
		
		if(thisPlayer && thisDungeon)
		{
			m_player_manager_ptr->SetLocationEnumOfPlayer(PlayerManager::PlayerLocation::DUNGEON,num_player_entered);
			thisDungeon->PlacePlayerInLocationNearEntrance(thisPlayer);
		}
		
		//reset player hit entrance bool
		m_labyrinth->setPlayerHitDungeonEntranceBool(false,num_player_entered);
	}
}

void LabyrinthDungeonManager::SetupMiniDungeon(int num_player, std::int16_t& num_mini_dungeon_entered)
{	
	//initialize dungeon
	
	std::unique_ptr <Dungeon> dungeonUPtr(new Dungeon() );
	
	Dungeon* dungeonPtr = nullptr;
	
	switch(num_player)
	{
		case 1:{ m_mini_dungeon_1 = std::move(dungeonUPtr); dungeonPtr = m_mini_dungeon_1.get(); break;}
		case 2:{ m_mini_dungeon_2 = std::move(dungeonUPtr); dungeonPtr = m_mini_dungeon_2.get(); break;}
		case 3:{ m_mini_dungeon_3 = std::move(dungeonUPtr); dungeonPtr = m_mini_dungeon_3.get(); break;}
		case 4:{ m_mini_dungeon_4 = std::move(dungeonUPtr); dungeonPtr = m_mini_dungeon_4.get(); break;}
	}
	
	if(dungeonPtr)
	{
		
		dungeonPtr->setPointerToTimer(stepTimer);
		
		dungeonPtr->SetPointerToPlayerManager(m_player_manager_ptr);
		dungeonPtr->setPointersToMedia(&dungeonTilesTexture,&dungeonMusicSource,&dungeonMusicBuffer);
		dungeonPtr->SetPointerToGameInventory(m_game_inventory_ptr);
				
		
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
			
			Player* thisPlayer = nullptr;
			switch(num_player)
			{
				case 1:{thisPlayer = m_player_manager_ptr->GetPointerToPlayerOne(); break;}
				case 2:{thisPlayer = m_player_manager_ptr->GetPointerToPlayerTwo(); break;}
				case 3:{thisPlayer = m_player_manager_ptr->GetPointerToPlayerThree(); break;}
				case 4:{thisPlayer = m_player_manager_ptr->GetPointerToPlayerFour(); break;}
			}
			
			if(thisPlayer)
			{
				m_player_manager_ptr->SetLocationEnumOfPlayer(PlayerManager::PlayerLocation::DUNGEON,num_player);
				dungeonPtr->PlacePlayerInLocationNearEntrance(thisPlayer);
			}
			
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
	
}

void LabyrinthDungeonManager::MiniDungeonToLabyrinthTransitionOperations()
{
	int num_players = m_player_manager_ptr->GetNumberOfPlayers();
	
	PlayerManager::PlayerLocation p1_loc, p2_loc, p3_loc, p4_loc;
	m_player_manager_ptr->GetLocationEnumOfPlayers(&p1_loc,&p2_loc,&p3_loc,&p4_loc);
	
	if(p1_loc == PlayerManager::PlayerLocation::DUNGEON_2_LABYRINTH)
	{
		m_player_manager_ptr->GetPointerToPlayerOne()->setPosX(player1PosX_beforedungeon);
		m_player_manager_ptr->GetPointerToPlayerOne()->setPosY(player1PosY_beforedungeon);
		
		m_player_manager_ptr->SetLocationEnumOfPlayer(PlayerManager::PlayerLocation::LABYRINTH,1);
	}
	
	if(p2_loc == PlayerManager::PlayerLocation::DUNGEON_2_LABYRINTH && num_players > 1)
	{
		m_player_manager_ptr->GetPointerToPlayerTwo()->setPosX(player2PosX_beforedungeon);
		m_player_manager_ptr->GetPointerToPlayerTwo()->setPosY(player2PosY_beforedungeon);
		
		m_player_manager_ptr->SetLocationEnumOfPlayer(PlayerManager::PlayerLocation::LABYRINTH,2);
	}
	
	if(p3_loc == PlayerManager::PlayerLocation::DUNGEON_2_LABYRINTH && num_players > 2)
	{
		m_player_manager_ptr->GetPointerToPlayerThree()->setPosX(player3PosX_beforedungeon);
		m_player_manager_ptr->GetPointerToPlayerThree()->setPosY(player3PosY_beforedungeon);
		
		m_player_manager_ptr->SetLocationEnumOfPlayer(PlayerManager::PlayerLocation::LABYRINTH,3);
	}
	
	if(p4_loc == PlayerManager::PlayerLocation::DUNGEON_2_LABYRINTH && num_players > 3)
	{
		m_player_manager_ptr->GetPointerToPlayerFour()->setPosX(player4PosX_beforedungeon);
		m_player_manager_ptr->GetPointerToPlayerFour()->setPosY(player4PosY_beforedungeon);
		
		m_player_manager_ptr->SetLocationEnumOfPlayer(PlayerManager::PlayerLocation::LABYRINTH,4);
	}
	
}

bool LabyrinthDungeonManager::setupWinnerRoom(PlayerManager* pm,GameInventory* gameInventory)
{
	std::unique_ptr <WinnerDecisionRoom> roomUPtr(new WinnerDecisionRoom() );
	
	WinnerDecisionRoom* winRoomPtr = nullptr;
	
	m_winner_room = std::move(roomUPtr); 
	winRoomPtr = m_winner_room.get();
		
	if(winRoomPtr)
	{
		winRoomPtr->SetPointerToPlayerManager(pm);
		winRoomPtr->SetPointerToGameInventory(gameInventory);
		
		winRoomPtr->setPointersToMedia(&winner_room_TilesTexture,
									&winner_judge1_texture,&winner_judge2_texture,&winner_judge3_texture,&winner_judge4_texture,
									&winner_room_MusicSource, &winner_room_MusicBuffer);
		
		std::int16_t LEVEL_WIDTH = SCREEN_WIDTH * 2;
		std::int16_t LEVEL_HEIGHT = SCREEN_HEIGHT * 2;

		winRoomPtr->setLevelDimensions(LEVEL_WIDTH,LEVEL_HEIGHT);
		
		winRoomPtr->GenerateBaseRoom();
		
		winRoomPtr->PlaceWinnerJudges(pm->GetNumberOfPlayers());
		
		std::unique_ptr <CollisonHandler> ptrToCollisionHandler(new CollisonHandler());
		if(!ptrToCollisionHandler)
		{
			std::cout << "Failed to initialize collision handler for winner room!\n";
			return false;
		}
		
		miniCollisionHandler_winner_room = std::move(ptrToCollisionHandler); 
	}
	else
	{
		return false;
	}
	
	return true;
}

void LabyrinthDungeonManager::LabyrinthToWinnerDecisionRoomTransitionOperations()
{
	PlayerManager::PlayerLocation p1_loc, p2_loc, p3_loc, p4_loc;
	m_player_manager_ptr->GetLocationEnumOfPlayers(&p1_loc,&p2_loc,&p3_loc,&p4_loc);
	
	int player_num_entered = 0;
	
	if(p1_loc == PlayerManager::PlayerLocation::LABYRINTH_2_WINNER_ROOM)
	{
		m_labyrinth->setPlayerHitLabyrinthExitBool(false,1);
		
		player_num_entered = 1;
	}
	
	if(p2_loc == PlayerManager::PlayerLocation::LABYRINTH_2_WINNER_ROOM)
	{
		m_labyrinth->setPlayerHitLabyrinthExitBool(false,2);
		
		player_num_entered = 2;
	}
	
	if(p3_loc == PlayerManager::PlayerLocation::LABYRINTH_2_WINNER_ROOM)
	{
		m_labyrinth->setPlayerHitLabyrinthExitBool(false,3);
		
		player_num_entered = 3;
	}
	
	if(p4_loc == PlayerManager::PlayerLocation::LABYRINTH_2_WINNER_ROOM)
	{
		m_labyrinth->setPlayerHitLabyrinthExitBool(false,4);
		
		player_num_entered = 4;
	}
	
	
		
	Player* thisPlayer = nullptr;
	switch(player_num_entered)
	{
		case 1:{thisPlayer = m_player_manager_ptr->GetPointerToPlayerOne(); break;}
		case 2:{thisPlayer = m_player_manager_ptr->GetPointerToPlayerTwo(); break;}
		case 3:{thisPlayer = m_player_manager_ptr->GetPointerToPlayerThree(); break;}
		case 4:{thisPlayer = m_player_manager_ptr->GetPointerToPlayerFour(); break;}
	}
	
	if(thisPlayer)
	{
		std::cout << "Placing player in winner room \n";
		m_player_manager_ptr->SetLocationEnumOfPlayer(PlayerManager::PlayerLocation::WINNER_ROOM,player_num_entered);
		
		switch(player_num_entered)
		{
			case 1:
			{
				player1PosX_beforedungeon = m_player_manager_ptr->GetPointerToPlayerOne()->getPosX() + 80;
				player1PosY_beforedungeon = m_player_manager_ptr->GetPointerToPlayerOne()->getPosY() + 80;
				
				break;
			}
			
			case 2:
			{
				player2PosX_beforedungeon = m_player_manager_ptr->GetPointerToPlayerTwo()->getPosX() + 80;
				player2PosY_beforedungeon = m_player_manager_ptr->GetPointerToPlayerTwo()->getPosY() + 80;
				break;
			}
			
			case 3:
			{
				player3PosX_beforedungeon = m_player_manager_ptr->GetPointerToPlayerThree()->getPosX() + 80;
				player3PosY_beforedungeon = m_player_manager_ptr->GetPointerToPlayerThree()->getPosY() + 80;
				break;
			}
			
			case 4:
			{
				player4PosX_beforedungeon = m_player_manager_ptr->GetPointerToPlayerFour()->getPosX() + 80;
				player4PosY_beforedungeon = m_player_manager_ptr->GetPointerToPlayerFour()->getPosY() + 80;
				break;
			}
		}
		
		m_winner_room->PlacePlayerInLocationNearEntrance(thisPlayer);
	}
}

void LabyrinthDungeonManager::WinnerDecisionRoomToLabyrinthTransitionOperations()
{
	PlayerManager::PlayerLocation p1_loc, p2_loc, p3_loc, p4_loc;
	m_player_manager_ptr->GetLocationEnumOfPlayers(&p1_loc,&p2_loc,&p3_loc,&p4_loc);
	
	int player_num_entered = 0;
	Player* thisPlayer = nullptr;
	float posX,posY;
	
	if(p1_loc == PlayerManager::PlayerLocation::WINNER_ROOM_2_LABYRINTH)
	{
		player_num_entered = 1;
		
		posX = player1PosX_beforedungeon;
		posY = player1PosY_beforedungeon;
		
		thisPlayer = m_player_manager_ptr->GetPointerToPlayerOne();		
	}
	
	if(p2_loc == PlayerManager::PlayerLocation::WINNER_ROOM_2_LABYRINTH)
	{
		player_num_entered = 2;
		
		posX = player1PosX_beforedungeon;
		posY = player1PosY_beforedungeon;
				
		thisPlayer = m_player_manager_ptr->GetPointerToPlayerTwo();
	}
	
	if(p3_loc == PlayerManager::PlayerLocation::WINNER_ROOM_2_LABYRINTH)
	{
		player_num_entered = 3;
		
		posX = player1PosX_beforedungeon;
		posY = player1PosY_beforedungeon;
				
		thisPlayer = m_player_manager_ptr->GetPointerToPlayerThree();
	}
	
	if(p4_loc == PlayerManager::PlayerLocation::WINNER_ROOM_2_LABYRINTH)
	{
		player_num_entered = 4;
		
		posX = player1PosX_beforedungeon;
		posY = player1PosY_beforedungeon;
				
		thisPlayer = m_player_manager_ptr->GetPointerToPlayerFour();
	}
	
	if(thisPlayer)
	{
		std::cout << "Placing player in labyrinth from winner room. \n";
		m_player_manager_ptr->SetLocationEnumOfPlayer(PlayerManager::PlayerLocation::LABYRINTH,player_num_entered);
		
		thisPlayer->setPosX(posX);
		thisPlayer->setPosY(posY);
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
		
		PlayerManager::PlayerLocation p1_loc, p2_loc, p3_loc, p4_loc;
		m_player_manager_ptr->GetLocationEnumOfPlayers(&p1_loc,&p2_loc,&p3_loc,&p4_loc);

		std::int16_t p1_index_dungeon,p2_index_dungeon,p3_index_dungeon,p4_index_dungeon;		
		m_player_manager_ptr->GetDungeonIndexesForPlayersInDungeon(&p1_index_dungeon,&p2_index_dungeon,&p3_index_dungeon,&p4_index_dungeon);
		
		bool one_player_in_lab = true;
		
		if(num_players > 1)
		{
			if(p1_loc != PlayerManager::PlayerLocation::LABYRINTH && p2_loc == p1_loc){one_player_in_lab = false;}
		}
		
		if(num_players > 2)
		{
			if(p1_loc != PlayerManager::PlayerLocation::LABYRINTH && p2_loc == p1_loc && p3_loc == p1_loc)
			{
				one_player_in_lab = false;
			}
		}
		
		if(num_players > 3)
		{
			if(p1_loc != PlayerManager::PlayerLocation::LABYRINTH && p2_loc == p1_loc 
				&& p3_loc == p1_loc && p4_loc == p1_loc)
			{
				one_player_in_lab = false;
			}
		}
		
		//handle events for labyrinth if any of the players are in labyrinth
		if(one_player_in_lab)
		{
			m_labyrinth->handle_events(thisEvent);
		}
		
		
		//handle events for each mini dungeon
		if(m_mini_dungeon_1)
		{
			std::int16_t d_index = m_mini_dungeon_1->GetDungeonIndex();
			
			if(p1_index_dungeon == d_index || 
				p2_index_dungeon == d_index ||
				p3_index_dungeon == d_index ||
				p4_index_dungeon == d_index)
			{
				m_mini_dungeon_1->handle_events(thisEvent);
			}
		}
		
		if(m_mini_dungeon_2)
		{
			std::int16_t d_index = m_mini_dungeon_2->GetDungeonIndex();
			
			if(p1_index_dungeon == d_index || 
				p2_index_dungeon == d_index ||
				p3_index_dungeon == d_index ||
				p4_index_dungeon == d_index)
			{
				m_mini_dungeon_2->handle_events(thisEvent);
			}
		}
		
		if(m_mini_dungeon_3)
		{
			std::int16_t d_index = m_mini_dungeon_3->GetDungeonIndex();
			
			if(p1_index_dungeon == d_index || 
				p2_index_dungeon == d_index ||
				p3_index_dungeon == d_index ||
				p4_index_dungeon == d_index)
			{
				m_mini_dungeon_3->handle_events(thisEvent);
			}
		}
		
		if(m_mini_dungeon_4)
		{
			std::int16_t d_index = m_mini_dungeon_4->GetDungeonIndex();
			
			if(p1_index_dungeon == d_index || 
				p2_index_dungeon == d_index ||
				p3_index_dungeon == d_index ||
				p4_index_dungeon == d_index)
			{
				m_mini_dungeon_4->handle_events(thisEvent);
			}
		}
		
		if(m_winner_room)
		{
			m_winner_room->handle_events(thisEvent);
		}
		
		if(m_player_manager_ptr)
		{
			m_player_manager_ptr->handleEvent(thisEvent);
		}
	}
	
}

void LabyrinthDungeonManager::handle_events_RNG(RNGType& rngSeed)
{
	if(m_player_manager_ptr)
	{
		
		int num_players = m_player_manager_ptr->GetNumberOfPlayers();
		
		PlayerManager::PlayerLocation p1_loc, p2_loc, p3_loc, p4_loc;
		m_player_manager_ptr->GetLocationEnumOfPlayers(&p1_loc,&p2_loc,&p3_loc,&p4_loc);
		
		std::int16_t p1_index_dungeon,p2_index_dungeon,p3_index_dungeon,p4_index_dungeon;		
		m_player_manager_ptr->GetDungeonIndexesForPlayersInDungeon(&p1_index_dungeon,&p2_index_dungeon,&p3_index_dungeon,&p4_index_dungeon);
		
		bool one_player_in_lab = true;
		
		if(num_players > 1)
		{
			if(p1_loc != PlayerManager::PlayerLocation::LABYRINTH && p2_loc == p1_loc){one_player_in_lab = false;}
		}
		
		if(num_players > 2)
		{
			if(p1_loc != PlayerManager::PlayerLocation::LABYRINTH && p2_loc == p1_loc && p3_loc == p1_loc)
			{
				one_player_in_lab = false;
			}
		}
		
		if(num_players > 3)
		{
			if(p1_loc != PlayerManager::PlayerLocation::LABYRINTH && p2_loc == p1_loc 
				&& p3_loc == p1_loc && p4_loc == p1_loc)
			{
				one_player_in_lab = false;
			}
		}
		
		//handle events for labyrinth if any of the players are in labyrinth
		if(one_player_in_lab)
		{
			m_labyrinth->handle_events_RNG(rngSeed);
		}
		
		//handle events random for each mini dungeon
		if(m_mini_dungeon_1)
		{
			std::int16_t d_index = m_mini_dungeon_1->GetDungeonIndex();
			
			if(p1_index_dungeon == d_index || 
				p2_index_dungeon == d_index ||
				p3_index_dungeon == d_index ||
				p4_index_dungeon == d_index)
			{
				m_mini_dungeon_1->handle_events_RNG(rngSeed);
			}
		}
		
		if(m_mini_dungeon_2)
		{
			std::int16_t d_index = m_mini_dungeon_2->GetDungeonIndex();
			
			if(p1_index_dungeon == d_index || 
				p2_index_dungeon == d_index ||
				p3_index_dungeon == d_index ||
				p4_index_dungeon == d_index)
			{
				m_mini_dungeon_2->handle_events_RNG(rngSeed);
			}
		}
		
		if(m_mini_dungeon_3)
		{
			std::int16_t d_index = m_mini_dungeon_3->GetDungeonIndex();
			
			if(p1_index_dungeon == d_index || 
				p2_index_dungeon == d_index ||
				p3_index_dungeon == d_index ||
				p4_index_dungeon == d_index)
			{
				m_mini_dungeon_3->handle_events_RNG(rngSeed);
			}
		}
		
		if(m_mini_dungeon_4)
		{
			std::int16_t d_index = m_mini_dungeon_4->GetDungeonIndex();
			
			if(p1_index_dungeon == d_index || 
				p2_index_dungeon == d_index ||
				p3_index_dungeon == d_index ||
				p4_index_dungeon == d_index)
			{
				m_mini_dungeon_4->handle_events_RNG(rngSeed);
			}
		}
		
		if(m_winner_room)
		{
			m_winner_room->handle_events_RNG(rngSeed);
		}
		
	}
	
}

void LabyrinthDungeonManager::logic()
{
	//create timestep for moving objects
    float timeStep = stepTimer->getTicks() / 1000.f; //frame rate
    
	if(m_player_manager_ptr)
	{
		//do logic for players
		m_player_manager_ptr->logic(timeStep);
		
		//do logic for labyrinth if any of the players are in labyrinth
		int num_players = m_player_manager_ptr->GetNumberOfPlayers();
		
		PlayerManager::PlayerLocation p1_loc, p2_loc, p3_loc, p4_loc;
		m_player_manager_ptr->GetLocationEnumOfPlayers(&p1_loc,&p2_loc,&p3_loc,&p4_loc);
		
		std::int16_t p1_index_dungeon,p2_index_dungeon,p3_index_dungeon,p4_index_dungeon;
		m_player_manager_ptr->GetDungeonIndexesForPlayersInDungeon(&p1_index_dungeon,&p2_index_dungeon,&p3_index_dungeon,&p4_index_dungeon);
		
		bool one_player_in_lab = true;
		
		if(num_players > 1)
		{
			if(p1_loc != PlayerManager::PlayerLocation::LABYRINTH && p2_loc == p1_loc){one_player_in_lab = false;}
		}
		
		if(num_players > 2)
		{
			if(p1_loc != PlayerManager::PlayerLocation::LABYRINTH && p2_loc == p1_loc && p3_loc == p1_loc)
			{
				one_player_in_lab = false;
			}
		}
		
		if(num_players > 3)
		{
			if(p1_loc != PlayerManager::PlayerLocation::LABYRINTH && p2_loc == p1_loc 
				&& p3_loc == p1_loc && p4_loc == p1_loc)
			{
				one_player_in_lab = false;
			}
		}
		
		//render for labyrinth if any of the players are in labyrinth
		if(one_player_in_lab)
		{
			m_labyrinth->logic_alt(timeStep);
		}
		
		//do logic for each player
		
		if(m_mini_dungeon_1)
		{
			std::int16_t d_index = m_mini_dungeon_1->GetDungeonIndex();
			
			if(p1_index_dungeon == d_index || 
				p2_index_dungeon == d_index ||
				p3_index_dungeon == d_index ||
				p4_index_dungeon == d_index)
			{
				m_mini_dungeon_1->logic_alt(timeStep);
			}
		}
		
		if(m_mini_dungeon_2)
		{
			std::int16_t d_index = m_mini_dungeon_2->GetDungeonIndex();
			
			if(p1_index_dungeon == d_index || 
				p2_index_dungeon == d_index ||
				p3_index_dungeon == d_index ||
				p4_index_dungeon == d_index)
			{
				m_mini_dungeon_2->logic_alt(timeStep);
			}
		}
		
		if(m_mini_dungeon_3)
		{
			std::int16_t d_index = m_mini_dungeon_3->GetDungeonIndex();
			
			if(p1_index_dungeon == d_index || 
				p2_index_dungeon == d_index ||
				p3_index_dungeon == d_index ||
				p4_index_dungeon == d_index)
			{
				m_mini_dungeon_3->logic_alt(timeStep);
			}
		}
		
		if(m_mini_dungeon_4)
		{
			std::int16_t d_index = m_mini_dungeon_4->GetDungeonIndex();
			
			if(p1_index_dungeon == d_index || 
				p2_index_dungeon == d_index ||
				p3_index_dungeon == d_index ||
				p4_index_dungeon == d_index)
			{
				m_mini_dungeon_4->logic_alt(timeStep);
			}
		}
		
		if(m_winner_room)
		{
			m_winner_room->logic_alt(timeStep);
			
			//check for winners in winner room
			LabyrinthDungeonManager::CheckForWinners();
			
		}
				
	}
	
	//Restart timer
    stepTimer->start();
	
}

void LabyrinthDungeonManager::CheckForWinners()
{
	if(m_winner_room)
	{
		int num_players = m_player_manager_ptr->GetNumberOfPlayers();
		
		//check for winning player(s)
		if(num_players > 0)
		{
			switch(m_winner_room->GetOneWinnersResult())
			{
				case WinnerJudge::WinningPlayers::PLAYERS_1:{player1_win = true; break;}
				case WinnerJudge::WinningPlayers::PLAYERS_2:{player2_win = true; break;}
				case WinnerJudge::WinningPlayers::PLAYERS_3:{player3_win = true; break;}
				case WinnerJudge::WinningPlayers::PLAYERS_4:{player4_win = true; break;}
				default:{break;}
			}
		}
		
		if(num_players > 1)
		{
			switch(m_winner_room->GetTwoWinnersResult())
			{
				case WinnerJudge::WinningPlayers::PLAYERS_1_2:
				{
					player1_win = true; player2_win = true;
					break;
				}
				case WinnerJudge::WinningPlayers::PLAYERS_1_3:
				{
					player1_win = true; player3_win = true;
					break;
				}
				case WinnerJudge::WinningPlayers::PLAYERS_1_4:
				{
					player1_win = true; player4_win = true;
					break;
				}
				case WinnerJudge::WinningPlayers::PLAYERS_2_3:
				{
					player2_win = true; player3_win = true;
					break;
				}
				case WinnerJudge::WinningPlayers::PLAYERS_2_4:
				{
					player2_win = true; player4_win = true;
					break;
				}
				case WinnerJudge::WinningPlayers::PLAYERS_3_4:
				{
					player3_win = true; player4_win = true;
					break;
				}
				default:{break;}
			}
		}
		
		if(num_players > 2)
		{
			switch(m_winner_room->GetThreeWinnersResult())
			{
				case WinnerJudge::WinningPlayers::PLAYERS_1_2_3:
				{
					player1_win = true; player2_win = true; player3_win = true;
					break;
				}
				case WinnerJudge::WinningPlayers::PLAYERS_1_2_4:
				{
					player1_win = true; player2_win = true; player4_win = true;
					break;
				}
				case WinnerJudge::WinningPlayers::PLAYERS_1_3_4:
				{
					player1_win = true; player3_win = true; player4_win = true;
					break;
				}
				case WinnerJudge::WinningPlayers::PLAYERS_2_3_4:
				{
					player2_win = true; player3_win = true; player4_win = true;
					break;
				}
				default:{break;}
			}
		}
		
		if(num_players > 3)
		{
			switch(m_winner_room->GetFourWinnersResult())
			{
				case WinnerJudge::WinningPlayers::PLAYERS_1_2_3_4:
				{
					player1_win = true; player2_win = true; player3_win = true; player4_win = true;
					break;
				}
				default:{break;}
			}
		}
		
		if(player1_win || player2_win || player3_win || player4_win)
		{
			m_labyrinth->StopPlayingTheme();
			
			LabyrinthDungeonManager::setState(GameState::State::NEXT);
			
			//done to stop playing labyrinth theme
			m_labyrinth->setState(GameState::State::NEXT);
		}
	}
}

void LabyrinthDungeonManager::GetWinnersBool(bool* p1, bool* p2, bool* p3, bool* p4)
{
	*p1 = player1_win;
	*p2 = player2_win;
	*p3 = player3_win;
	*p4 = player4_win;
}

void LabyrinthDungeonManager::sound(AudioRenderer* gAudioRenderer)
{
	if(m_player_manager_ptr)
	{
		int num_players = m_player_manager_ptr->GetNumberOfPlayers();
		
		PlayerManager::PlayerLocation p1_loc, p2_loc, p3_loc, p4_loc;
		m_player_manager_ptr->GetLocationEnumOfPlayers(&p1_loc,&p2_loc,&p3_loc,&p4_loc);
		
		std::int16_t p1_index_dungeon,p2_index_dungeon,p3_index_dungeon,p4_index_dungeon;
		m_player_manager_ptr->GetDungeonIndexesForPlayersInDungeon(&p1_index_dungeon,&p2_index_dungeon,&p3_index_dungeon,&p4_index_dungeon);
		
		bool one_player_in_lab = true;
		
		if(num_players > 1)
		{
			if(p1_loc != PlayerManager::PlayerLocation::LABYRINTH && p2_loc == p1_loc){one_player_in_lab = false;}
		}
		
		if(num_players > 2)
		{
			if(p1_loc != PlayerManager::PlayerLocation::LABYRINTH && p2_loc == p1_loc && p3_loc == p1_loc)
			{
				one_player_in_lab = false;
			}
		}
		
		if(num_players > 3)
		{
			if(p1_loc != PlayerManager::PlayerLocation::LABYRINTH && p2_loc == p1_loc 
				&& p3_loc == p1_loc && p4_loc == p1_loc)
			{
				one_player_in_lab = false;
			}
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
		
		PlayerManager::PlayerLocation p1_loc, p2_loc, p3_loc, p4_loc;
		m_player_manager_ptr->GetLocationEnumOfPlayers(&p1_loc,&p2_loc,&p3_loc,&p4_loc);
		
		std::int16_t p1_index_dungeon,p2_index_dungeon,p3_index_dungeon,p4_index_dungeon;
		m_player_manager_ptr->GetDungeonIndexesForPlayersInDungeon(&p1_index_dungeon,&p2_index_dungeon,&p3_index_dungeon,&p4_index_dungeon);
		
		bool one_player_in_lab = true;
		
		if(num_players > 1)
		{
			if(p1_loc != PlayerManager::PlayerLocation::LABYRINTH && p2_loc == p1_loc)
			{
				one_player_in_lab = false;
			}
		}
		
		if(num_players > 2)
		{
			if(p1_loc != PlayerManager::PlayerLocation::LABYRINTH && p2_loc == p1_loc && p3_loc == p1_loc)
			{
				one_player_in_lab = false;
			}
		}
		
		if(num_players > 3)
		{
			if(p1_loc != PlayerManager::PlayerLocation::LABYRINTH && p2_loc == p1_loc 
				&& p3_loc == p1_loc && p4_loc == p1_loc)
			{
				one_player_in_lab = false;
			}
		}
		
		//render for labyrinth if any of the players are in labyrinth
		if(one_player_in_lab)
		{
			m_labyrinth->render(gDrawManager);
		}
		
		//render for each mini dungeon
		
		if(m_mini_dungeon_1)
		{
			std::int16_t d_index = m_mini_dungeon_1->GetDungeonIndex();
			
			if(p1_index_dungeon == d_index || 
				p2_index_dungeon == d_index ||
				p3_index_dungeon == d_index ||
				p4_index_dungeon == d_index)
			{
				m_mini_dungeon_1->render(gDrawManager);
			}
		}
		
		if(m_mini_dungeon_2)
		{
			std::int16_t d_index = m_mini_dungeon_2->GetDungeonIndex();
			
			if(p1_index_dungeon == d_index || 
				p2_index_dungeon == d_index ||
				p3_index_dungeon == d_index ||
				p4_index_dungeon == d_index)
			{
				m_mini_dungeon_2->render(gDrawManager);
			}
		}
		
		if(m_mini_dungeon_3)
		{
			std::int16_t d_index = m_mini_dungeon_3->GetDungeonIndex();
			
			if(p1_index_dungeon == d_index || 
				p2_index_dungeon == d_index ||
				p3_index_dungeon == d_index ||
				p4_index_dungeon == d_index)
			{
				m_mini_dungeon_3->render(gDrawManager);
			}
		}
		
		if(m_mini_dungeon_4)
		{
			std::int16_t d_index = m_mini_dungeon_4->GetDungeonIndex();
			
			if(p1_index_dungeon == d_index || 
				p2_index_dungeon == d_index ||
				p3_index_dungeon == d_index ||
				p4_index_dungeon == d_index)
			{
				m_mini_dungeon_4->render(gDrawManager);
			}
		}
		
		if(m_winner_room)
		{
			m_winner_room->render(gDrawManager);
		}
	}
	
}



WinnerDecisionRoom* LabyrinthDungeonManager::GetPointerToWinnerDecisionRoom(){return m_winner_room.get();}

Labyrinth* LabyrinthDungeonManager::GetPointerToLabyrinth(){return m_labyrinth.get();}

bool LabyrinthDungeonManager::GetLabyrinthCreatedBool(){return labyrinthCreated;}

void LabyrinthDungeonManager::RunCollisionHandlersOps()
{
	int num_players = m_player_manager_ptr->GetNumberOfPlayers();
	
	PlayerManager::PlayerLocation location = PlayerManager::PlayerLocation::NONE;
	
	if(mainLabCollisionHandler && m_player_manager_ptr)
	{
		location = PlayerManager::PlayerLocation::LABYRINTH;
		mainLabCollisionHandler->run_collision_handler(*m_player_manager_ptr,location);
	}
	
	if(miniCollisionHandler_winner_room && m_player_manager_ptr)
	{
		location = PlayerManager::PlayerLocation::WINNER_ROOM;
		miniCollisionHandler_winner_room->run_collision_handler(*m_player_manager_ptr,location);
	}
	
}
