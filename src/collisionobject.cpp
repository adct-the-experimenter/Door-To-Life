#include "collisionobject.h"

bool checkCollision(SDL_Rect& a, SDL_Rect& b)
{
	if(a.y)
	{
		std::int32_t bottomA = a.y + a.h;
		std::int32_t topB = b.y; 
		//If any of the sides from A are outside of B
		if( bottomA <= topB )
		{
			return false;
		}
		
		std::int32_t topA = a.y;
		std::int32_t bottomB = b.y + b.h;
		if( topA >= bottomB )
		{
			return false;
		}
		
		std::int32_t rightA = a.x + a.w;
		std::int32_t leftB = b.x;
		if( rightA <= leftB )
		{
			return false;
		}
		
		std::int32_t leftA = a.x;
		std::int32_t rightB = b.x + b.w; 
		if( leftA >= rightB )
		{
			return false;
		}

		//If none of the sides from A are outside B
		return true;
		
	}
	
    return false;
}
