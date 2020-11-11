#include "player_manager.h"

PlayerManager::PlayerManager()
{
	player_one_ptr = nullptr;
	player_two_ptr = nullptr;
	player_three_ptr = nullptr;
	player_four_ptr = nullptr;
}

PlayerManager::~PlayerManager()
{
	
}
	
void PlayerManager::SetPointerToPlayerOne(Player* player){player_one_ptr = player;}
void PlayerManager::SetPointerToPlayerTwo(Player* player){player_two_ptr = player;}
void PlayerManager::SetPointerToPlayerThree(Player* player){player_three_ptr = player;}
void PlayerManager::SetPointerToPlayerFour(Player* player){player_four_ptr = player;}

Player* PlayerManager::GetPointerToPlayerOne(){return player_one_ptr;}
Player* PlayerManager::GetPointerToPlayerTwo(){return player_two_ptr;}
Player* PlayerManager::GetPointerToPlayerThree(){return player_three_ptr;}
Player* PlayerManager::GetPointerToPlayerFour(){return player_four_ptr;}
