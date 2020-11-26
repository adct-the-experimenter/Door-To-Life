#include "winner_judge.h"

WinnerJudge::WinnerJudge()
{
	//set collider
	collider.x = 0;
	collider.y = 0;
	collider.w = 20;
	collider.h = 20;
	
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

void WinnerJudge::CheckPlayerandJudgeCollisions(PlayerManager* pm)
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
	
	if(p1)
	{
		//if there is a collision
		if(checkCollision(collider,*p1->getCollisionObjectPtr()->ptrToCollisionBox))
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
		if(checkCollision(collider,*p2->getCollisionObjectPtr()->ptrToCollisionBox))
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
		if(checkCollision(collider,*p3->getCollisionObjectPtr()->ptrToCollisionBox))
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
		if(checkCollision(collider,*p4->getCollisionObjectPtr()->ptrToCollisionBox))
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

void WinnerJudge::render(DrawingManager* gDrawManager)
{
	if(m_texture_ptr)
	{
		m_texture_ptr->render(collider.x,collider.y,gDrawManager->GetPointerToRenderer(),nullptr);
	}
}
