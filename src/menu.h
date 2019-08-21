#ifndef MENU_H
#define MENU_H


#include "gamestate.h"
#include "globalvariables.h"
#include <iostream>
#include <sstream> //header for string stream processing
#include <stack> //header for state stack

#include "graphicalbutton.h"

class Menu : public GameState
{
public:

        Menu();
        virtual ~Menu();

        //state
        void setState(GameState::State thisState);
        GameState::State getState();

        //Menu State
        enum class MenuState : std::int8_t {NOT_RUNNING = 0,DEFAULT_MENU,OPTIONS,QUIT_PROMPT,QUIT};

        virtual void pushState(Menu::MenuState thisState);
        virtual void popState();
        Menu::MenuState getCurrentMenuState();

        //Game loop functions
        virtual void handle_events(Event& thisEvent);
        virtual void handle_events_RNG(RNGType& rngSeed);
        virtual void logic();
        virtual void sound();
        virtual void render(SDL_Renderer* gRenderer);

        bool loadMedia(SDL_Renderer* gRenderer, SDL_Window *gWindow);

        //Key presses
        enum class KeyPress : std::int8_t {K_NONE = 0,
                                            //direction keys
                                            K_UP, K_DOWN, K_LEFT, K_RIGHT,
                                            //action keys
                                            K_ENTER,K_ESCAPE,K_YES,K_NO,K_QUIT};
        
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
        virtual void defaultMenu_handleEvents(SDL_Event& event) = 0;
        virtual void defaultMenu_logic() = 0;
        virtual void defaultMenu_sound() = 0;
        virtual void defaultMenu_render(SDL_Renderer* gRenderer) = 0;
        //quit prompt
        virtual void quitPrompt_handleEvents(SDL_Event& event) = 0;
        virtual void quitPrompt_logic() = 0;
        virtual void quitPrompt_sound() = 0;
        virtual void quitPrompt_render(SDL_Renderer* gRenderer) = 0;
        //options menu
        virtual void options_handleEvents(SDL_Event& event) = 0;
        virtual void options_logic() = 0;
        virtual void options_sound() = 0;
        virtual void options_render(SDL_Renderer* gRenderer) = 0;
        
private:
        Menu::KeyPress mKeyPress;
    //state stack
        std::stack <Menu::MenuState> state_stack;

        LTexture menuImage;

        //variable to increment or decrement for use of knowing what to focus on in menu
        //EX: Pressing down will increment position and will highlight next option in menu
        std::int8_t base_key_focus_position;
       
};

#endif
