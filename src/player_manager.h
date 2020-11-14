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
	void handleEvent_player2(SDL_Joystick* joystick_controller);

	
private:
	
	Player* player_one_ptr;
	Player* player_two_ptr;
	Player* player_three_ptr;
	Player* player_four_ptr;
	
	SDL_Rect* camera1_ptr;
	SDL_Rect* camera2_ptr;
	SDL_Rect* camera3_ptr;
	SDL_Rect* camera4_ptr;
	
	bool mulitple_players_bool;
	int m_num_players;
	
};

#endif
