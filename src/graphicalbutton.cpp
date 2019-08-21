#include "graphicalbutton.h"

GraphicalButton::GraphicalButton()
{
    GraphicalButton::setButtonState(State::MOUSE_OUTSIDE_BUTTON);
}

GraphicalButton::~GraphicalButton()
{
    GraphicalButton::setButtonState(State::MOUSE_OUTSIDE_BUTTON);
    buttonTexture.free();
}

void GraphicalButton::setPosition(std::int16_t x, std::int16_t y){positionX = x; positionY = y;}


//function to load texture,sound,etc.
bool GraphicalButton::loadMedia(std::string filePath, std::vector<SDL_Rect> &clips, SDL_Renderer* gRenderer)
{
    
    bool success = true;

    if(!buttonTexture.loadFromFile(filePath,gRenderer))
    {
        std::cout << "Failed to load button texture! \n";
        success = false;
    }
    else
    {
        buttonClips = clips;
    }

    return success;
}

//game loop functions
void GraphicalButton::handle_events(SDL_Event& event)
{
    
    //GraphicalButton::handleEvent_MouseInput(event);
    

}

void GraphicalButton::handleEvent_MouseInput(SDL_Event& event)
{
    /*This piece of code was originally from Lazy Foo' Productions
(http://lazyfoo.net/)*/
    if(event.type == SDL_MOUSEMOTION || event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP)
    {
        int x,y;
        SDL_GetMouseState(&x,&y);

        //check if mouse is within button bounds
        if(x > positionX && x < positionX + buttonClips[size_t(Clip::DEFAULT)].w
                && y > positionY && y < positionY + buttonClips[size_t(Clip::DEFAULT)].h)
        {
            GraphicalButton::setButtonState(State::MOUSE_OVER_BUTTON);
        }
        else{GraphicalButton::setButtonState(State::MOUSE_OUTSIDE_BUTTON);}

        //if mouse is over the button
        if(GraphicalButton::getButtonState() == State::MOUSE_OVER_BUTTON)
        {
            switch(event.type)
            {
                case SDL_MOUSEMOTION:{ GraphicalButton::setButtonState(State::MOUSE_OVER_BUTTON); break;}
                case SDL_MOUSEBUTTONDOWN:{ GraphicalButton::setButtonState(State::BUTTON_DOWN); break;}
                case SDL_MOUSEBUTTONUP:{GraphicalButton::setButtonState(State::BUTTON_UP); break;}
            }
        }
    }
}

void GraphicalButton::logic()
{

}

void GraphicalButton::render(SDL_Renderer* gRenderer)
{
    switch(GraphicalButton::getButtonState())
    {
        case State::MOUSE_OUTSIDE_BUTTON:{ buttonTexture.render(positionX,positionY,gRenderer,&buttonClips[size_t(Clip::DEFAULT)]); break; }
        case State::MOUSE_OVER_BUTTON:{ buttonTexture.render(positionX,positionY,gRenderer,&buttonClips[size_t(Clip::FOCUS_OVER)]); break;}
        case State::KEY_FOCUS_OFF_BUTTON:{ buttonTexture.render(positionX,positionY,gRenderer,&buttonClips[size_t(Clip::DEFAULT)]); break; }
        case State::KEY_FOCUS_ON_BUTTON:{ buttonTexture.render(positionX,positionY,gRenderer,&buttonClips[size_t(Clip::FOCUS_OVER)]); break;}
        case State::BUTTON_DOWN:{buttonTexture.render(positionX,positionY,gRenderer,&buttonClips[size_t(Clip::BUTTON_DOWN)]); break;}
        case State::BUTTON_UP:{buttonTexture.render(positionX,positionY,gRenderer,&buttonClips[size_t(Clip::BUTTON_UP)]); break;}
    }
}

void GraphicalButton::sound()
{
    
}

void GraphicalButton::setButtonState(GraphicalButton::State thisState){ buttonState = thisState;}

GraphicalButton::State GraphicalButton::getButtonState(){return buttonState;}
