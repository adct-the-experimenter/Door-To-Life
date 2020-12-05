#include "titlemenu.h"


TitleMenu::TitleMenu()
{
    TitleMenu::setKeyPress(Menu::KeyPress::K_NONE);
    TitleMenu::pushState(Menu::MenuState::NOT_RUNNING);
}

TitleMenu::~TitleMenu()
{
    //std::cout << "TitleMenu destructor called! \n";
}

void TitleMenu::setState(GameState::State thisState){Menu::setState(thisState);}

GameState::State TitleMenu::getState(){return Menu::getState();}

bool TitleMenu::loadMedia(SDL_Renderer *gRenderer)
{
    bool success = true;

    
    std::string filePath = DATADIR_STR +  MENU_IMAGE_DIR_STR + std::string("title.png");

    if(!titleImage.loadFromFile(filePath,gRenderer) )
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
        
        //load exit button media
        std::string exitButtonFilePath = DATADIR_STR + BUTTONSDIR_STR + std::string("exit-button.png");
        if(!exitButton.loadMedia(exitButtonFilePath,clips,gRenderer))
        {
            std::cout << "Failed to load exit button media! \n";
            success = false;
        }
        else{exitButton.setPosition(50 ,400);}

        //load play 1 player game button media
        std::string playGameButtonFilePath = DATADIR_STR + BUTTONSDIR_STR + std::string("play-game-singleplayer-button.png");
        if(!playGameButton_1.loadMedia(playGameButtonFilePath,clips,gRenderer))
        {
            std::cout << "Failed to load play 1 game button media! \n";
            success = false;
        }
        else{playGameButton_1.setPosition(50 ,0);}
        
        //load play 2 player game button media
        playGameButtonFilePath = DATADIR_STR + BUTTONSDIR_STR + std::string("play-game-2player-button.png");
        if(!playGameButton_2.loadMedia(playGameButtonFilePath,clips,gRenderer))
        {
            std::cout << "Failed to load play 2 game button media! \n";
            success = false;
        }
        else{playGameButton_2.setPosition(50 ,100);}
        
        //load play 3 player game button media
        playGameButtonFilePath = DATADIR_STR + BUTTONSDIR_STR + std::string("play-game-3player-button.png");
        if(!playGameButton_3.loadMedia(playGameButtonFilePath,clips,gRenderer))
        {
            std::cout << "Failed to load play 3 game button media! \n";
            success = false;
        }
        else{playGameButton_3.setPosition(50 ,200);}
        
        //load play 4 player game button media
        playGameButtonFilePath = DATADIR_STR + BUTTONSDIR_STR + std::string("play-game-4player-button.png");
        if(!playGameButton_4.loadMedia(playGameButtonFilePath,clips,gRenderer))
        {
            std::cout << "Failed to load play 4 game button media! \n";
            success = false;
        }
        else{playGameButton_4.setPosition(50 ,300);}

        
    }
    
    
    return success;
}

void TitleMenu::handle_events(Event& thisEvent)
{	
   Menu::handle_events(thisEvent);
}

void TitleMenu::handle_events_RNG(RNGType& rngSeed){}

void TitleMenu::logic()
{
    
    switch(TitleMenu::getCurrentMenuState())
    {
        case Menu::MenuState::NOT_RUNNING:{ break;}
        case Menu::MenuState::DEFAULT_MENU:{TitleMenu::defaultMenu_logic(); break;}
        case Menu::MenuState::OPTIONS:{TitleMenu::options_logic(); break;}
        case Menu::MenuState::QUIT_PROMPT:{TitleMenu::quitPrompt_logic(); break;}
        case Menu::MenuState::QUIT:{ break;}
    }
    //resets key press for now
    Menu::logic();
}

void TitleMenu::render(SDL_Renderer* gRenderer)
{
    //render title background image first 
    titleImage.render(0,0,gRenderer);
    
    switch(TitleMenu::getCurrentMenuState())
    {
        case Menu::MenuState::NOT_RUNNING:{ break;}
        case Menu::MenuState::DEFAULT_MENU:{TitleMenu::defaultMenu_render(gRenderer); break;}
        case Menu::MenuState::OPTIONS:{TitleMenu::options_render(gRenderer); break;}
        case Menu::MenuState::QUIT_PROMPT:{TitleMenu::quitPrompt_render(gRenderer); break;}
        case Menu::MenuState::QUIT:{ break;}
    }
}

