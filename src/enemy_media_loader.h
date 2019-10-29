#ifndef ENEMY_MEDIA_LOADER_H
#define ENEMY_MEDIA_LOADER_H

#include "globalvariables.h"
#include "othercockroach.h"
#include "greedy_zombie.h"

extern std::vector <Enemy*> enemies; 

bool loadEnemyMedia(SDL_Renderer* gRenderer);

//Other cock roach media
bool setupLoad_Cockroach(SDL_Renderer* gRenderer);
extern LTexture cockroach_texture;
extern std::vector <SDL_Rect> cockroach_walk_clips;
extern ALuint cockroach_scream_buffer;
bool loadCockRoachVisualMedia(LTexture* cTexture,
                        std::vector <SDL_Rect> &clips,
                        SDL_Renderer* gRenderer );
void freeCockRoachVisualMedia(LTexture* cTexture);

bool loadCockRoachAudioMedia(ALuint* cockroachScreamBuffer);
void freeCockRoachAudioMedia(ALuint* cockroachScreamBuffer);

//Greedy Zombie media
bool setupLoad_GreedyZombie(SDL_Renderer* gRenderer);
extern LTexture greed_zombie_texture;
extern std::vector <SDL_Rect> greed_zombie_walk_clips;
bool loadGreedyZombieMedia(LTexture* cTexture,
                        std::vector <SDL_Rect> &clips,
                        SDL_Renderer* gRenderer );
void freeGreedyZombieMedia(LTexture* cTexture);


void freeEnemyMedia();





                        
#endif
