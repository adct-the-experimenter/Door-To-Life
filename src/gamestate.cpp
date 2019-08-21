#include "gamestate.h"

GameState::GameState()
{
    //Initialize state to running 
    GameState::setState(GameState::State::RUNNING);
}

void GameState::setState(GameState::State thisState){mainState = thisState;}

GameState::State GameState::getState(){return mainState;}

