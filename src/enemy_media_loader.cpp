#include "enemy_media_loader.h"


bool loadEnemyMedia(SDL_Renderer* gRenderer)
{
    
    if(!setupLoad_Cockroach(gRenderer)){return false;}
    
    return true;
}


//Setup cockroach media
LTexture cockroach_texture;
std::vector <SDL_Rect> cockroach_walk_clips;
bool setupLoad_Cockroach(SDL_Renderer* gRenderer)
{
    //load cockroach media
    if(!loadCockRoachMedia(&cockroach_texture,
                        cockroach_walk_clips,
                        gRenderer )
    )
    {
        printf("Failed to load cockroach media! \n");
        return false;
    }
    
    return true;
}

void freeEnemyMedia()
{
    freeCockRoachMedia(&cockroach_texture);
}

