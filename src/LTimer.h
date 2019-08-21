#ifndef LTIMER_H
#define LTIMER_H

#include "globalvariables.h"
#include <stdio.h>

/*This wrapper class code was originally from Lazy Foo' Productions
(http://lazyfoo.net/)*/

class LTimer
{
    public:

    LTimer();

    //various clock actions
    void start();void stop();void pause(); void unpause();

    //Gets the timer's time
    Uint32 getTicks();

    //checks status of the time
    bool isStarted();
    bool isPaused();

    private:
    Uint32 mStartTicks; //clock time when timer starts
    Uint32 mPausedTicks; //the ticksstarted when the timer was paused
    //TImer status
    bool mPaused; bool mStarted;

};

#endif
