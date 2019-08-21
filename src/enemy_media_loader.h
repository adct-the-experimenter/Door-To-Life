#ifndef ENEMY_MEDIA_LOADER_H
#define ENEMY_MEDIA_LOADER_H

#include "othercockroach.h"

extern std::vector <Enemy*> enemies; 

bool loadEnemyMedia(SDL_Renderer* gRenderer);

//Other cock roach media
bool setupLoad_Cockroach(SDL_Renderer* gRenderer);
extern LTexture cockroach_texture;
extern std::vector <SDL_Rect> cockroach_walk_clips;
bool loadCockRoachMedia(LTexture* cTexture,
                        std::vector <SDL_Rect> &clips,
                        SDL_Renderer* gRenderer );
void freeCockRoachMedia(LTexture* cTexture);






                        
#endif