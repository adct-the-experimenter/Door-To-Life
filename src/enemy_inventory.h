#ifndef ENEMY_INVENTORY_H
#define ENEMY_INVENTORY_H

#include "enemy_media_loader.h"
#include "collisionhandler.h" // for check collision

#include <vector>

#include "audio_renderer.h"

//class to generate enemies in labyrinth and handle their logic and events

class EnemyInventory
{
public:
	EnemyInventory();
	~EnemyInventory();
	
	//function to setup global vector of enemies
	void setupEnemyVector();
	std::vector <Enemy*> *GetEnemyVector();
	
	//Game Loop Functions

	//function to run event handling for enemies
	void run_enemies_handle_events(RNGType& rngSeed,SDL_Rect& camera);

	//function to run logic for enemies
	void run_enemies_logic(float& timeStep,SDL_Rect& camera, 
							std::vector <DungeonTile*> &labyrinthTilesVector);
	
	//function to render enemies
	void run_enemies_render(SDL_Rect& camera,SDL_Renderer* gRenderer );
	
	//function to render sound of enemies
	void run_enemies_sound(SDL_Rect& camera, AudioRenderer* gAudioRenderer);

	//function to check remove enemies on screen that died
	void checkAndRemoveDeadEnemies(SDL_Rect& camera);

	//End Game Functions

	//function to free global vector of enemies
	void freeEnemyVector();
	//function to free media of all enemies
	void freeEnemyMedia();
	
private:
	std::vector <Enemy*> enemies_vector;
};


#endif
