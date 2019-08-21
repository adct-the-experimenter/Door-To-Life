#include "submap.h"

SubMap::SubMap()
{
    mapViewPort = {0,0,100,100};
    
    dot_rect = {0,0,5,5};
    
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
}

void SubMap::setPosition(std::int16_t x, std::int16_t y)
{
    mapViewPort.x = x; mapViewPort.y = y;
}

void SubMap::renderSubMapAndDot(Dot* thisDot, SDL_Renderer* gRenderer)
{
    SDL_RenderSetViewport( gRenderer, &mapViewPort );
//    std::int16_t xColDot = thisDot->getCollisionBox().x / NODE_LEVEL_WIDTH;
//    std::int16_t yRowDot = thisDot->getCollisionBox().y / NODE_LEVEL_HEIGHT;
    
    
    //render gray square
    SDL_SetRenderDrawColor(gRenderer,
                           gray_r,gray_g,gray_b,
                           50);
                           
    SDL_RenderFillRect(gRenderer,&mapViewPort);
   
    //render dot over gray square
    SDL_SetRenderDrawColor(gRenderer,
                           200,0,0,
                           50);
    
    // dot_pixel_x * (mini map width / labyrinth map grid width)
    
    double mini_width_per_map_width = double( mapViewPort.w) / double( (GRID_WIDTH / 20) * NODE_LEVEL_WIDTH ) ;
    double mini_height_per_map_height = double( mapViewPort.h ) / double( (GRID_HEIGHT / 20) * NODE_LEVEL_HEIGHT );
    
    double dotMapX = thisDot->getCollisionBox().x * mini_width_per_map_width;
                    
    double dotMapY = thisDot->getCollisionBox().y * mini_height_per_map_height;
                    
    
    //convert from grid node position to square position 
    dot_rect.x = dotMapX;
    dot_rect.y = dotMapY;
    
    SDL_RenderDrawRect(gRenderer,&dot_rect);
    
    SDL_SetRenderDrawColor(gRenderer,
                           gray_r,gray_g,gray_b,
                           50);
    
    SDL_RenderSetViewport( gRenderer, NULL );
}