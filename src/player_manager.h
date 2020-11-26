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
	
	void SetDungeonEnteredForPlayer(std::int16_t dungeon_index, int num_player);
	
	void SetDungeonEnteredBoolForPlayer(bool state, int num_player);
	
	void GetBoolsForPlayersInDungeon(bool* p1,bool* p2,bool* p3,bool* p4 );
	void GetDungeonIndexesForPlayersInDungeon(std::int16_t* p1,std::int16_t* p2,std::int16_t* p3,std::int16_t* p4 );
	
	std::int16_t GetDungeonIndexForThisPlayerInDungeon(int num_player);
	
	void SetDungeonExitBoolForPlayer(bool state, int num_player);
	void GetDungeonExitBoolForPlayers(bool* p1, bool* p2, bool* p3, bool* p4);
	
	void SetWinnerRoomBoolForPlayer(bool state, int num_player);
	void GetBoolsForPlayersInWinnerRoom(bool* p1,bool* p2,bool* p3,bool* p4 );
	
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
	
	//player bools in labyrinth or in dugneon
	bool player1_in_dungeon;
	bool player2_in_dungeon;
	bool player3_in_dungeon;
	bool player4_in_dungeon;
	
	bool player1_exit_dungeon;
	bool player2_exit_dungeon;
	bool player3_exit_dungeon;
	bool player4_exit_dungeon;
	
	//index of dungeon that players are in
	std::int16_t num_dungeon_index_p1;
	std::int16_t num_dungeon_index_p2;
	std::int16_t num_dungeon_index_p3;
	std::int16_t num_dungeon_index_p4;
	
	//player bool to indicate if in winner decition room
	bool player1_in_winner_room;
	bool player2_in_winner_room;
	bool player3_in_winner_room;
	bool player4_in_winner_room;
};

#endif
