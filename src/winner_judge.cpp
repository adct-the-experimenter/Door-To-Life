#include "winner_judge.h"

WinnerJudge::WinnerJudge()
{
	//set collider
	collider.x = 0;
	collider.y = 0;
	collider.w = 80;
	collider.h = 80;
	
}

WinnerJudge::~WinnerJudge()
{
	
}

void WinnerJudge::SetNumberOfPlayersToWin(std::int8_t num)
{
	num_players_win = num;
}

bool WinnerJudge::GetWinnersSetBool(){return winners_set;}

WinnerJudge::WinningPlayers WinnerJudge::GetPlayersWon()
{
	return players_won;
}

void WinnerJudge::SetPosition(std::int16_t x, std::int16_t y)
{
	collider.x = x;
	collider.y = y;
}

void WinnerJudge::SetPointerToTexture(LTexture* thisTexture){m_texture_ptr = thisTexture;}

SDL_Rect* WinnerJudge::getCollisionBoxPtr(){return &collider;}

void WinnerJudge::CheckPlayerandJudgeCollisions(PlayerManager* pm, PlayerManager::PlayerLocation location)
{
	//count for number of players touching the judge
	int player_collision_count = 0;
	
	Player* p1 = pm->GetPointerToPlayerOne();
	Player* p2 = pm->GetPointerToPlayerTwo();
	Player* p3 = pm->GetPointerToPlayerThree();
	Player* p4 = pm->GetPointerToPlayerFour();
	
	bool p1_collide = false;
	bool p2_collide = false;
	bool p3_collide = false;
	bool p4_collide = false;
	
	//make collision check location dependent
	PlayerManager::PlayerLocation p1_loc, p2_loc, p3_loc, p4_loc;
	pm->GetLocationEnumOfPlayers(&p1_loc,&p2_loc,&p3_loc,&p4_loc);
	
	if(p1)
	{
		//if there is a collision
		if(p1_loc == location && checkCollision(collider,*p1->getCollisionObjectPtr()->ptrToCollisionBox))
		{
			p1_collide = true;
			player_collision_count++;
		}
	}
	
	if(player_collision_count == 1 && num_players_win == 1 
		&& p1_collide)
	{
		winners_set = true;
		players_won = WinnerJudge::WinningPlayers::PLAYERS_1;
		return; 
	}

	if(p2)
	{
		//if there is a collision
		if(p2_loc == location && checkCollision(collider,*p2->getCollisionObjectPtr()->ptrToCollisionBox))
		{
			p2_collide = true;
			player_collision_count++;
		}
	}
	
	if(player_collision_count == 1 && num_players_win == 1 
		&& p2_collide)
	{
		winners_set = true;
		players_won = WinnerJudge::WinningPlayers::PLAYERS_2; 
		return; 
	}
	
	if(player_collision_count == 2 && num_players_win == 2 
		&& p1_collide && p2_collide)
	{
		winners_set = true;
		players_won = WinnerJudge::WinningPlayers::PLAYERS_1_2;
		return; 
	}
	
	if(p3)
	{
		//if there is a collision
		if(p3_loc == location && checkCollision(collider,*p3->getCollisionObjectPtr()->ptrToCollisionBox))
		{
			p3_collide = true;
			player_collision_count++;
		}
	}
	
	if(player_collision_count == 1 && num_players_win == 1 
		&& p3_collide)
	{
		winners_set = true;
		players_won = WinnerJudge::WinningPlayers::PLAYERS_3; 
		return; 
	}
	
	if(player_collision_count == 2 && num_players_win == 2 
		&& p1_collide && p3_collide)
	{
		winners_set = true;
		players_won = WinnerJudge::WinningPlayers::PLAYERS_1_3;
		return; 
	}
	
	if(player_collision_count == 2 && num_players_win == 2 
		&& p2_collide && p3_collide)
	{
		winners_set = true;
		players_won = WinnerJudge::WinningPlayers::PLAYERS_2_3;
		return; 
	}
	
	if(player_collision_count == 3 && num_players_win == 3 
		&& p1_collide && p2_collide && p3_collide)
	{
		winners_set = true;
		players_won = WinnerJudge::WinningPlayers::PLAYERS_1_2_3;
		return; 
	}
	
	if(p4)
	{
		if(p4_loc == location && checkCollision(collider,*p4->getCollisionObjectPtr()->ptrToCollisionBox))
		{
			p4_collide = true;
			player_collision_count++;
		}
	}
	
	if(player_collision_count == 1 && num_players_win == 1 
		&& p4_collide)
	{
		winners_set = true;
		players_won = WinnerJudge::WinningPlayers::PLAYERS_4; 
		return; 
	}
	
	if(player_collision_count == 2 && num_players_win == 2 
		&& p1_collide && p4_collide)
	{
		winners_set = true;
		players_won = WinnerJudge::WinningPlayers::PLAYERS_1_4;
		return; 
	}
	
	if(player_collision_count == 2 && num_players_win == 2 
		&& p2_collide && p4_collide)
	{
		winners_set = true;
		players_won = WinnerJudge::WinningPlayers::PLAYERS_2_4;
		return; 
	}
	
	if(player_collision_count == 2 && num_players_win == 2 
		&& p3_collide && p4_collide)
	{
		winners_set = true;
		players_won = WinnerJudge::WinningPlayers::PLAYERS_3_4;
		return; 
	}
	
	if(player_collision_count == 3 && num_players_win == 3 
		&& p1_collide && p2_collide && p4_collide)
	{
		winners_set = true;
		players_won = WinnerJudge::WinningPlayers::PLAYERS_1_2_4;
		return; 
	}
	
	if(player_collision_count == 3 && num_players_win == 3 
		&& p1_collide && p4_collide && p3_collide)
	{
		winners_set = true;
		players_won = WinnerJudge::WinningPlayers::PLAYERS_1_3_4;
		return; 
	}
	
	if(player_collision_count == 3 && num_players_win == 3 
		&& p4_collide && p2_collide && p3_collide)
	{
		winners_set = true;
		players_won = WinnerJudge::WinningPlayers::PLAYERS_2_3_4;
		return; 
	}
	
	if(player_collision_count == 4 && num_players_win == 4 
		&& p1_collide && p2_collide && p3_collide && p4_collide)
	{
		winners_set = true;
		players_won = WinnerJudge::WinningPlayers::PLAYERS_1_2_3_4;
		return; 
	}
}

void WinnerJudge::render(SDL_Renderer* gRenderer, SDL_Rect& camera)
{
	if(m_texture_ptr)
	{
		std::int16_t x = collider.x - camera.x;
        std::int16_t y = collider.y - camera.y;
        
		m_texture_ptr->render(x,y,gRenderer,nullptr);
	}
}
