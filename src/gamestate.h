#ifndef GAMESTATE_H
#define GAMESTATE_H



#include <string>
#include "LTexture.h"

//#include "globalvariables.h"
#include <cstdint>

#include <vector>

#include "globalvariables.h"

#include "event_handler.h"

#include <cmath>

//Base class for game state
class GameState
{
    public:

        GameState();
        virtual ~GameState(){};


//State
        enum class State : std::int8_t {RUNNING = 0,EXIT,NEXT,PAUSE,GAME_OVER};

        virtual void setState(GameState::State thisState);
        virtual GameState::State getState();

		
        //Game loop functions
        virtual void handle_events(Event& thisEvent) = 0;
        virtual void handle_events_RNG(RNGType& rngSeed) = 0;
        virtual void logic() = 0;
        virtual void sound() = 0;
        virtual void render(SDL_Renderer* gRenderer) = 0;
		
      

		

    private:

        GameState::State mainState;

};

#endif // GAMESTATE_H
//GameState base class
