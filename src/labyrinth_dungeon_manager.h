#ifndef LABYRINTH_DUNGEON_MANAGER_H
#define LABYRINTH_DUNGEON_MANAGER_H


#include <memory> //for unique_ptr
#include "globalvariables.h"
#include "Dungeon.h"
#include "labyrinth.h"

#include "collisionhandler.h"

#include "DungeonXMLReader.h"

#include "WinnerDecisionRoom.h"

class LabyrinthDungeonManager : public GameState
{
public:
	LabyrinthDungeonManager();
	~LabyrinthDungeonManager();
	
	void SetPointerToPlayerManager(PlayerManager* pm);
	
	void SetPointerToTimer(LTimer* timer);
	
	void SetPointerToGameInventory(GameInventory* thisInventory);
	
	void setupScreenDimensions(std::int16_t width, std::int16_t height);
	
	//labyrinth specific functions
	bool setupLabyrinth(PlayerManager* mainPlayerManager, GameInventory* gameInventory,
											DungeonXMLRegistry* dungeon_xml_reg, RNGType& rngSeed,
											LTimer* stepTimer, Dot* mainDotPointer,
											std::int16_t SCREEN_WIDTH , std::int16_t SCREEN_HEIGHT,
											LTexture& keyTexture, ALuint& keySource,ALuint& keyBuffer,
											LTexture& doorTexture, ALuint& doorSource, ALuint& doorBufferOpen, ALuint& doorBufferFail,
											std::vector <SDL_Rect> &doorClips);
	
	

											
	Labyrinth* GetPointerToLabyrinth();
	
	bool GetLabyrinthCreatedBool();

	void LabyrinthToMiniDungeonTransitionOperations();
	
	//dungeon specific functions
	
	void SetPointerToDungeonXMLRegistry(DungeonXMLRegistry* reg);
	
	void MiniDungeonToLabyrinthTransitionOperations();
	
	void SetupMiniDungeon(int num_player, std::int16_t& num_mini_dungeon_entered);
	void CloseMiniDungeon(int num_player);
	
	//winner decision room specific functions
	
	bool setupWinnerRoom(PlayerManager* pm,GameInventory* gameInventory);
	
	void LabyrinthToWinnerDecisionRoomTransitionOperations();
	
	void WinnerDecisionRoomToLabyrinthTransitionOperations();
	
	WinnerDecisionRoom* GetPointerToWinnerDecisionRoom();
	
	//Game loop functions
	
	virtual void setState(GameState::State thisState);
    virtual GameState::State getState();
      
	virtual void handle_events(Event& thisEvent);
	virtual void handle_events_RNG(RNGType& rngSeed);
	virtual void logic();
	virtual void sound(AudioRenderer* gAudioRenderer);
	virtual void render(SDL_Renderer* gRenderer);
	
	virtual void render(DrawingManager* gDrawManager);
	
	void RunCollisionHandlersOps();
	
	void CheckForWinners();
	void GetWinnersBool(bool* p1, bool* p2, bool* p3, bool* p4);
	
private:
	
	PlayerManager* m_player_manager_ptr;
	
	LTimer* stepTimer;
	
	std::int16_t SCREEN_WIDTH,SCREEN_HEIGHT;
	
	GameInventory* m_game_inventory_ptr;
	
	//labyrinth
	std::unique_ptr <Labyrinth> m_labyrinth;
	std::unique_ptr <CollisonHandler> mainLabCollisionHandler;
	bool labyrinthCreated;
	
	//dungeons
	
	DungeonXMLRegistry* m_dungeon_xml_reg_ptr;
	
	
	//container for a mini dungeons, one for each player
	std::unique_ptr <Dungeon> m_mini_dungeon_1;
	std::unique_ptr <Dungeon> m_mini_dungeon_2;
	std::unique_ptr <Dungeon> m_mini_dungeon_3;
	std::unique_ptr <Dungeon> m_mini_dungeon_4;
	
	//collision handlers for each mini dungeon
	std::unique_ptr <CollisonHandler> miniCollisionHandler_d1;
	std::unique_ptr <CollisonHandler> miniCollisionHandler_d2;
	std::unique_ptr <CollisonHandler> miniCollisionHandler_d3;
	std::unique_ptr <CollisonHandler> miniCollisionHandler_d4;
	

	
	float player1PosX_beforedungeon;
	float player1PosY_beforedungeon;
	
	float player2PosX_beforedungeon;
	float player2PosY_beforedungeon;
	
	float player3PosX_beforedungeon;
	float player3PosY_beforedungeon;
	
	float player4PosX_beforedungeon;
	float player4PosY_beforedungeon;
	
	//winner room
	
	std::unique_ptr <WinnerDecisionRoom> m_winner_room;
	
	std::unique_ptr <CollisonHandler> miniCollisionHandler_winner_room;
	
	bool player1_win;
	bool player2_win;
	bool player3_win;
	bool player4_win;
	
};

#endif
