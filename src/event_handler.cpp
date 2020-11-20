#include "event_handler.h"

std::queue <Event> event_instances_queue_p1;
std::queue <Event> event_instances_queue_p2;
std::queue <Event> event_instances_queue_p3;
std::queue <Event> event_instances_queue_p4;
SDL_Event sdl_event;

//function to set event 
void run_event_handler()
{
    while( SDL_PollEvent(&sdl_event) != 0)
    {
        readAndSetEventQueue(&sdl_event);
    }
}

//Analog joystick dead zone
const int JOYSTICK_DEAD_ZONE = 8000;

void readAndSetEventQueue(SDL_Event* sdl_event_ptr)
{
	Event thisEvent;
	int player_num = 0;
	
    if(sdl_event_ptr->type == SDL_QUIT){thisEvent.event_id = Event_ID::QUIT_WINDOW; player_num = 1;}
    //If key was pressed
    else if(sdl_event_ptr->type == SDL_KEYDOWN && sdl_event_ptr->key.repeat == 0)
    {
        switch(sdl_event_ptr->key.keysym.sym)
        {
            case SDLK_UP: {thisEvent.event_id = Event_ID::UP_ARROW; player_num = 1; break;}
            case SDLK_w: {thisEvent.event_id = Event_ID::UP_ARROW; player_num = 1; break;}
            
            case SDLK_DOWN: {thisEvent.event_id = Event_ID::DOWN_ARROW; player_num = 1; break;}
            case SDLK_s: {thisEvent.event_id = Event_ID::DOWN_ARROW; player_num = 1; break;}
            
            case SDLK_LEFT: {thisEvent.event_id = Event_ID::LEFT_ARROW; player_num = 1; break;}
            case SDLK_a: {thisEvent.event_id = Event_ID::LEFT_ARROW; player_num = 1; break;}
            
            case SDLK_RIGHT: {thisEvent.event_id = Event_ID::RIGHT_ARROW; player_num = 1; break;}
            case SDLK_d: {thisEvent.event_id = Event_ID::RIGHT_ARROW; player_num = 1; break;}
            
            case SDLK_SPACE:{ thisEvent.event_id = Event_ID::SPACE; player_num = 1; break;}
            case SDLK_RETURN:{thisEvent.event_id = Event_ID::ENTER; player_num = 1; break;}
            case SDLK_ESCAPE:{thisEvent.event_id = Event_ID::ESCAPE; player_num = 1; break;}
            case SDLK_g:{thisEvent.event_id = Event_ID::G; player_num = 1; break;}
            case SDLK_v:{thisEvent.event_id = Event_ID::V; player_num = 1; break;}
            case SDLK_b:{thisEvent.event_id = Event_ID::B; player_num = 1; break;}
            case SDLK_n:{thisEvent.event_id = Event_ID::N; player_num = 1; break;}
            case SDLK_r:{thisEvent.event_id = Event_ID::R; player_num = 1; break;}
            default:{thisEvent.event_id = Event_ID::NONE; player_num = 1; break;}
        }
        pushEventInstance(thisEvent,player_num);
    }
    //if key was pressed and repeated
    else if(sdl_event_ptr->type == SDL_KEYDOWN && sdl_event_ptr->key.repeat >= 1)
    {
        switch(sdl_event_ptr->key.keysym.sym)
        {
            case SDLK_UP: {thisEvent.event_id = Event_ID::UP_ARROW_REPEAT; player_num = 1; break;}
            case SDLK_w: {thisEvent.event_id = Event_ID::UP_ARROW_REPEAT; player_num = 1; break;}
            
            case SDLK_DOWN: {thisEvent.event_id = Event_ID::DOWN_ARROW_REPEAT; player_num = 1; break;}
            case SDLK_s: {thisEvent.event_id = Event_ID::DOWN_ARROW_REPEAT; player_num = 1; break;}
            
            case SDLK_LEFT: {thisEvent.event_id = Event_ID::LEFT_ARROW_REPEAT; player_num = 1; break;}
            case SDLK_a: {thisEvent.event_id = Event_ID::LEFT_ARROW_REPEAT; player_num = 1; break;}
            
            case SDLK_RIGHT: {thisEvent.event_id = Event_ID::RIGHT_ARROW_REPEAT; player_num = 1; break;}
            case SDLK_d: {thisEvent.event_id = Event_ID::RIGHT_ARROW_REPEAT; player_num = 1; break;}
            
            case SDLK_SPACE:{ thisEvent.event_id = Event_ID::SPACE_REPEAT; player_num = 1; break;}
            default:{thisEvent.event_id = Event_ID::NONE; player_num = 1; break;}
        }
        pushEventInstance(thisEvent,player_num);
    }
    //if a key was released
    else if(sdl_event_ptr->type == SDL_KEYUP && sdl_event_ptr->key.repeat == 0)
    {
        switch(sdl_event_ptr->key.keysym.sym )//slow down dot if key is released
        {
            case SDLK_UP: {thisEvent.event_id = Event_ID::UP_ARROW_RELEASE; player_num = 1; break;}
            case SDLK_w: {thisEvent.event_id = Event_ID::UP_ARROW_RELEASE; player_num = 1; break;}
            
            case SDLK_DOWN: {thisEvent.event_id = Event_ID::DOWN_ARROW_RELEASE; player_num = 1; break;}
			case SDLK_s: {thisEvent.event_id = Event_ID::DOWN_ARROW_RELEASE; player_num = 1; break;}
			
            case SDLK_LEFT: {thisEvent.event_id = Event_ID::LEFT_ARROW_RELEASE; player_num = 1; break;}
			case SDLK_a: {thisEvent.event_id = Event_ID::LEFT_ARROW_RELEASE; player_num = 1; break;}
			
            case SDLK_RIGHT: {thisEvent.event_id = Event_ID::RIGHT_ARROW_RELEASE; player_num = 1; break;}
            case SDLK_d: {thisEvent.event_id = Event_ID::RIGHT_ARROW_RELEASE; player_num = 1; break;}
  
            case SDLK_SPACE:{ thisEvent.event_id = Event_ID::SPACE_RELEASE; player_num = 1; break;}
            default:{thisEvent.event_id = Event_ID::NONE; player_num = 1; break;}
        }
        
        pushEventInstance(thisEvent,player_num);
    }
    else if( sdl_event_ptr->type == SDL_JOYAXISMOTION )
	{
		//Normalized direction
		int xDir = 0;
		int yDir = 0;
		
		//Motion on controller 0
		if( sdl_event_ptr->jaxis.which == 0 )
		{                        
			//X axis motion
			if( sdl_event_ptr->jaxis.axis == 0 )
			{
				//Left of dead zone
				if( sdl_event_ptr->jaxis.value < -JOYSTICK_DEAD_ZONE )
				{
					xDir = -1;
				}
				//Right of dead zone
				else if( sdl_event_ptr->jaxis.value > JOYSTICK_DEAD_ZONE )
				{
					xDir =  1;
				}
				else
				{
					xDir = 0;
				}
			}
			
			//Y axis motion
			if( sdl_event_ptr->jaxis.axis == 1 )
			{
				//Below of dead zone
				if( sdl_event_ptr->jaxis.value < -JOYSTICK_DEAD_ZONE )
				{
					yDir = -1;
				}
				//Above of dead zone
				else if( sdl_event_ptr->jaxis.value > JOYSTICK_DEAD_ZONE )
				{
					yDir =  1;
				}
				else
				{
					yDir = 0;
				}
			}
			
			if(xDir == 0)
			{
				if(yDir == 0){thisEvent.event_id = Event_ID::JOYSTICK_0_NULL; player_num = 2;}
				if(yDir == -1){thisEvent.event_id = Event_ID::JOYSTICK_0_LEFT; player_num = 2;}
				if(yDir == 1){thisEvent.event_id = Event_ID::JOYSTICK_0_RIGHT; player_num = 2;}
				
			}
			else if(xDir == -1)
			{
				if(yDir == 0){thisEvent.event_id = Event_ID::JOYSTICK_0_LEFT; player_num = 2;}
				if(yDir == -1){thisEvent.event_id = Event_ID::JOYSTICK_0_DOWN_LEFT; player_num = 2;}
				if(yDir == 1){thisEvent.event_id = Event_ID::JOYSTICK_0_UP_LEFT; player_num = 2;}
			}
			else if(xDir == 1)
			{
				if(yDir == 0){thisEvent.event_id = Event_ID::JOYSTICK_0_RIGHT; player_num = 2;}
				if(yDir == -1){thisEvent.event_id = Event_ID::JOYSTICK_0_DOWN_RIGHT; player_num = 2;}
				if(yDir == 1){thisEvent.event_id = Event_ID::JOYSTICK_0_UP_RIGHT; player_num = 2;}
			}
			
		}
		
		thisEvent.joystick_xDir = xDir;
		thisEvent.joystick_yDir = yDir;
		pushEventInstance(thisEvent,player_num);
	}
	else if(sdl_event_ptr->type == SDL_JOYHATMOTION)
	{
		
		
		if( sdl_event_ptr->jhat.which == 0 )
		{
			//joystick hat
			if( sdl_event_ptr->jhat.value == SDL_HAT_LEFTUP )
			{
				thisEvent.event_id = Event_ID::JOYSTICK_0_HAT_UP_LEFT; player_num = 2;
			}
			
			else if(sdl_event_ptr->jhat.value == SDL_HAT_RIGHTUP)
			{
				thisEvent.event_id = Event_ID::JOYSTICK_0_HAT_UP_RIGHT; player_num = 2;
			}
			
			else if(sdl_event_ptr->jhat.value == SDL_HAT_UP)
			{
				thisEvent.event_id = Event_ID::JOYSTICK_0_HAT_UP; player_num = 2;
			}
			
			else if(sdl_event_ptr->jhat.value == SDL_HAT_LEFT)
			{
				thisEvent.event_id = Event_ID::JOYSTICK_0_HAT_LEFT; player_num = 2;
			}
			
			else if(sdl_event_ptr->jhat.value == SDL_HAT_RIGHT)
			{
				thisEvent.event_id = Event_ID::JOYSTICK_0_HAT_RIGHT; player_num = 2;
			}
			
			else if(sdl_event_ptr->jhat.value == SDL_HAT_LEFTDOWN)
			{
				thisEvent.event_id = Event_ID::JOYSTICK_0_HAT_DOWN_LEFT; player_num = 2;
			}
			
			else if(sdl_event_ptr->jhat.value == SDL_HAT_RIGHTDOWN)
			{
				thisEvent.event_id = Event_ID::JOYSTICK_0_HAT_DOWN_RIGHT; player_num = 2;
			}
			
			else if(sdl_event_ptr->jhat.value == SDL_HAT_DOWN)
			{
				thisEvent.event_id = Event_ID::JOYSTICK_0_HAT_DOWN; player_num = 2;
			}
			
			else if(sdl_event_ptr->jhat.value == SDL_HAT_CENTERED)
			{
				thisEvent.event_id = Event_ID::JOYSTICK_0_HAT_NULL; player_num = 2;
			}
			else
			{
				thisEvent.event_id = Event_ID::NONE; player_num = 2;
			}
			
			pushEventInstance(thisEvent,player_num);
		}
		else if( sdl_event_ptr->jhat.which == 1 )
		{
			//joystick hat
			if( sdl_event_ptr->jhat.value == SDL_HAT_LEFTUP )
			{
				thisEvent.event_id = Event_ID::JOYSTICK_1_HAT_UP_LEFT; player_num = 3;
			}
			
			else if(sdl_event_ptr->jhat.value == SDL_HAT_RIGHTUP)
			{
				thisEvent.event_id = Event_ID::JOYSTICK_1_HAT_UP_RIGHT; player_num = 3;
			}
			
			else if(sdl_event_ptr->jhat.value == SDL_HAT_UP)
			{
				thisEvent.event_id = Event_ID::JOYSTICK_1_HAT_UP; player_num = 3;
			}
			
			else if(sdl_event_ptr->jhat.value == SDL_HAT_LEFT)
			{
				thisEvent.event_id = Event_ID::JOYSTICK_1_HAT_LEFT; player_num = 3;
			}
			
			else if(sdl_event_ptr->jhat.value == SDL_HAT_RIGHT)
			{
				thisEvent.event_id = Event_ID::JOYSTICK_1_HAT_RIGHT; player_num = 3;
			}
			
			else if(sdl_event_ptr->jhat.value == SDL_HAT_LEFTDOWN)
			{
				thisEvent.event_id = Event_ID::JOYSTICK_1_HAT_DOWN_LEFT; player_num = 3;
			}
			
			else if(sdl_event_ptr->jhat.value == SDL_HAT_RIGHTDOWN)
			{
				thisEvent.event_id = Event_ID::JOYSTICK_1_HAT_DOWN_RIGHT; player_num = 3;
			}
			
			else if(sdl_event_ptr->jhat.value == SDL_HAT_DOWN)
			{
				thisEvent.event_id = Event_ID::JOYSTICK_1_HAT_DOWN; player_num = 3;
			}
			
			else if(sdl_event_ptr->jhat.value == SDL_HAT_CENTERED)
			{
				thisEvent.event_id = Event_ID::JOYSTICK_1_HAT_NULL; player_num = 3;
			}
			else
			{
				thisEvent.event_id = Event_ID::NONE; player_num = 3;
			}
			
			pushEventInstance(thisEvent,player_num);
		}
		
	}
	else if(sdl_event_ptr->type == SDL_JOYBUTTONDOWN)
	{
		if(sdl_event_ptr->jbutton.which == 0)
		{
			if( sdl_event_ptr->jbutton.state == SDL_PRESSED )
			{
				thisEvent.event_id = Event_ID::JOYSTICK_0_BUTTON_DOWN_PRESSED; player_num = 2;
			}
			else if(sdl_event_ptr->jbutton.state == SDL_RELEASED)
			{
				thisEvent.event_id = Event_ID::JOYSTICK_0_BUTTON_DOWN_RELEASED; player_num = 2;
			}
		}
		else if(sdl_event_ptr->jbutton.which == 1)
		{
			if( sdl_event_ptr->jbutton.state == SDL_PRESSED )
			{
				thisEvent.event_id = Event_ID::JOYSTICK_1_BUTTON_DOWN_PRESSED; player_num = 3;
			}
			else if( sdl_event_ptr->jbutton.state == SDL_RELEASED )
			{
				thisEvent.event_id = Event_ID::JOYSTICK_1_BUTTON_DOWN_RELEASED; player_num = 3;
			}
		}
		
		pushEventInstance(thisEvent,player_num);
	}
	else if(sdl_event_ptr->type == SDL_JOYBUTTONUP)
	{
		if(sdl_event_ptr->jbutton.which == 0)
		{
			if( sdl_event_ptr->jbutton.state == SDL_PRESSED )
			{
				thisEvent.event_id = Event_ID::JOYSTICK_0_BUTTON_UP_PRESSED; player_num = 2;
			}
			else if(sdl_event_ptr->jbutton.state == SDL_RELEASED)
			{
				thisEvent.event_id = Event_ID::JOYSTICK_0_BUTTON_UP_RELEASED; player_num = 2;
			}
		}
		else if(sdl_event_ptr->jbutton.which == 1)
		{
			if( sdl_event_ptr->jbutton.state == SDL_PRESSED )
			{
				thisEvent.event_id = Event_ID::JOYSTICK_1_BUTTON_UP_PRESSED; player_num = 3;
			}
			else if( sdl_event_ptr->jbutton.state == SDL_RELEASED )
			{
				thisEvent.event_id = Event_ID::JOYSTICK_1_BUTTON_UP_RELEASED; player_num = 3;
			}
		}
		
		pushEventInstance(thisEvent,player_num);
	}
    else
    {
		thisEvent.event_id = Event_ID::NONE;
		pushEventInstance(thisEvent,1);
		thisEvent.event_id = Event_ID::NONE;
		pushEventInstance(thisEvent,2);
		thisEvent.event_id = Event_ID::NONE;
		pushEventInstance(thisEvent,3); 
	}
}

