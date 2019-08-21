#include "collisionobject.h"

bool checkCollision(SDL_Rect& a, SDL_Rect& b)
{
   
    //The sides of the rectangles
    std::int16_t leftA, leftB;
    std::int16_t rightA, rightB;
    std::int16_t topA; std::int16_t topB;
    std::int16_t bottomA; std::int16_t bottomB;

    //Calculate the sides of rect A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    //Calculate the sides of rect B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    //If any of the sides from A are outside of B
    if( bottomA <= topB )
    {
        return false;
    }

    if( topA >= bottomB )
    {
        return false;
    }

    if( rightA <= leftB )
    {
        return false;
    }

    if( leftA >= rightB )
    {
        return false;
    }

    //If none of the sides from A are outside B
    return true;
}
