#ifndef PLAYER_MANAGER_H
#define PLAYER_MANAGER_H

#include "player.h"

class PlayerManager
{

public:
	
	PlayerManager();
	~PlayerManager();
	
	void SetPointerToPlayerOne(Player* player);
	void SetPointerToPlayerTwo(Player* player);
	void SetPointerToPlayerThree(Player* player);
	void SetPointerToPlayerFour(Player* player);
	
	Player* GetPointerToPlayerOne();
	Player* GetPointerToPlayerTwo();
	Player* GetPointerToPlayerThree();
	Player* GetPointerToPlayerFour();
	
	void SetPointerToCameraOne(SDL_Rect* camera);
	void SetPointerToCameraTwo(SDL_Rect* camera);
	void SetPointerToCameraThree(SDL_Rect* camera);
	void SetPointerToCameraFour(SDL_Rect* camera);
	
	SDL_Rect* GetPointerToCameraOne();
	SDL_Rect* GetPointerToCameraTwo();
	SDL_Rect* GetPointerToCameraThree();
	SDL_Rect* GetPointerToCameraFour();
	
	void SetMultiplePlayersBool(bool state);
	bool GetMultiplePlayersBool();
	
	void SetNumberOfPlayers(int num);
	int GetNumberOfPlayers();
	
	//game loop functions
	
	void handleEvent(Event& thisEvent);
	void logic(float& timestep);
	void sound(AudioRenderer* gAudioRenderer);
	
	void handleEvent_player1(Event& thisEvent);	
	void handleEvent_player2(Event& thisEvent);
	void handleEvent_player3(Event& thisEvent);
	void handleEvent_player4(Event& thisEvent);
		
	//enum to describe where player is. 
	// Transition partially counts as a location and is used to help the labyrinthdungeonmanager class
	// move player from one place to another.
	enum class PlayerLocation : std::int8_t {NONE=0, LABYRINTH, DUNGEON, WINNER_ROOM,
											LABYRINTH_2_DUNGEON, DUNGEON_2_LABYRINTH, 
											LABYRINTH_2_WINNER_ROOM, WINNER_ROOM_2_LABYRINTH};
	
	void SetLocationEnumOfPlayer(PlayerLocation thisLocation, int num_player);
	void GetLocationEnumOfPlayers(PlayerLocation* p1,PlayerLocation* p2,PlayerLocation* p3,PlayerLocation* p4);
	
	void SetDungeonEnteredForPlayer(std::int16_t dungeon_index, int num_player);
	void GetDungeonIndexesForPlayersInDungeon(std::int16_t* p1,std::int16_t* p2,std::int16_t* p3,std::int16_t* p4 );
	
	std::int16_t GetDungeonIndexForThisPlayerInDungeon(int num_player);
	
private:
	
	//pointers to players
	Player* player_one_ptr;
	Player* player_two_ptr;
	Player* player_three_ptr;
	Player* player_four_ptr;
	
	//pointers to cameras following players
	SDL_Rect* camera1_ptr;
	SDL_Rect* camera2_ptr;
	SDL_Rect* camera3_ptr;
	SDL_Rect* camera4_ptr;
	
	bool mulitple_players_bool;
	int m_num_players;
	
	//info on which dungeons players are in
	
	PlayerManager::PlayerLocation player1_location;
	PlayerManager::PlayerLocation player2_location;
	PlayerManager::PlayerLocation player3_location;
	PlayerManager::PlayerLocation player4_location;
	
	//index of dungeon that players are in
	std::int16_t num_dungeon_index_p1;
	std::int16_t num_dungeon_index_p2;
	std::int16_t num_dungeon_index_p3;
	std::int16_t num_dungeon_index_p4;
	

};

#endif
