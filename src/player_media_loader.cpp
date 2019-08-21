#include "player_media_loader.h"

//initialize vector of sprite clips
std::vector <SDL_Rect> player_clips;

void setupPlayerSpriteClips()
{
	
    player_clips.resize(32);
    
    std::int8_t width = 35;
    std::int8_t height = 62;
    
    player_clips[Sprite::UP_1] = {15,196,width,height};
    player_clips[Sprite::UP_2] = {80,196,width,height}; 
    player_clips[Sprite::UP_3] = {143,196,width,height}; 
    player_clips[Sprite::UP_4] = {207,196,width,height};
    
    player_clips[Sprite::LEFT_1] = {15,64,width,height};
    player_clips[Sprite::LEFT_2] = {80,64,width,height};
    player_clips[Sprite::LEFT_3] = {143,64,width,height};
    player_clips[Sprite::LEFT_4] = {207,64,width,height};
    
    player_clips[Sprite::DOWN_1] = {16,1,width,height};
    player_clips[Sprite::DOWN_2] = {80,1,width,height};
    player_clips[Sprite::DOWN_3] = {143,1,width,height};
    player_clips[Sprite::DOWN_4] = {207,1,width,height};
    
    player_clips[Sprite::RIGHT_1] = {15,128,width,height};
    player_clips[Sprite::RIGHT_2] = {80,128,width,height};
    player_clips[Sprite::RIGHT_3] = {143,128,width,height};
    player_clips[Sprite::RIGHT_4] = {207,128,width,height};
    
    player_clips[Sprite::DOWN_RIGHT_1] = {12,257,width,height};
    player_clips[Sprite::DOWN_RIGHT_2] = {76,258,width,height};
    player_clips[Sprite::DOWN_RIGHT_3] = {140,258,width,height};
    player_clips[Sprite::DOWN_RIGHT_4] = {204,258,width,height};
    
    player_clips[Sprite::DOWN_LEFT_1] = {17,321,width,height};
    player_clips[Sprite::DOWN_LEFT_2] = {81,321,width,height};
    player_clips[Sprite::DOWN_LEFT_3] = {145,321,width,height};
    player_clips[Sprite::DOWN_LEFT_4] = {209,321,width,height};
    
    player_clips[Sprite::UP_LEFT_1] = {17,385,width,height};
    player_clips[Sprite::UP_LEFT_2] = {81,385,width,height};
    player_clips[Sprite::UP_LEFT_3] = {145,385,width,height};
    player_clips[Sprite::UP_LEFT_4] = {209,385,width,height};
    
    player_clips[Sprite::UP_RIGHT_1] = {12,450,width,height};
    player_clips[Sprite::UP_RIGHT_2] = {76,450,width,height};
    player_clips[Sprite::UP_RIGHT_3] = {140,450,width,height};
    player_clips[Sprite::UP_RIGHT_4] = {204,450,width,height};
}

bool setup_loadPlayerMedia(Player* thisPlayer,SDL_Renderer* gRenderer)
{
	//load main player media
    std::string mainPlayerTexFilePath = DATADIR_STR + std::string("/Graphics/main_char.png");
    
    if(!thisPlayer->loadMedia(nullptr,mainPlayerTexFilePath.c_str(),gRenderer))
    {
        printf("Failed to load player media! \n");
        return false;
    }
    else
    {
		setupPlayerSpriteClips();
		thisPlayer->setSpriteClips(&player_clips);
	}
	
	return true;
}
