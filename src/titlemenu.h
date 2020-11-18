#ifndef TITLEMENU_H
#define TITLEMENU_H

#include "menu.h"

class TitleMenu : public Menu
{

public:
    TitleMenu();
    virtual ~TitleMenu();
    
     //state
    void setState(GameState::State thisState);
    GameState::State getState();

    //Menu State
    virtual void pushState(Menu::MenuState thisState);
    virtual void popState();
    Menu::MenuState getCurrentMenuState();

    //Game loop functions
    virtual void handle_events(Event& thisEvent);
    virtual void handle_events_RNG(RNGType& rngSeed);
    virtual void logic();
    virtual void sound(AudioRenderer* gAudioRenderer);
    virtual void render(SDL_Renderer* gRenderer);
	virtual void render(DrawingManager* gDrawManager);
	
    bool loadMedia(SDL_Renderer* gRenderer);

    //Key presses
    virtual void setKeyPress(Menu::KeyPress press);
    virtual Menu::KeyPress getKeyPress();
    
    //key focus position functions
    virtual std::int8_t getKeyFocusPosition();
    virtual void incrementKeyFocusPosition();
    virtual void decrementKeyFocusPosition();
    virtual void resetKeyFocusPosition();
    virtual void setKeyFocusPosition(std::int8_t& position);
                        
    //game loop functions for menu states
    //will be overriden by derived classes
    //default menu
    virtual void defaultMenu_handleEvents(SDL_Event& event);
    virtual void defaultMenu_logic();
    virtual void defaultMenu_sound();
    virtual void defaultMenu_render(SDL_Renderer* gRenderer);
    //quit prompt
    virtual void quitPrompt_handleEvents(SDL_Event& event);
    virtual void quitPrompt_logic();
    virtual void quitPrompt_sound();
    virtual void quitPrompt_render(SDL_Renderer* gRenderer);
    //options menu
    virtual void options_handleEvents(SDL_Event& event);
    virtual void options_logic();
    virtual void options_sound();
    virtual void options_render(SDL_Renderer* gRenderer);
    
    
    std::int8_t TitleMenuOptionsMax = 6;
    enum class TitleOptions : std::int8_t{ PLAY_GAME_SINGLE = 0, 
										   PLAY_GAME_2_PLAYER,PLAY_GAME_3_PLAYER,PLAY_GAME_4_PLAYER,
										   EXIT, NODE_GEN_DEBUG};
    
    TitleMenu::TitleOptions getTitleOption();
    
private:
    LTexture titleImage;
    
    //default menu members
    GraphicalButton exitButton;
    GraphicalButton playGameButton_1; //single player
    GraphicalButton playGameButton_2; //2 player
    GraphicalButton playGameButton_3; //3 player
    GraphicalButton playGameButton_4; //4 player
    
    
    TitleMenu::TitleOptions title_options; 
};

#endif
