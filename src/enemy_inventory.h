#ifndef ENEMY_INVENTORY_H
#define ENEMY_INVENTORY_H

#include "enemy_media_loader.h"
#include "collisionhandler.h" // for check collision

//Game Setup

extern std::vector <Enemy*> enemies_vector;
//function to setup global vector of enemies
void setupEnemyVector();

//Game Loop Functions

//function to run event handling for enemies
void run_enemies_handle_events(RNGType& rngSeed,SDL_Rect& camera);

//function to run logic for enemies
void run_enemies_logic(float& timeStep,SDL_Rect& camera, 
                        std::vector <DungeonTile*> &labyrinthTilesVector);

void run_enemies_render(SDL_Rect& camera,SDL_Renderer* gRenderer );

//function to check remove enemies on screen that died
void checkAndRemoveDeadEnemies(SDL_Rect& camera);

//End Game Functions

//function to free global vector of enemies
void freeEnemyVector();
//function to free media of all enemies
void freeEnemyMedia();

#endif