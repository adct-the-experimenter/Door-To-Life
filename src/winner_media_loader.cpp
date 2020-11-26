#include "winner_media_loader.h"

bool loadWinnerRoom_Media(SDL_Renderer* gRenderer)
{
	if(!setupLoad_WinnerRoomMedia(gRenderer))
	{
		return false;
	}
	
	return true;
}

void freeWinnerRoom_Media()
{
	freeWinnerDecisionRoomMedia(&winner_room_TilesTexture,
								   &winner_judge1_texture,&winner_judge2_texture,&winner_judge3_texture,&winner_judge4_texture,
								   &winner_room_MusicSource,&winner_room_MusicBuffer);
	
}

ALuint winner_room_MusicSource;
ALuint winner_room_MusicBuffer;
LTexture winner_room_TilesTexture;

LTexture winner_judge1_texture;
LTexture winner_judge2_texture;
LTexture winner_judge3_texture;
LTexture winner_judge4_texture;

bool setupLoad_WinnerRoomMedia(SDL_Renderer* gRenderer)
{
	if(!loadWinnerDecisionRoomMedia(gRenderer,&winner_room_TilesTexture,
								   &winner_judge1_texture,&winner_judge2_texture,&winner_judge3_texture,&winner_judge4_texture,
								   &winner_room_MusicSource,&winner_room_MusicBuffer) )
	{
		return false;
	}
	
	return true;
}

