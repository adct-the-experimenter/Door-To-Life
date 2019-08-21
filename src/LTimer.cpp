#include "LTimer.h"

/*This wrapper class code was originally from Lazy Foo' Productions
(http://lazyfoo.net/)*/

LTimer::LTimer()
{
    //Initialize variables
    mStartTicks = 0; mPausedTicks = 0;
    mPaused = false; mStarted = false;
}

void LTimer::start()
{
    mStarted = true; //timer started
    mPaused = false; //tiemr is not paused

    //get current clocktime
    mStartTicks = SDL_GetTicks();
    mPausedTicks = 0;
}

void LTimer::stop()
{
    mStarted = false; //stop the timer
    mPaused = false; //unpause the timer

    //clear tick variables
    mStartTicks =0;
    mPausedTicks = 0;
}

void LTimer::pause()
{
    //if timeris running an isn't already paused
    if(mStarted && !mPaused) //mStarted = true and mPaused = false
    {
        //pause the timer
        mPaused = true;
        //Calculate paused ticks
        mPausedTicks -= SDL_GetTicks() - mStartTicks;
        mStartTicks= 0;
    }
}

void LTimer::unpause()
{
    //if timer is running and paused
    if(mStarted && mPaused) //mstarted = true mPaused=true
    {
        //unpause timer
        mPaused = false;
        //Reset starting ticks
        mStartTicks = SDL_GetTicks() - mPausedTicks;
        //reset paused ticks
        mPausedTicks=0;
    }
}

Uint32 LTimer::getTicks()
{
    Uint32 time = 0; //actual timer time
    //if timer is running
    if(mStarted) //mStarted = true
    {
        //if timer is paused
        if(mPaused) //mPaused = true
        {
            //Return number of tickswhen timer was paused
            time = mPausedTicks;
        }
        else //timer is running and not paused
        {
            //return current time minus start time for actual relative time
            time = SDL_GetTicks() - mStartTicks;
        }
    }
    return time;
}

bool LTimer::isStarted()
{
    //Timer is running and paused or unpaused
    return mStarted;
}

bool LTimer::isPaused()
{
    //Timer is running and paused
    return mPaused && mStarted;
}