void TitleMenu::render(DrawingManager* gDrawManager)
{
	
}

void TitleMenu::sound(AudioRenderer* gAudioRenderer)
{
    switch(TitleMenu::getCurrentMenuState())
    {
        case Menu::MenuState::NOT_RUNNING:{ break;}
        case Menu::MenuState::DEFAULT_MENU:{TitleMenu::defaultMenu_sound(); break;}
        case Menu::MenuState::OPTIONS:{TitleMenu::options_sound(); break;}
        case Menu::MenuState::QUIT_PROMPT:{TitleMenu::quitPrompt_sound(); break;}
        case Menu::MenuState::QUIT:{ break;}
    }
}

void TitleMenu::pushState(Menu::MenuState thisState){ Menu::pushState(thisState);}

void TitleMenu::popState(){Menu::popState();}

Menu::MenuState TitleMenu::getCurrentMenuState(){return Menu::getCurrentMenuState();}

void TitleMenu::setKeyPress(Menu::KeyPress press){Menu::setKeyPress(press);}
Menu::KeyPress TitleMenu::getKeyPress(){return Menu::getKeyPress();}

void TitleMenu::incrementKeyFocusPosition(){Menu::incrementKeyFocusPosition();}
void TitleMenu::decrementKeyFocusPosition(){Menu::decrementKeyFocusPosition();}
void TitleMenu::resetKeyFocusPosition(){Menu::resetKeyFocusPosition();}
std::int8_t TitleMenu::getKeyFocusPosition(){return Menu::getKeyFocusPosition();}
void TitleMenu::setKeyFocusPosition(std::int8_t& position){Menu::setKeyFocusPosition(position);}

//default menu
void TitleMenu::defaultMenu_handleEvents(SDL_Event& event)
{
    
}

