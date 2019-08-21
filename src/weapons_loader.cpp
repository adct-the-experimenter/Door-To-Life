#include "weapons_loader.h"


bool loadWeaponsMedia(SDL_Renderer* gRenderer)
{
    //load sword media
    if(!loadMedia_Sword(gRenderer))
    {
        printf("Failed to load media for sword! \n");
        return false;
    }
    
    //load gun media
    if(!loadMedia_Gun(gRenderer))
    {
		printf("Failed to load media for gun! \n");
		return false;
	}
	
	//load bullet media
	if(!loadMedia_Bullet(gRenderer))
	{
		printf("Failed to load media for bullets! \n");
		return false;
	}
    
    return true;
}

void freeWeaponsMedia()
{
    //freeMedia_Sword();
}

//Sword

LTexture sword_sprite_sheet_tex;
std::vector <SDL_Rect> sword_walk_clips;

bool loadSwordMedia(SDL_Renderer* gRenderer,LTexture* sTexture, 
                                std::vector <SDL_Rect> &s_walk_clips);
                                
bool loadMedia_Sword(SDL_Renderer* gRenderer)
{
    return loadSwordMedia(gRenderer,&sword_sprite_sheet_tex, sword_walk_clips);
}

void freeSwordMedia(LTexture* sTexture);

void freeMedia_Sword(){ freeSwordMedia(&sword_sprite_sheet_tex);}


//Gun

LTexture gun_sprite_sheet_tex;
std::vector <SDL_Rect> gun_walk_clips;

bool loadGunMedia(SDL_Renderer* gRenderer,LTexture* sTexture, 
                                std::vector <SDL_Rect> &s_walk_clips);
                                
bool loadMedia_Gun(SDL_Renderer* gRenderer)
{
    return loadGunMedia(gRenderer,&gun_sprite_sheet_tex, gun_walk_clips);
}

void freeGunMedia(LTexture* sTexture);

void freeMedia_Gun(){ freeGunMedia(&gun_sprite_sheet_tex);}

//Bullet

LTexture bullet_sprite_sheet_tex;
std::vector <SDL_Rect> bullet_direction_clips;

bool loadBulletMedia(SDL_Renderer* gRenderer,LTexture* bulletTexture, 
                                std::vector <SDL_Rect> &bullet_clips);

//function to load media for bullet
bool loadMedia_Bullet(SDL_Renderer* gRenderer)
{
	return loadBulletMedia(gRenderer,&bullet_sprite_sheet_tex, bullet_direction_clips);
}
