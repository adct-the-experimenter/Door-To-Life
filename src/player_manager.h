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
	
	
	//game loop functions
	
	void logic(float& timestep);
	void sound(AudioRenderer* gAudioRenderer);
	
private:
	
	Player* player_one_ptr;
	Player* player_two_ptr;
	Player* player_three_ptr;
	Player* player_four_ptr;
};

#endif
