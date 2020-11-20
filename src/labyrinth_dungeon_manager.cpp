#include "labyrinth_dungeon_manager.h"


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

bool LabyrinthDungeonManager::setupLabyrinth(PlayerManager* mainPlayerManager, GameInventory* gameInventory,
											DungeonXMLRegistry* dungeon_xml_reg, RNGType& rngSeed,
											LTimer* stepTimer, Dot* mainDotPointer,
											std::int16_t SCREEN_WIDTH , std::int16_t SCREEN_HEIGHT,
											LTexture& dungeonTilesTexture, ALuint& dungeonMusicSource, ALuint& dungeonMusicBuffer,
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
        
        return true;
    }
    
    std::cout << "Failed to generate labyrinth! \n";
    return false;
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
		
		//handle events for mini dungeon for player 2 if player 2 is in mini dungeon
		
		//handle events for mini dungeon for player 3 if player 3 is in mini dungeon
		
		//handle events for mini dungeon for player 4 if player 4 is in mini dungeon
		
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
		//handle events for mini dungeon for player 2 if player 2 is in mini dungeon
		//handle events for mini dungeon for player 3 if player 3 is in mini dungeon
		//handle events for mini dungeon for player 4 if player 4 is in mini dungeon
		
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
		//do logic for mini dungeon for player 2 if player 2 is in mini dungeon
		//do logic for mini dungeon for player 3 if player 3 is in mini dungeon
		//do logic for mini dungeon for player 4 if player 4 is in mini dungeon
		
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
		//render mini dungeon for player 2 if player 2 is in mini dungeon
		//render mini dungeon for player 3 if player 3 is in mini dungeon
		//render mini dungeon for player 4 if player 4 is in mini dungeon
		
	}
	
}

Labyrinth* LabyrinthDungeonManager::GetPointerToLabyrinth(){return m_labyrinth.get();}

bool LabyrinthDungeonManager::GetLabyrinthCreatedBool(){return labyrinthCreated;}

