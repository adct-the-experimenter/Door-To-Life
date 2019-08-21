#ifndef GRAPHICALBUTTON_H
#define GRAPHICALBUTTON_H

#include "LTexture.h"
#include <cstdint>
#include <vector>

class GraphicalButton
{
public:
    GraphicalButton();
    ~GraphicalButton();

    //function to set position of button
    void setPosition(std::int16_t x,std::int16_t y);

    //function to load texture,sound,etc.
    bool loadMedia(std::string filePath,std::vector <SDL_Rect> &clips, SDL_Renderer* gRenderer);

    //game loop functions
    void handle_events(SDL_Event& event);
    void logic();
    void render(SDL_Renderer* gRenderer);
    void sound();

    enum class State : std::int8_t {MOUSE_OUTSIDE_BUTTON = 0, MOUSE_OVER_BUTTON,
                                    KEY_FOCUS_ON_BUTTON, KEY_FOCUS_OFF_BUTTON,
                                    BUTTON_DOWN,BUTTON_UP};
    void setButtonState(State thisState);
    State getButtonState();

    enum class Clip : std::int8_t {DEFAULT = 0,FOCUS_OVER,BUTTON_DOWN,BUTTON_UP};

private:

    std::int16_t positionX;
    std::int16_t positionY;

    LTexture buttonTexture;
    std::vector <SDL_Rect> buttonClips;
    State buttonState;
    
    //function to handle event for mouse input
    void handleEvent_MouseInput(SDL_Event& event);
};

#endif // GraphicalButton_H
