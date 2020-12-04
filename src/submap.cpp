#include "submap.h"

SubMap::SubMap()
{
    mapViewPort = {0,0,100,100};
    
    dot_rect1 = {0,0,5,5};
    dot_rect2 = {0,0,5,5};
    dot_rect3 = {0,0,5,5};
    dot_rect4 = {0,0,5,5};
    
    gray_r = 128; 
    gray_g = 128; 
    gray_b = 128;
}

SubMap::~SubMap()
{
    
}

void SubMap::initParametersFromLabyrinth(Labyrinth& thisLabyrinth)
{
    //Grid Dimensions from node generator and maze generator
    GRID_X = thisLabyrinth.GRID_X;
    GRID_Y = thisLabyrinth.GRID_Y;
    GRID_WIDTH = thisLabyrinth.GRID_WIDTH;
    GRID_HEIGHT = thisLabyrinth.GRID_HEIGHT;
    
    //dimensions of nodes in grid
    NODE_LEVEL_WIDTH = thisLabyrinth.NODE_LEVEL_WIDTH;
    NODE_LEVEL_HEIGHT = thisLabyrinth.NODE_LEVEL_HEIGHT;
    
    TILE_WIDTH = thisLabyrinth.TILE_WIDTH;
    TILE_HEIGHT = thisLabyrinth.TILE_HEIGHT;
    
    // dot_pixel_x * (mini map width / labyrinth map grid width)
    
    mini_width_per_map_width = double( mapViewPort.w) / double( (GRID_WIDTH / 20) * NODE_LEVEL_WIDTH ) ;
    mini_height_per_map_height = double( mapViewPort.h ) / double( (GRID_HEIGHT / 20) * NODE_LEVEL_HEIGHT );
    
    //set dungeon entrance(s)
    dungeon_entraces_vec.resize(thisLabyrinth.getNumberOfDungeonEntranceLocations());
    
    for(size_t i = 0; i < dungeon_entraces_vec.size(); i++)
    {
		int x,y;
		thisLabyrinth.getDungeonEntranceLocationForThisIndex(i,&x,&y);
		
		double dotMapX = x * mini_width_per_map_width;
                    
		double dotMapY = y * mini_height_per_map_height;
		
		SDL_Rect thisRect;
		thisRect.x = dotMapX; thisRect.y = dotMapY;
		thisRect.w = 5; thisRect.h = 5;
		
		dungeon_entraces_vec[i] = thisRect;
	}
	
	//set exit tile rect
	int x,y;
	
	thisLabyrinth.GetExitTileLocation(&x,&y);
	
	exit_tile_rect.x = x * mini_width_per_map_width - (exit_tile_rect.w / 2);
	exit_tile_rect.y = y * mini_height_per_map_height - (exit_tile_rect.h / 2);
	exit_tile_rect.w = 15; exit_tile_rect.h = 15;
}

void SubMap::setPosition(std::int16_t x, std::int16_t y)
{
    mapViewPort.x = x; mapViewPort.y = y;
}

void SubMap::renderSubMapAndDot(Dot* thisDot1, Dot* thisDot2, Dot* thisDot3, Dot* thisDot4, SDL_Renderer* gRenderer)
{
    SDL_RenderSetViewport( gRenderer, &mapViewPort );
    
    
    //render gray square
    SDL_SetRenderDrawColor(gRenderer,
                           gray_r,gray_g,gray_b,
                           50);
                           
    SDL_RenderFillRect(gRenderer,NULL);
   
    //render red dot over gray square
    SDL_SetRenderDrawColor(gRenderer,
                           200,0,0,
                           50);
    
    
    
    if(thisDot1)
    {
		double dotMapX1 = thisDot1->getCollisionBox().x * mini_width_per_map_width;
                    
		double dotMapY1 = thisDot1->getCollisionBox().y * mini_height_per_map_height;
		
		//convert from grid node position to square position 
		dot_rect1.x = dotMapX1;
		dot_rect1.y = dotMapY1;
		
		SDL_RenderDrawRect(gRenderer,&dot_rect1);
	}
    
    
    if(thisDot2)
    {
		double dotMapX2 = thisDot2->getCollisionBox().x * mini_width_per_map_width;
                    
		double dotMapY2 = thisDot2->getCollisionBox().y * mini_height_per_map_height;
		
		dot_rect2.x = dotMapX2;
		dot_rect2.y = dotMapY2;
		
		SDL_RenderDrawRect(gRenderer,&dot_rect2);
		
	}
	
	if(thisDot3)
    {
		double dotMapX3 = thisDot3->getCollisionBox().x * mini_width_per_map_width;
                    
		double dotMapY3 = thisDot3->getCollisionBox().y * mini_height_per_map_height;
		
		dot_rect3.x = dotMapX3;
		dot_rect3.y = dotMapY3;
		
		SDL_RenderDrawRect(gRenderer,&dot_rect3);
		
	}
	
	if(thisDot4)
    {
		double dotMapX4 = thisDot4->getCollisionBox().x * mini_width_per_map_width;
                    
		double dotMapY4 = thisDot4->getCollisionBox().y * mini_height_per_map_height;
		
		dot_rect4.x = dotMapX4;
		dot_rect4.y = dotMapY4;
		
		SDL_RenderDrawRect(gRenderer,&dot_rect4);
		
	}
	
	//render blue dot over gray square
    SDL_SetRenderDrawColor(gRenderer,
                           0,0,200,
                           50);
    
    //for all mini dungeon entrances in labyrinth
    for(size_t i = 0; i < dungeon_entraces_vec.size(); i++)
    {
		//render a rectangle
		SDL_RenderDrawRect(gRenderer,&dungeon_entraces_vec[i]);
	}
	
	//render yellow rectangle for exit tile area
    SDL_SetRenderDrawColor(gRenderer,
                           204,204,0,
                           50);
    //render a rectangle
	SDL_RenderDrawRect(gRenderer,&exit_tile_rect);
    
    SDL_SetRenderDrawColor(gRenderer,
                           gray_r,gray_g,gray_b,
                           50);
    
    SDL_RenderSetViewport( gRenderer, NULL );
}

