#include "pause_menu.h"

PauseMenu::PauseMenu()
{
    PauseMenu::setKeyPress(Menu::KeyPress::K_NONE);
    PauseMenu::pushState(Menu::MenuState::NOT_RUNNING);
}

PauseMenu::~PauseMenu()
{
    //std::cout << "PauseMenu destructor called! \n";

    menuImage.free();

}

void PauseMenu::setState(GameState::State thisState){Menu::setState(thisState);}

GameState::State PauseMenu::getState(){return Menu::getState();}

bool PauseMenu::loadMedia(SDL_Renderer *gRenderer)
{
    bool success = true;

    
    std::string filePath = DATADIR_STR +  MENU_IMAGE_DIR_STR + std::string("menu.png");

    if(!menuImage.loadFromFile(filePath,gRenderer) )
    {
        std::cout << "Failed to load menu image! \n";
        success = false;
    }
    else
    {
        //load media for buttons
        //clips for buttons
        std::vector <SDL_Rect> clips(4);
        clips[size_t(GraphicalButton::Clip::DEFAULT)] = {0,0,100,75};
        clips[size_t(GraphicalButton::Clip::FOCUS_OVER)] = {100,0,100,75};
        clips[size_t(GraphicalButton::Clip::BUTTON_DOWN)] = {0,75,100,75};
        clips[size_t(GraphicalButton::Clip::BUTTON_UP)] = {100,75,100,75};
        
        //load quit button media
        std::string quitButtonFilePath = DATADIR_STR + BUTTONSDIR_STR + std::string("quit-button.png");
        if(!quitButton.loadMedia(quitButtonFilePath,clips,gRenderer))
        {
            std::cout << "Failed to load quit button media! \n";
            success = false;
        }
        else{quitButton.setPosition(320 - 150 ,240 - 100);}

        //load resume button media
        std::string resumeButtonFilePath = DATADIR_STR + BUTTONSDIR_STR + std::string("resume-button.png");
        if(!resumeButton.loadMedia(resumeButtonFilePath,clips,gRenderer))
        {
            std::cout << "Failed to load escape button media! \n";
            success = false;
        }
        else{resumeButton.setPosition(320 + 75 ,240 - 100);}

        
    }
    
    
    return success;
}

void PauseMenu::handle_events(Event& thisEvent)
{	
   Menu::handle_events(thisEvent);
}

void PauseMenu::handle_events_RNG(RNGType& rngSeed){}

void PauseMenu::logic()
{
    
    switch(PauseMenu::getCurrentMenuState())
    {
        case Menu::MenuState::NOT_RUNNING:{ break;}
        case Menu::MenuState::DEFAULT_MENU:{PauseMenu::defaultMenu_logic(); break;}
        case Menu::MenuState::OPTIONS:{PauseMenu::options_logic(); break;}
        case Menu::MenuState::QUIT_PROMPT:{PauseMenu::quitPrompt_logic(); break;}
        case Menu::MenuState::QUIT:{ break;}
    }
    //resets key press for now
    Menu::logic();
}

void PauseMenu::render(SDL_Renderer* gRenderer)
{
    //render menu background image first 
    menuImage.render(0,0,gRenderer);
    
    switch(PauseMenu::getCurrentMenuState())
    {
        case Menu::MenuState::NOT_RUNNING:{ break;}
        case Menu::MenuState::DEFAULT_MENU:{PauseMenu::defaultMenu_render(gRenderer); break;}
        case Menu::MenuState::OPTIONS:{PauseMenu::options_render(gRenderer); break;}
        case Menu::MenuState::QUIT_PROMPT:{PauseMenu::quitPrompt_render(gRenderer); break;}
        case Menu::MenuState::QUIT:{ break;}
    }
}


void PauseMenu::sound()
{
    switch(PauseMenu::getCurrentMenuState())
    {
        case Menu::MenuState::NOT_RUNNING:{ break;}
        case Menu::MenuState::DEFAULT_MENU:{PauseMenu::defaultMenu_sound(); break;}
        case Menu::MenuState::OPTIONS:{PauseMenu::options_sound(); break;}
        case Menu::MenuState::QUIT_PROMPT:{PauseMenu::quitPrompt_sound(); break;}
        case Menu::MenuState::QUIT:{ break;}
    }
}

