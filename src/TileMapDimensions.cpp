#include "TileMapDimensions.h"

//floor tiles
SDL_Rect redTile = {0,0,80,80}; 
SDL_Rect greenTile = {0,80,80,80}; 
SDL_Rect blueTile = {0,160,80,80}; 

//hole tile
SDL_Rect centerHoleTile = {160,80,80,80}; 

//Wall tiles

SDL_Rect topLeftTile = {80,0,80,80};
SDL_Rect leftTile = {80,80,80,80};
SDL_Rect bottomLeftTile = {80,160,80,80};

SDL_Rect topTile = {160,0,80,80};
SDL_Rect topRightTile = {240,0,80,80};

SDL_Rect bottomTile = {160,160,80,80};
SDL_Rect bottomRightTile = {240,160,80,80};

SDL_Rect rightTile = {240,80,80,80};

//exit tile
SDL_Rect exitTile = {320,0,82,83};
  
//invisible wall tile
SDL_Rect invisibleWallTile = {321,80,80,80};