void TitleMenu::defaultMenu_logic()
{
    //if key is pressed
    switch(TitleMenu::getKeyPress() )
    {
        case Menu::KeyPress::K_UP:{ TitleMenu::decrementKeyFocusPosition(); break;}
        case Menu::KeyPress::K_DOWN:{ TitleMenu::incrementKeyFocusPosition(); break;}
        case Menu::KeyPress::K_ENTER:
        {
            //if key focus is in position zero, push into quit state 
            if(TitleMenu::getKeyFocusPosition() == (std::int8_t)TitleMenu::TitleOptions::EXIT)
            {
                exitButton.setButtonState(GraphicalButton::State::BUTTON_DOWN);
                TitleMenu::setState(GameState::State::EXIT);
                title_options = TitleMenu::TitleOptions::EXIT; 
            }
            //if key focus is in position one, pop into not running state to resume game
            else if(TitleMenu::getKeyFocusPosition() == 
            (std::int8_t)TitleMenu::TitleOptions::PLAY_GAME_SINGLE)
            {
                playGameButton_1.setButtonState(GraphicalButton::State::BUTTON_DOWN);
                TitleMenu::setState(GameState::State::NEXT);
                title_options = TitleMenu::TitleOptions::PLAY_GAME_SINGLE;
            }
            else if(TitleMenu::getKeyFocusPosition() == 
            (std::int8_t)TitleMenu::TitleOptions::PLAY_GAME_2_PLAYER)
            {
                playGameButton_2.setButtonState(GraphicalButton::State::BUTTON_DOWN);
                TitleMenu::setState(GameState::State::NEXT);
                title_options = TitleMenu::TitleOptions::PLAY_GAME_2_PLAYER;
            }
            else if(TitleMenu::getKeyFocusPosition() == 
            (std::int8_t)TitleMenu::TitleOptions::PLAY_GAME_3_PLAYER)
            {
                playGameButton_3.setButtonState(GraphicalButton::State::BUTTON_DOWN);
                TitleMenu::setState(GameState::State::NEXT);
                title_options = TitleMenu::TitleOptions::PLAY_GAME_3_PLAYER;
            }
            else if(TitleMenu::getKeyFocusPosition() == 
            (std::int8_t)TitleMenu::TitleOptions::PLAY_GAME_4_PLAYER)
            {
                playGameButton_4.setButtonState(GraphicalButton::State::BUTTON_DOWN);
                TitleMenu::setState(GameState::State::NEXT);
                title_options = TitleMenu::TitleOptions::PLAY_GAME_4_PLAYER;
            }
            else if(TitleMenu::getKeyFocusPosition() == 
            (std::int8_t)TitleMenu::TitleOptions::NODE_GEN_DEBUG)
            {
                TitleMenu::setState(GameState::State::NEXT);
                title_options = TitleMenu::TitleOptions::NODE_GEN_DEBUG;
            }
            break;
        }
        default:{ break;}
    }
    
    //logic for graphical buttons
    
    //if at position 0, set quit button to key focus on button state
    if(TitleMenu::getKeyFocusPosition() == (std::int8_t)TitleMenu::TitleOptions::EXIT)
    {exitButton.setButtonState(GraphicalButton::State::KEY_FOCUS_ON_BUTTON);}
    else{exitButton.setButtonState(GraphicalButton::State::KEY_FOCUS_OFF_BUTTON);}
    
    if(TitleMenu::getKeyFocusPosition() == (std::int8_t)TitleMenu::TitleOptions::PLAY_GAME_SINGLE)
    {playGameButton_1.setButtonState(GraphicalButton::State::KEY_FOCUS_ON_BUTTON);}
    else{playGameButton_1.setButtonState(GraphicalButton::State::KEY_FOCUS_OFF_BUTTON);}
    
    if(TitleMenu::getKeyFocusPosition() == (std::int8_t)TitleMenu::TitleOptions::PLAY_GAME_2_PLAYER)
    {playGameButton_2.setButtonState(GraphicalButton::State::KEY_FOCUS_ON_BUTTON);}
    else{playGameButton_2.setButtonState(GraphicalButton::State::KEY_FOCUS_OFF_BUTTON);}
    
    if(TitleMenu::getKeyFocusPosition() == (std::int8_t)TitleMenu::TitleOptions::PLAY_GAME_3_PLAYER)
    {playGameButton_3.setButtonState(GraphicalButton::State::KEY_FOCUS_ON_BUTTON);}
    else{playGameButton_3.setButtonState(GraphicalButton::State::KEY_FOCUS_OFF_BUTTON);}
    
    if(TitleMenu::getKeyFocusPosition() == (std::int8_t)TitleMenu::TitleOptions::PLAY_GAME_4_PLAYER)
    {playGameButton_4.setButtonState(GraphicalButton::State::KEY_FOCUS_ON_BUTTON);}
    else{playGameButton_4.setButtonState(GraphicalButton::State::KEY_FOCUS_OFF_BUTTON);}
    
    
    //bounds checking for key focus position
    if(TitleMenu::getKeyFocusPosition() < 0){TitleMenu::resetKeyFocusPosition();}
    else if(TitleMenu::getKeyFocusPosition() > TitleMenuOptionsMax - 1)
    {
        std::int8_t max = TitleMenuOptionsMax - 1;
        TitleMenu::setKeyFocusPosition(max);
    }
}

void TitleMenu::defaultMenu_sound()
{
    
}

void TitleMenu::defaultMenu_render(SDL_Renderer* gRenderer)
{
    exitButton.render(gRenderer);
    playGameButton_1.render(gRenderer);
    playGameButton_2.render(gRenderer);
    playGameButton_3.render(gRenderer);
    playGameButton_4.render(gRenderer);
}

//quit prompt
void TitleMenu::quitPrompt_handleEvents(SDL_Event& event)
{
    
}

void TitleMenu::quitPrompt_logic()
{
    
}

void TitleMenu::quitPrompt_sound()
{
    
}

void TitleMenu::quitPrompt_render(SDL_Renderer* gRenderer)
{
    
}

//options menu
void TitleMenu::options_handleEvents(SDL_Event& event)
{
    
}

void TitleMenu::options_logic()
{
    
}

void TitleMenu::options_sound()
{
    
}

void TitleMenu::options_render(SDL_Renderer* gRenderer)
{
    
}

TitleMenu::TitleOptions TitleMenu::getTitleOption(){return title_options;}
