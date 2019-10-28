#ifndef TITLE_H
#define TITLE_H

#include "gamestate.h"
#include "titlemenu.h"

class Title : public GameState
{
public:

    Title();
    virtual ~Title();


//State

    virtual void setState(GameState::State thisState);
    virtual GameState::State getState();

    bool loadMedia(SDL_Renderer* gRenderer);
    
    //Game loop functions
    virtual void handle_events(Event& thisEvent);
    virtual void handle_events_RNG(RNGType& rngSeed);
    virtual void logic();
    virtual void sound(AudioRenderer* gAudioRenderer);
    virtual void render(SDL_Renderer* gRenderer);
    
    TitleMenu::TitleOptions getTitleMenuOptionSelect();
		
private:
    TitleMenu titleMenu;
};

#endif
