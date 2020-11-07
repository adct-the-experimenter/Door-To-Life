#include "enemy_media_loader.h"


bool loadEnemyMedia(SDL_Renderer* gRenderer)
{
    
    if(!setupLoad_Cockroach(gRenderer)){return false;}
    
    if(!setupLoad_GreedyZombie(gRenderer)){return false;}
    
    return true;
}


//Setup cockroach media
LTexture cockroach_texture;
std::vector <SDL_Rect> cockroach_walk_clips;
ALuint cockroach_scream_buffer;
bool setupLoad_Cockroach(SDL_Renderer* gRenderer)
{
    //load cockroach visual media
    if(!loadCockRoachVisualMedia(&cockroach_texture,
                        cockroach_walk_clips,
                        gRenderer )
    )
    {
        printf("Failed to load cockroach visual media! \n");
        return false;
    }
    
    //load cockroach audio media
    if(!loadCockRoachAudioMedia(&cockroach_scream_buffer))
    {
		printf("Failed to load cockroach audio media! \n");
        return false;
	}
    
    return true;
}

//Setup greedy zombie media
LTexture greed_zombie_texture;
std::vector <SDL_Rect> greed_zombie_walk_clips;
bool setupLoad_GreedyZombie(SDL_Renderer* gRenderer)
{
    //load greedy zombie media
    if(!loadGreedyZombieMedia(&greed_zombie_texture,
                        greed_zombie_walk_clips,
                        gRenderer )
    )
    {
        printf("Failed to load greedy zombie media! \n");
        return false;
    }
    
    return true;
}

void freeEnemyMedia()
{
    greed_zombie_texture.free();
    cockroach_texture.free();
    //freeCockRoachVisualMedia(&cockroach_texture);
    freeCockRoachAudioMedia(&cockroach_scream_buffer);
    //freeGreedyZombieMedia(&greed_zombie_texture);
    
}

