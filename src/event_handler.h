#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include "globalvariables.h"
#include <cstdint>
#include <queue>

extern SDL_Event sdl_event;

enum class Event : std::int8_t {
 
        NONE = 0,
        
    //Keys
        //arrows
        UP_ARROW, LEFT_ARROW, DOWN_ARROW, RIGHT_ARROW,
        UP_ARROW_REPEAT, LEFT_ARROW_REPEAT, DOWN_ARROW_REPEAT, RIGHT_ARROW_REPEAT,
        UP_ARROW_RELEASE,LEFT_ARROW_RELEASE,DOWN_ARROW_RELEASE,RIGHT_ARROW_RELEASE,
        // space
        SPACE, SPACE_REPEAT, SPACE_RELEASE,
        //Enter
        ENTER,
        //escape
        ESCAPE,
        
        //Various keys
        G,V,B,N,R,
        
    //Joystick events
		JOYSTICK_0_NULL, JOYSTICK_0_LEFT, JOYSTICK_0_RIGHT,
		JOYSTICK_0_UP, JOYSTICK_0_DOWN,
		JOYSTICK_0_UP_LEFT, JOYSTICK_0_DOWN_LEFT,
		JOYSTICK_0_UP_RIGHT, JOYSTICK_0_DOWN_RIGHT,
		
		JOYSTICK_0_HAT_NULL, JOYSTICK_0_HAT_LEFT, JOYSTICK_0_HAT_RIGHT,
		JOYSTICK_0_HAT_UP, JOYSTICK_0_HAT_DOWN,
		JOYSTICK_0_HAT_UP_LEFT, JOYSTICK_0_HAT_DOWN_LEFT,
		JOYSTICK_0_HAT_UP_RIGHT, JOYSTICK_0_HAT_DOWN_RIGHT,
		
		JOYSTICK_1_HAT_NULL, JOYSTICK_1_HAT_LEFT, JOYSTICK_1_HAT_RIGHT,
		JOYSTICK_1_HAT_UP, JOYSTICK_1_HAT_DOWN,
		JOYSTICK_1_HAT_UP_LEFT, JOYSTICK_1_HAT_DOWN_LEFT,
		JOYSTICK_1_HAT_UP_RIGHT, JOYSTICK_1_HAT_DOWN_RIGHT,
    
    //Quit
        QUIT_WINDOW
};

//queue of events, first in first out order
extern std::queue <Event> event_instances_queue_p1;
extern std::queue <Event> event_instances_queue_p2;

//function to push event into queue
void pushEventInstance(Event thisEvent, int player_num);

//function to pop event from queue. pops event in front
void popEventInstanceFromFront();
void popEventInstanceFromFront_Player1();
void popEventInstanceFromFront_Player2();

//function to tell whether event queue is empty or not
bool isEventQueueEmpty();
bool isEventQueueEmpty_Player1();
bool isEventQueueEmpty_Player2();

//function to get event in front of queue
Event& getEventInstanceFront();
Event& getEventInstanceFront_Player1();
Event& getEventInstanceFront_Player2();

//function to clear events on queue
void clearEventsQueue();

//function to run loop for event and set event 
void run_event_handler();
//function to set events in queue
void readAndSetEventQueue(SDL_Event* sdl_event_ptr);

#endif
