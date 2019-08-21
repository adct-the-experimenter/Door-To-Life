#include "frame_rate_cap.h"

 //constrcutor
FrameRateCap::FrameRateCap()
{
    //initialize counted frames
    countedFrames = 0;
    
    //Set text color as black 
    textColor = { 0, 0, 0, 255 };
}

//destructor
FrameRateCap::~FrameRateCap()
{
    
}

//function to set frame rate
void FrameRateCap::setFrameRate(std::int16_t& frame_rate)
{
    /*This piece of code was originally from Lazy Foo' Productions
(http://lazyfoo.net/)*/
    SCREEN_FPS = frame_rate;
    SCREEN_TICKS_PER_FRAME = 1000 / frame_rate;
}

//function to start frame count
void FrameRateCap::startFrameCount()
{
    /*This piece of code was originally from Lazy Foo' Productions
(http://lazyfoo.net/)*/
    //Start counting frames per second 
    countedFrames = 0; 
    fpsTimer.start();
}

//function to start cap timer
void FrameRateCap::startCapTimer()
{
    /*This piece of code was originally from Lazy Foo' Productions
(http://lazyfoo.net/)*/
     //Start cap 
     capTimer.start();
}

//function to calculate and correct fps
void FrameRateCap::calculateFPS()
{
    /*This piece of code was originally from Lazy Foo' Productions
(http://lazyfoo.net/)*/
     //Calculate and correct fps 
     float fps = FrameRateCap::getCountedFrames() / ( fpsTimer.getTicks() / 1000.f ); 
     if( fps > 2000000 ) { fps = 0; FrameRateCap::setAVGFPS(fps); }
     else{ FrameRateCap::setAVGFPS(fps);}
}

void FrameRateCap::setAVGFPS(float& thisNum){avgFPS = thisNum;}
float FrameRateCap::getAVGFPS(){return avgFPS;}

//function to increment frame counted
void FrameRateCap::countFrame()
{
    //increment frame
    FrameRateCap::incrementCountedFrames();
}

//function to delay FPS to keep it constant if needed
void FrameRateCap::delayForEarlyFrameFinish()
{
    /*This piece of code was originally from Lazy Foo' Productions
(http://lazyfoo.net/)*/
    //If frame finished early 
    int frameTicks = capTimer.getTicks(); 
    if( frameTicks < SCREEN_TICKS_PER_FRAME ) 
    { 
        //Wait remaining time 
        SDL_Delay( SCREEN_TICKS_PER_FRAME - frameTicks ); 
    }
}

 //function to render frame rate
void FrameRateCap::renderFrameRate(std::int16_t& x, std::int16_t& y,
                                    TTF_Font* gFont, SDL_Renderer* gRenderer)
{
    /*This piece of code was originally from Lazy Foo' Productions
(http://lazyfoo.net/)*/
    //Set text to be rendered 
    timeText.str( "" ); timeText << "FPS(Cap) " << FrameRateCap::getAVGFPS(); 
    //Render text 
    if( !fpsTexture.loadFromRenderedText( timeText.str().c_str(), textColor,gFont,gRenderer ) ) 
    { printf( "Unable to render FPS texture!\n" ); }
    else
    {
        //Render textures 
        fpsTexture.render( x - fpsTexture.getWidth(), 
                            y - fpsTexture.getHeight(),
                            gRenderer);
    }
}

void FrameRateCap::incrementCountedFrames(){++countedFrames;}

std::int32_t FrameRateCap::getCountedFrames(){return countedFrames;}

//function to return pointer to fps timer
LTimer* FrameRateCap::getFPSTimer(){return &fpsTimer;}