void PauseMenu::pushState(Menu::MenuState thisState){ Menu::pushState(thisState);}

void PauseMenu::popState(){Menu::popState();}

Menu::MenuState PauseMenu::getCurrentMenuState(){return Menu::getCurrentMenuState();}

void PauseMenu::setKeyPress(Menu::KeyPress press){Menu::setKeyPress(press);}
Menu::KeyPress PauseMenu::getKeyPress(){return Menu::getKeyPress();}

void PauseMenu::incrementKeyFocusPosition(){Menu::incrementKeyFocusPosition();}
void PauseMenu::decrementKeyFocusPosition(){Menu::decrementKeyFocusPosition();}
void PauseMenu::resetKeyFocusPosition(){Menu::resetKeyFocusPosition();}
std::int8_t PauseMenu::getKeyFocusPosition(){return Menu::getKeyFocusPosition();}
void PauseMenu::setKeyFocusPosition(std::int8_t& position){Menu::setKeyFocusPosition(position);}

//default menu
void PauseMenu::defaultMenu_handleEvents(SDL_Event& event)
{
    
}

void PauseMenu::defaultMenu_logic()
{
    //if key is pressed
    switch(PauseMenu::getKeyPress() )
    {
        case Menu::KeyPress::K_LEFT:{ PauseMenu::decrementKeyFocusPosition(); break;}
        case Menu::KeyPress::K_RIGHT:{ PauseMenu::incrementKeyFocusPosition(); break;}
        case Menu::KeyPress::K_ENTER:
        {
            //if key focus is in position zero, push into quit state 
            if(PauseMenu::getKeyFocusPosition() == 0)
            {
                quitButton.setButtonState(GraphicalButton::State::BUTTON_DOWN);
                PauseMenu::pushState(Menu::MenuState::QUIT); 
            }
            //if key focus is in position one, pop into not running state to resume game
            else if(PauseMenu::getKeyFocusPosition() == 1)
            {
                resumeButton.setButtonState(GraphicalButton::State::BUTTON_DOWN);
                PauseMenu::popState();
            }
            break;
        }
    }
    
    //logic for graphical buttons
    
    //if at position 0, set quit button to key focus on button state
    if(PauseMenu::getKeyFocusPosition() == 0)
    {quitButton.setButtonState(GraphicalButton::State::KEY_FOCUS_ON_BUTTON);}
    else{quitButton.setButtonState(GraphicalButton::State::KEY_FOCUS_OFF_BUTTON);}
    
    if(PauseMenu::getKeyFocusPosition() == 1)
    {resumeButton.setButtonState(GraphicalButton::State::KEY_FOCUS_ON_BUTTON);}
    else{resumeButton.setButtonState(GraphicalButton::State::KEY_FOCUS_OFF_BUTTON);}
    
    
    //bounds checking for key focus position
    if(PauseMenu::getKeyFocusPosition() < 0){PauseMenu::resetKeyFocusPosition();}
    else if(PauseMenu::getKeyFocusPosition() > pauseMenuOptionsMax - 1)
    {
        std::int8_t max = pauseMenuOptionsMax - 1;
        PauseMenu::setKeyFocusPosition(max);
    }
}

void PauseMenu::defaultMenu_sound()
{
    
}

void PauseMenu::defaultMenu_render(SDL_Renderer* gRenderer)
{
    quitButton.render(gRenderer);
    resumeButton.render(gRenderer);
}

//quit prompt
void PauseMenu::quitPrompt_handleEvents(SDL_Event& event)
{
    
}

void PauseMenu::quitPrompt_logic()
{
    
}

void PauseMenu::quitPrompt_sound()
{
    
}

void PauseMenu::quitPrompt_render(SDL_Renderer* gRenderer)
{
    
}

//options menu
void PauseMenu::options_handleEvents(SDL_Event& event)
{
    
}

void PauseMenu::options_logic()
{
    
}

void PauseMenu::options_sound()
{
    
}

void PauseMenu::options_render(SDL_Renderer* gRenderer)
{
    
}