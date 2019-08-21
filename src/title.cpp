#include "title.h"

Title::Title()
{
    //initialize title menu state
    titleMenu.pushState(Menu::MenuState::DEFAULT_MENU);
}

Title::~Title()
{
    
}


//State
void Title::setState(GameState::State thisState){GameState::setState(thisState);}
GameState::State Title::getState(){return GameState::getState();}

bool Title::loadMedia(SDL_Renderer* gRenderer)
{
    return titleMenu.loadMedia(gRenderer);
}

//Game loop functions
void Title::handle_events(Event& thisEvent)
{
    titleMenu.handle_events(thisEvent);
}

void Title::handle_events_RNG(RNGType& rngSeed){}

void Title::logic()
{
    titleMenu.logic();
    
    if(titleMenu.getState() == GameState::State::NEXT)
    {
        //reset title menu game state to running
        titleMenu.setState(GameState::State::RUNNING);
        //set title game state to next
        Title::setState(GameState::State::NEXT);
    }
    else if(titleMenu.getState() == GameState::State::EXIT)
    {
        //reset title menu game state to running
        titleMenu.setState(GameState::State::RUNNING);
        //set title game state to exit
        Title::setState(GameState::State::EXIT);
    }
}

void Title::sound()
{
    titleMenu.sound();
}

void Title::render(SDL_Renderer* gRenderer)
{
    titleMenu.render(gRenderer);
}

TitleMenu::TitleOptions Title::getTitleMenuOptionSelect(){return titleMenu.getTitleOption();}