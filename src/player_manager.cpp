#include "player_manager.h"

PlayerManager::PlayerManager()
{
	player_one_ptr = nullptr;
	player_two_ptr = nullptr;
	player_three_ptr = nullptr;
	player_four_ptr = nullptr;
	
	mulitple_players_bool = false;
	
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


void PlayerManager::SetPointerToCameraOne(SDL_Rect* camera){camera1_ptr = camera;}
void PlayerManager::SetPointerToCameraTwo(SDL_Rect* camera){camera2_ptr = camera;}
void PlayerManager::SetPointerToCameraThree(SDL_Rect* camera){camera3_ptr = camera;}
void PlayerManager::SetPointerToCameraFour(SDL_Rect* camera){camera4_ptr = camera;}

SDL_Rect* PlayerManager::GetPointerToCameraOne(){return camera1_ptr;}
SDL_Rect* PlayerManager::GetPointerToCameraTwo(){return camera2_ptr;}
SDL_Rect* PlayerManager::GetPointerToCameraThree(){return camera3_ptr;}
SDL_Rect* PlayerManager::GetPointerToCameraFour(){return camera4_ptr;}

void PlayerManager::SetMultiplePlayersBool(bool state){mulitple_players_bool = state;}
bool PlayerManager::GetMultiplePlayersBool(){return mulitple_players_bool;}

void PlayerManager::SetNumberOfPlayers(int num){m_num_players = num;}
int PlayerManager::GetNumberOfPlayers(){return m_num_players;}

void PlayerManager::handleEvent(Event& thisEvent)
{
	if(player_one_ptr)
	{
		player_one_ptr->handleEvent(thisEvent);
	}
	if(player_two_ptr)
	{
		player_two_ptr->handleEvent(thisEvent);
	}
	if(player_three_ptr)
	{
		player_three_ptr->handleEvent(thisEvent);
	}
	if(player_four_ptr)
	{
		player_four_ptr->handleEvent(thisEvent);
	}
}

void PlayerManager::handleEvent_player1(Event& thisEvent)
{
	if(player_one_ptr)
	{
		player_one_ptr->handleEvent(thisEvent);
	}
}

void PlayerManager::handleEvent_player2(Event& thisEvent)
{
	if(player_two_ptr)
	{
		player_two_ptr->handleEvent(thisEvent);
	}
}

void PlayerManager::handleEvent_player2(SDL_Joystick* joystick_controller)
{
	if(player_two_ptr)
	{
		player_two_ptr->handleEvent(joystick_controller);
	}
}

void PlayerManager::logic(float& timestep)
{
	
	if(player_one_ptr)
	{
		player_one_ptr->logic(timestep);
	}
	if(player_two_ptr)
	{
		player_two_ptr->logic(timestep);
	}
	if(player_three_ptr){player_three_ptr->logic(timestep);}
	if(player_four_ptr){player_four_ptr->logic(timestep);}
}

void PlayerManager::sound(AudioRenderer* gAudioRenderer)
{
	
}

