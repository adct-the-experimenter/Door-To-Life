#ifndef WINNER_JUDGE_H
#define WINNER_JUDGE_H

#include "collisionhandler.h"
#include "LTexture.h"

#include "DrawingManager.h"
#include "player_manager.h"

#include <cstdint>

//class made to choose a winner
//Done by setting the number of players needed to touch the object
//and just choosing the first number of players to touch it to win

class WinnerJudge
{
public:
	WinnerJudge();
	~WinnerJudge();
	
	//set number of players to win
	void SetNumberOfPlayersToWin(std::int8_t num);
	
	//get winners based on player number
	enum class WinningPlayers : std::int8_t {NONE = 0, 
											PLAYERS_1, PLAYERS_2, PLAYERS_3, PLAYERS_4,
											
											//2 player permutations
											PLAYERS_1_2, PLAYERS_1_3, PLAYERS_1_4,
											PLAYERS_2_3, PLAYERS_2_4, 
											PLAYERS_3_4,
											
											//3 player permutations
											PLAYERS_1_2_3, PLAYERS_1_2_4, PLAYERS_1_3_4,
											PLAYERS_2_3_4,
											
											//4 player permutation
											PLAYERS_1_2_3_4
											};
	WinningPlayers GetPlayersWon();
	
	//function to return if there are winners
	bool GetWinnersSetBool();
	
	//set position of the judge
	void SetPosition(std::int16_t x, std::int16_t y);
	
	//set pointer to texture for judge
	void SetPointerToTexture(LTexture* thisTexture);
	
	SDL_Rect* getCollisionBoxPtr();
	
//game loop functions
	
	//check collision for players
	void CheckPlayerandJudgeCollisions(PlayerManager* pm, PlayerManager::PlayerLocation location);
	
	//render the judge
	void render(SDL_Renderer* gRenderer, SDL_Rect& camera);
	
private:
	
	//number of players to win
	std::int8_t num_players_win;
		
	//rectangle representing collision object of the winner judge
	SDL_Rect collider;
	
	//var indicating who won
	WinningPlayers players_won;
	
	bool winners_set;
	
	LTexture* m_texture_ptr;
	
};

#endif
