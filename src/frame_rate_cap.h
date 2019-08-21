#ifndef FRAME_RATE_CAP_H
#define FRAME_RATE_CAP_H

#include "LTexture.h"
#include "LTimer.h"
#include <cstdint>
#include <sstream>

class FrameRateCap
{
public:
    //constrcutor
    FrameRateCap();
    //destructor
    ~FrameRateCap();
    
    //function to set frame rate
    void setFrameRate(std::int16_t& frame_rate);
    
    //function to start frame count
    void startFrameCount();
    
    //function to start cap timer
    void startCapTimer();
    
    //function to calculate and correct fps
    void calculateFPS();
    
    //function to increment frame counted
    void countFrame();
    
    //function to delay FPS to keep it constant if needed
    void delayForEarlyFrameFinish();
    
    //function to render frame rate
    void renderFrameRate(std::int16_t& x, std::int16_t& y, TTF_Font* gFont, SDL_Renderer* gRenderer);
    
    //function to return pointer to fps timer
    LTimer* getFPSTimer();
    
private:
    std::int16_t SCREEN_FPS; 
    std::int16_t SCREEN_TICKS_PER_FRAME;
    
    //Timer to keep track of the frames pass per second
    LTimer fpsTimer;
    //Timer for limiting frames per second
    LTimer capTimer;
    
    //texture for showing frames per second
    LTexture fpsTexture;
    //In memory text stream 
    std::stringstream timeText;
    //Set text color as black 
    SDL_Color textColor;
    
    //Frame count
    std::int32_t countedFrames;
    void incrementCountedFrames();
    std::int32_t getCountedFrames();
    
    //Average FPS
    float avgFPS;
    void setAVGFPS(float& thisNum);
    float getAVGFPS();
};
#endif