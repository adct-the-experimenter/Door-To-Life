#include "player_manager.h"

PlayerManager::PlayerManager()
{
	player_one_ptr = nullptr;
	player_two_ptr = nullptr;
	player_three_ptr = nullptr;
	player_four_ptr = nullptr;
	
	mulitple_players_bool = false;
	
	num_dungeon_index_p1 = 0;
	num_dungeon_index_p2 = 0;
	num_dungeon_index_p3 = 0;
	num_dungeon_index_p4 = 0;
	
	player1_location = PlayerManager::PlayerLocation::NONE;
	player2_location = PlayerManager::PlayerLocation::NONE;
	player3_location = PlayerManager::PlayerLocation::NONE;
	player4_location = PlayerManager::PlayerLocation::NONE;
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

void PlayerManager::handleEvent_player3(Event& thisEvent)
{
	if(player_three_ptr)
	{
		player_three_ptr->handleEvent(thisEvent);
	}
}

void PlayerManager::handleEvent_player4(Event& thisEvent)
{
	if(player_four_ptr)
	{
		player_four_ptr->handleEvent(thisEvent);
	}
}

void PlayerManager::logic(float& timestep)
{
	
	if(player_one_ptr)
	{
		if(player_one_ptr->getHealth() > 0){player_one_ptr->logic(timestep);}
	}
	if(player_two_ptr)
	{
		if(player_two_ptr->getHealth() > 0){player_two_ptr->logic(timestep);}
	}
	if(player_three_ptr)
	{
		if(player_three_ptr->getHealth() > 0){player_three_ptr->logic(timestep);}
	}
	if(player_four_ptr)
	{
		if(player_four_ptr->getHealth() > 0){player_four_ptr->logic(timestep);}
	}
}

void PlayerManager::sound(AudioRenderer* gAudioRenderer)
{
	
}



void PlayerManager::SetLocationEnumOfPlayer(PlayerLocation thisLocation, int num_player)
{
	switch(num_player)
	{
		case 1:{ player1_location = thisLocation; break;}
		case 2:{ player2_location = thisLocation; break;}
		case 3:{ player3_location = thisLocation; break;}
		case 4:{ player4_location = thisLocation; break;}
	}
}

void PlayerManager::GetLocationEnumOfPlayers(PlayerLocation* p1,PlayerLocation* p2,PlayerLocation* p3,PlayerLocation* p4)
{
	*p1 = player1_location;
	*p2 = player2_location;
	*p3 = player3_location;
	*p4 = player4_location;
}

void PlayerManager::SetDungeonEnteredForPlayer(std::int16_t dungeon_index, int num_player)
{
	switch(num_player)
	{
		case 1:{ num_dungeon_index_p1 = dungeon_index; break;}
		case 2:{ num_dungeon_index_p2 = dungeon_index; break;}
		case 3:{ num_dungeon_index_p3 = dungeon_index; break;}
		case 4:{ num_dungeon_index_p4 = dungeon_index; break;}
		default:{ std::cout << "Invalid dungeon index entered for player!\n"; break;}
	}
}

void PlayerManager::GetDungeonIndexesForPlayersInDungeon(std::int16_t* p1,std::int16_t* p2,std::int16_t* p3,std::int16_t* p4 )
{
	*p1 = num_dungeon_index_p1;
	*p2 = num_dungeon_index_p2;
	*p3 = num_dungeon_index_p3;
	*p4 = num_dungeon_index_p4;
}

std::int16_t PlayerManager::GetDungeonIndexForThisPlayerInDungeon(int num_player)
{
	std::int16_t indexToReturn = 0;
	
	switch(num_player)
	{
		case 1:{ return indexToReturn = num_dungeon_index_p1; break;}
		case 2:{ return indexToReturn = num_dungeon_index_p2; break;}
		case 3:{ return indexToReturn = num_dungeon_index_p3; break;}
		case 4:{ return indexToReturn = num_dungeon_index_p4; break;}
	}
	
	return indexToReturn;
}

void PlayerManager::KeepCamerasInBounds()
{
	//player 1 camera
	SDL_Rect* thisCamera = PlayerManager::GetPointerToCameraOne();
	
	if(thisCamera)
	{
		if(thisCamera->x < 0){thisCamera->x = 0;} 
		if(thisCamera->y < 0){thisCamera->y = 0;} 
		std::cout << "camera  x: " << thisCamera->x << " y: " << thisCamera->y << std::endl;
	}
	
	//player 2 camera
	thisCamera = PlayerManager::GetPointerToCameraTwo();
	
	if(thisCamera && m_num_players > 1)
	{
		if(thisCamera->x < 1){thisCamera->x = 1;} 
		if(thisCamera->y < 1){thisCamera->y = 1;} 
	}
	
	//player 3 camera
	thisCamera = PlayerManager::GetPointerToCameraThree();
	
	if(thisCamera && m_num_players > 2)
	{
		if(thisCamera->x < 1){thisCamera->x = 1;} 
		if(thisCamera->y < 1){thisCamera->y = 1;} 
	}
	
	//player 4 camera
	thisCamera = PlayerManager::GetPointerToCameraFour();
	
	if(thisCamera && m_num_players > 3)
	{
		if(thisCamera->x < 1){thisCamera->x = 1;} 
		if(thisCamera->y < 1){thisCamera->y = 1;} 
	}
}
