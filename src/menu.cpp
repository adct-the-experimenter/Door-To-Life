#include "menu.h"

Menu::Menu()
{
    Menu::setKeyPress(Menu::KeyPress::K_NONE);
    Menu::pushState(Menu::MenuState::NOT_RUNNING);
    Menu::resetKeyFocusPosition();
}

Menu::~Menu()
{
    //std::cout << "Menu destructor called! \n";

    Menu::setKeyPress(Menu::KeyPress::K_NONE);
    menuImage.free();
    while(!state_stack.empty()){Menu::popState();}
    Menu::resetKeyFocusPosition();

}

void Menu::setState(GameState::State thisState){GameState::setState(thisState);}

GameState::State Menu::getState(){return GameState::getState();}

bool Menu::loadMedia(SDL_Renderer *gRenderer,SDL_Window* gWindow)
{
    bool success = true;

    /*
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
       /* std::vector <SDL_Rect> clips(4);
        clips[size_t(GraphicalButton::Clip::DEFAULT)] = {0,0,100,75};
        clips[size_t(GraphicalButton::Clip::FOCUS_OVER)] = {100,0,100,75};
        clips[size_t(GraphicalButton::Clip::BUTTON_DOWN)] = {0,75,100,75};
        clips[size_t(GraphicalButton::Clip::BUTTON_UP)] = {100,75,100,75};
        */
    //}
    
    
    return success;
}

void Menu::handle_events(Event& thisEvent)
{	
    
    switch(thisEvent)
    {
        case Event::ESCAPE:{Menu::setKeyPress(Menu::KeyPress::K_ESCAPE); break;}
        //case SDLK_n:{Menu::setKeyPress(Menu::KeyPress::K_NO); break;}
        //case SDLK_y:{Menu::setKeyPress(Menu::KeyPress::K_YES); break;}
        case Event::UP_ARROW:{Menu::setKeyPress(Menu::KeyPress::K_UP); break;}
        case Event::DOWN_ARROW:{Menu::setKeyPress(Menu::KeyPress::K_DOWN); break;}
        case Event::LEFT_ARROW:{Menu::setKeyPress(Menu::KeyPress::K_LEFT); break;}
        case Event::RIGHT_ARROW:{Menu::setKeyPress(Menu::KeyPress::K_RIGHT); break;}
        case Event::ENTER:{Menu::setKeyPress(Menu::KeyPress::K_ENTER); break;}
        default:{ Menu::setKeyPress(Menu::KeyPress::K_NONE); break;}
    }


}

void Menu::handle_events_RNG(RNGType& rngSeed){}

void Menu::logic()
{
    //reset key press
    Menu::setKeyPress(Menu::KeyPress::K_NONE);
    
}

void Menu::render(SDL_Renderer* gRenderer)
{
    
}


void Menu::sound()
{

}

void Menu::pushState(Menu::MenuState thisState){ state_stack.push(thisState);}

void Menu::popState(){state_stack.pop();}

Menu::MenuState Menu::getCurrentMenuState(){return state_stack.top();}

void Menu::setKeyPress(Menu::KeyPress press){mKeyPress = press;}
Menu::KeyPress Menu::getKeyPress(){return mKeyPress;}

void Menu::incrementKeyFocusPosition(){base_key_focus_position += 1;}
void Menu::decrementKeyFocusPosition(){base_key_focus_position -= 1;}
void Menu::resetKeyFocusPosition(){base_key_focus_position = 0;}
std::int8_t Menu::getKeyFocusPosition(){return base_key_focus_position;}
void Menu::setKeyFocusPosition(std::int8_t& position){base_key_focus_position = position;}