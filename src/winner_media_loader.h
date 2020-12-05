#include "WinnerDecisionRoom.h"

bool loadWinnerRoom_Media(SDL_Renderer* gRenderer);
void freeWinnerRoom_Media();

bool setupLoad_WinnerRoomMedia(SDL_Renderer* gRenderer);

//friend functions from winner decision room classs

bool loadWinnerDecisionRoomMedia(SDL_Renderer* gRenderer,LTexture* tileMap,
											LTexture* wnjudge1_texture,LTexture* wnjudge2_texture,LTexture* wnjudge3_texture,LTexture* wnjudge4_texture,
											ALuint* source,ALuint* buffer);
											
void freeWinnerDecisionRoomMedia(LTexture* tileMap,
									LTexture* wnjudge1_texture,LTexture* wnjudge2_texture,LTexture* wnjudge3_texture,LTexture* wnjudge4_texture,
									ALuint* source,ALuint* buffer);
									
extern ALuint winner_room_MusicSource;
extern ALuint winner_room_MusicBuffer;
extern LTexture winner_room_TilesTexture;

extern LTexture winner_judge1_texture;
extern LTexture winner_judge2_texture;
extern LTexture winner_judge3_texture;
extern LTexture winner_judge4_texture;
