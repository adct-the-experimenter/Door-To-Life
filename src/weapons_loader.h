#ifndef WEAPON_LOADER_H
#define WEAPON_LOADER_H

#include "sword.h" //for sword
#include "gun.h" //for gun
#include "bullet.h" //for bullet

//function to load media for all weapons and return a bool if it worked
bool loadWeaponsMedia(SDL_Renderer* gRenderer);
//function to free media for all weapons if loaded successfully
void freeWeaponsMedia();


// Sword

//Texture for sword sprite sheet
extern LTexture sword_sprite_sheet_tex;
//vector of walking clips for sword
extern std::vector <SDL_Rect> sword_walk_clips;

//function to load media for sword
bool loadMedia_Sword(SDL_Renderer* gRenderer);
//function to free sword media
void freeMedia_Sword();


//Gun

//Texture for sword sprite sheet
extern LTexture gun_sprite_sheet_tex;
//vector of walking clips for sword
extern std::vector <SDL_Rect> gun_walk_clips;

//function to load media for sword
bool loadMedia_Gun(SDL_Renderer* gRenderer);
//function to free sword media
void freeMedia_Gun();

//Bullet

//Texture for bullet sprite sheet
extern LTexture bullet_sprite_sheet_tex;
//vector of direction clips for bullet animation
extern std::vector <SDL_Rect> bullet_direction_clips;

//function to load media for bullet
bool loadMedia_Bullet(SDL_Renderer* gRenderer);


#endif
