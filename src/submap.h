#ifndef SUB_MAP
#define SUB_MAP

#include "globalvariables.h"
#include "labyrinth.h"

class SubMap
{
public:
    SubMap();
    ~SubMap();
    
    //function to initialize values from a labyrinth object
    void initParametersFromLabyrinth(Labyrinth& thisLabyrinth);
    
    //function to set position of submap
    void setPosition(std::int16_t x, std::int16_t y);
    
    //function to render dot in sub map
    void renderSubMapAndDot(Dot* thisDot1, Dot* thisDot2, Dot* thisDot3, Dot* thisDot4, SDL_Renderer* gRenderer);

    std::int8_t mapSquareDivision = 10;
private:

     //Grid Dimensions from node generator and maze generator
    std::int16_t GRID_X;
    std::int16_t GRID_Y;
    std::int16_t GRID_WIDTH;
    std::int16_t GRID_HEIGHT;
    
    
    //dimensions of nodes in grid
    std::int16_t NODE_LEVEL_WIDTH;
    std::int16_t NODE_LEVEL_HEIGHT;
    
    std::int16_t TILE_WIDTH;
    std::int16_t TILE_HEIGHT;
    
    SDL_Rect mapViewPort;
    
    //gray square
    unsigned int gray_r; unsigned int gray_g; unsigned int gray_b;
    
    SDL_Rect dot_rect1;
    SDL_Rect dot_rect2;
    SDL_Rect dot_rect3;
    SDL_Rect dot_rect4;
    
};

#endif