void pushEventInstance(Event thisEvent, int player_num)
{
	switch(player_num)
	{
		case 1:{ event_instances_queue_p1.push(thisEvent); break;}
		case 2:{ event_instances_queue_p2.push(thisEvent); break;}
		case 3:{ event_instances_queue_p3.push(thisEvent); break;}
		
	}
	
}
void popEventInstanceFromFront(){event_instances_queue_p1.pop();}
void popEventInstanceFromFront_Player1(){event_instances_queue_p1.pop();}
void popEventInstanceFromFront_Player2(){event_instances_queue_p2.pop();}
void popEventInstanceFromFront_Player3(){event_instances_queue_p3.pop();}
void popEventInstanceFromFront_Player4(){event_instances_queue_p4.pop();}

Event& getEventInstanceFront(){return event_instances_queue_p1.front();}
Event& getEventInstanceFront_Player1(){return event_instances_queue_p1.front();}
Event& getEventInstanceFront_Player2(){return event_instances_queue_p2.front();}
Event& getEventInstanceFront_Player3(){return event_instances_queue_p3.front();}
Event& getEventInstanceFront_Player4(){return event_instances_queue_p4.front();}

bool isEventQueueEmpty(){return event_instances_queue_p1.empty();}
bool isEventQueueEmpty_Player1(){return event_instances_queue_p1.empty();}
bool isEventQueueEmpty_Player2(){return event_instances_queue_p2.empty();}
bool isEventQueueEmpty_Player3(){return event_instances_queue_p3.empty();}
bool isEventQueueEmpty_Player4(){return event_instances_queue_p4.empty();}

void clearEventsQueue()
{
    std::queue <Event> empty_queue;
    //swap with empty queue
    event_instances_queue_p1.swap(empty_queue);
    event_instances_queue_p2.swap(empty_queue);
    event_instances_queue_p3.swap(empty_queue);
    event_instances_queue_p4.swap(empty_queue);
}
