#ifndef PLAYER_MEDIA_LOADER_H
#define PLAYER_MEDIA_LOADER_H

#include "player.h" //for player pointer walk anim frames enum
extern std::vector <SDL_Rect> player_clips;


void setupPlayerSpriteClips();

bool setup_loadPlayerMedia(Player* thisPlayer,SDL_Renderer* gRenderer, int num_player);


#endif
