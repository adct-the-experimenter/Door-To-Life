#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include "globalvariables.h"
#include <cstdint>
#include <queue>

extern SDL_Event sdl_event;



enum class Event_ID : std::int8_t {
 
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
		
		//joystick stick position saved in xDir,yDir variables
		
		//joystick hat events
		JOYSTICK_HAT_NULL, JOYSTICK_HAT_LEFT, JOYSTICK_HAT_RIGHT,
		JOYSTICK_HAT_UP, JOYSTICK_HAT_DOWN,
		JOYSTICK_HAT_UP_LEFT, JOYSTICK_HAT_DOWN_LEFT,
		JOYSTICK_HAT_UP_RIGHT, JOYSTICK_HAT_DOWN_RIGHT,
		
		//joystick button presses
		JOYSTICK_BUTTON_DOWN_PRESSED, JOYSTICK_BUTTON_DOWN_RELEASED, 
		JOYSTICK_BUTTON_UP_PRESSED, JOYSTICK_BUTTON_UP_RELEASED,
		
    
    //Quit
        QUIT_WINDOW
};

struct Event
{
	Event_ID event_id; //event id for joystick events
	int joystick_xDir; //x direction of joystick
	int joystick_yDir; //y direction of joystick
	int player_num; //player for which event is intended
};

//queue of events, first in first out order
extern std::queue <Event> event_instances_queue_p1;
extern std::queue <Event> event_instances_queue_p2;
extern std::queue <Event> event_instances_queue_p3;
extern std::queue <Event> event_instances_queue_p4;

//function to push event into queue
void pushEventInstance(Event thisEvent, int player_num);

//function to pop event from queue. pops event in front
void popEventInstanceFromFront();
void popEventInstanceFromFront_Player1();
void popEventInstanceFromFront_Player2();
void popEventInstanceFromFront_Player3();
void popEventInstanceFromFront_Player4();

//function to tell whether event queue is empty or not
bool isEventQueueEmpty();
bool isEventQueueEmpty_Player1();
bool isEventQueueEmpty_Player2();
bool isEventQueueEmpty_Player3();
bool isEventQueueEmpty_Player4();

//function to get event in front of queue
Event& getEventInstanceFront();
Event& getEventInstanceFront_Player1();
Event& getEventInstanceFront_Player2();
Event& getEventInstanceFront_Player3();
Event& getEventInstanceFront_Player4();

//function to clear events on queue
void clearEventsQueue();

//function to run loop for event and set event 
void run_event_handler();
//function to set events in queue
void readAndSetEventQueue(SDL_Event* sdl_event_ptr);

#endif
