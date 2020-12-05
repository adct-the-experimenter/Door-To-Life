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
	
    if(sdl_event_ptr->type == SDL_QUIT)
    {
		thisEvent.event_id = Event_ID::QUIT_WINDOW; player_num = 1;
		pushEventInstance(thisEvent,player_num);
	}
    //If key was pressed
    else if(sdl_event_ptr->type == SDL_KEYDOWN && sdl_event_ptr->key.repeat == 0)
    {
		player_num = 1;
        switch(sdl_event_ptr->key.keysym.sym)
        {
            case SDLK_UP: {thisEvent.event_id = Event_ID::UP_ARROW; break;}
           // case SDLK_w: {thisEvent.event_id = Event_ID::UP_ARROW; break;}
            
            case SDLK_DOWN: {thisEvent.event_id = Event_ID::DOWN_ARROW; break;}
           // case SDLK_s: {thisEvent.event_id = Event_ID::DOWN_ARROW; break;}
            
            case SDLK_LEFT: {thisEvent.event_id = Event_ID::LEFT_ARROW; break;}
           // case SDLK_a: {thisEvent.event_id = Event_ID::LEFT_ARROW; break;}
            
            case SDLK_RIGHT: {thisEvent.event_id = Event_ID::RIGHT_ARROW; break;}
           // case SDLK_d: {thisEvent.event_id = Event_ID::RIGHT_ARROW; break;}
            
            case SDLK_SPACE:{ thisEvent.event_id = Event_ID::SPACE; break;}
            case SDLK_RETURN:{thisEvent.event_id = Event_ID::ENTER; break;}
            case SDLK_ESCAPE:{thisEvent.event_id = Event_ID::ESCAPE; break;}
            case SDLK_g:{thisEvent.event_id = Event_ID::G; break;}
            case SDLK_v:{thisEvent.event_id = Event_ID::V; break;}
            case SDLK_b:{thisEvent.event_id = Event_ID::B; break;}
            case SDLK_n:{thisEvent.event_id = Event_ID::N; break;}
            case SDLK_r:{thisEvent.event_id = Event_ID::R; break;}
            default:{thisEvent.event_id = Event_ID::NONE;  break;}
        }
        
        pushEventInstance(thisEvent,player_num);
    }
    //if key was pressed and repeated
    else if(sdl_event_ptr->type == SDL_KEYDOWN && sdl_event_ptr->key.repeat >= 1)
    {
		player_num = 1;
        switch(sdl_event_ptr->key.keysym.sym)
        {
            case SDLK_UP: {thisEvent.event_id = Event_ID::UP_ARROW_REPEAT; break;}
            case SDLK_w: {thisEvent.event_id = Event_ID::UP_ARROW_REPEAT; break;}
            
            case SDLK_DOWN: {thisEvent.event_id = Event_ID::DOWN_ARROW_REPEAT; break;}
            case SDLK_s: {thisEvent.event_id = Event_ID::DOWN_ARROW_REPEAT; break;}
            
            case SDLK_LEFT: {thisEvent.event_id = Event_ID::LEFT_ARROW_REPEAT; break;}
            case SDLK_a: {thisEvent.event_id = Event_ID::LEFT_ARROW_REPEAT; break;}
            
            case SDLK_RIGHT: {thisEvent.event_id = Event_ID::RIGHT_ARROW_REPEAT; break;}
            case SDLK_d: {thisEvent.event_id = Event_ID::RIGHT_ARROW_REPEAT; break;}
            
            case SDLK_SPACE:{ thisEvent.event_id = Event_ID::SPACE_REPEAT; break;}
            default:{thisEvent.event_id = Event_ID::NONE; break;}
        }
        
        pushEventInstance(thisEvent,player_num);
    }
    //if a key was released
    else if(sdl_event_ptr->type == SDL_KEYUP && sdl_event_ptr->key.repeat == 0)
    {
		player_num = 1;
		
        switch(sdl_event_ptr->key.keysym.sym )//slow down dot if key is released
        {
            case SDLK_UP: {thisEvent.event_id = Event_ID::UP_ARROW_RELEASE; break;}
            case SDLK_w: {thisEvent.event_id = Event_ID::UP_ARROW_RELEASE; break;}
            
            case SDLK_DOWN: {thisEvent.event_id = Event_ID::DOWN_ARROW_RELEASE; break;}
			case SDLK_s: {thisEvent.event_id = Event_ID::DOWN_ARROW_RELEASE; break;}
			
            case SDLK_LEFT: {thisEvent.event_id = Event_ID::LEFT_ARROW_RELEASE; break;}
			case SDLK_a: {thisEvent.event_id = Event_ID::LEFT_ARROW_RELEASE; break;}
			
            case SDLK_RIGHT: {thisEvent.event_id = Event_ID::RIGHT_ARROW_RELEASE; break;}
            case SDLK_d: {thisEvent.event_id = Event_ID::RIGHT_ARROW_RELEASE; break;}
  
            case SDLK_SPACE:{ thisEvent.event_id = Event_ID::SPACE_RELEASE; break;}
            default:{thisEvent.event_id = Event_ID::NONE; break;}
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
			player_num = 2;
			
			//X axis motion
			if( sdl_event_ptr->jaxis.axis == 0 )
			{
				//std::cout << "x axis value: " << sdl_event_ptr->jaxis.value << std::endl;
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
				//std::cout << "y axis value: " << sdl_event_ptr->jaxis.value << std::endl;
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
			
			
			thisEvent.joystick_xDir = xDir;
			thisEvent.joystick_yDir = yDir;
			pushEventInstance(thisEvent,player_num);
		}
		//Motion on controller 1
		else if( sdl_event_ptr->jaxis.which == 1 )
		{                        
			player_num = 3;
			
			//X axis motion
			if( sdl_event_ptr->jaxis.axis == 0 )
			{
				//std::cout << "x axis value: " << sdl_event_ptr->jaxis.value << std::endl;
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
				//std::cout << "y axis value: " << sdl_event_ptr->jaxis.value << std::endl;
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
			
			
			thisEvent.joystick_xDir = xDir;
			thisEvent.joystick_yDir = yDir;
			pushEventInstance(thisEvent,player_num);
		}
		//Motion on controller 2
		if( sdl_event_ptr->jaxis.which == 2 )
		{                        
			player_num = 4;
			
			//X axis motion
			if( sdl_event_ptr->jaxis.axis == 0 )
			{
				//std::cout << "x axis value: " << sdl_event_ptr->jaxis.value << std::endl;
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
				//std::cout << "y axis value: " << sdl_event_ptr->jaxis.value << std::endl;
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
			
			
			thisEvent.joystick_xDir = xDir;
			thisEvent.joystick_yDir = yDir;
			pushEventInstance(thisEvent,player_num);
		}
		
		
	}
	else if(sdl_event_ptr->type == SDL_JOYHATMOTION)
	{
		
		if( sdl_event_ptr->jhat.which == 0 )
		{
			player_num = 2;
			
			//joystick hat
			if( sdl_event_ptr->jhat.value == SDL_HAT_LEFTUP )
			{
				thisEvent.event_id = Event_ID::JOYSTICK_HAT_UP_LEFT; 
			}
			
			else if(sdl_event_ptr->jhat.value == SDL_HAT_RIGHTUP)
			{
				thisEvent.event_id = Event_ID::JOYSTICK_HAT_UP_RIGHT;
			}
			
			else if(sdl_event_ptr->jhat.value == SDL_HAT_UP)
			{
				thisEvent.event_id = Event_ID::JOYSTICK_HAT_UP;
			}
			
			else if(sdl_event_ptr->jhat.value == SDL_HAT_LEFT)
			{
				thisEvent.event_id = Event_ID::JOYSTICK_HAT_LEFT;
			}
			
			else if(sdl_event_ptr->jhat.value == SDL_HAT_RIGHT)
			{
				thisEvent.event_id = Event_ID::JOYSTICK_HAT_RIGHT;
			}
			
			else if(sdl_event_ptr->jhat.value == SDL_HAT_LEFTDOWN)
			{
				thisEvent.event_id = Event_ID::JOYSTICK_HAT_DOWN_LEFT; 
			}
			
			else if(sdl_event_ptr->jhat.value == SDL_HAT_RIGHTDOWN)
			{
				thisEvent.event_id = Event_ID::JOYSTICK_HAT_DOWN_RIGHT;
			}
			
			else if(sdl_event_ptr->jhat.value == SDL_HAT_DOWN)
			{
				thisEvent.event_id = Event_ID::JOYSTICK_HAT_DOWN;
			}
			
			else if(sdl_event_ptr->jhat.value == SDL_HAT_CENTERED)
			{
				thisEvent.event_id = Event_ID::JOYSTICK_HAT_NULL; 
			}
			else
			{
				thisEvent.event_id = Event_ID::NONE; 
			}
			
			pushEventInstance(thisEvent,player_num);
		}
		else if( sdl_event_ptr->jhat.which == 1 )
		{
			player_num = 3;
			
			//joystick hat
			if( sdl_event_ptr->jhat.value == SDL_HAT_LEFTUP )
			{
				thisEvent.event_id = Event_ID::JOYSTICK_HAT_UP_LEFT; 
			}
			
			else if(sdl_event_ptr->jhat.value == SDL_HAT_RIGHTUP)
			{
				thisEvent.event_id = Event_ID::JOYSTICK_HAT_UP_RIGHT;
			}
			
			else if(sdl_event_ptr->jhat.value == SDL_HAT_UP)
			{
				thisEvent.event_id = Event_ID::JOYSTICK_HAT_UP;
			}
			
			else if(sdl_event_ptr->jhat.value == SDL_HAT_LEFT)
			{
				thisEvent.event_id = Event_ID::JOYSTICK_HAT_LEFT;
			}
			
			else if(sdl_event_ptr->jhat.value == SDL_HAT_RIGHT)
			{
				thisEvent.event_id = Event_ID::JOYSTICK_HAT_RIGHT;
			}
			
			else if(sdl_event_ptr->jhat.value == SDL_HAT_LEFTDOWN)
			{
				thisEvent.event_id = Event_ID::JOYSTICK_HAT_DOWN_LEFT; 
			}
			
			else if(sdl_event_ptr->jhat.value == SDL_HAT_RIGHTDOWN)
			{
				thisEvent.event_id = Event_ID::JOYSTICK_HAT_DOWN_RIGHT;
			}
			
			else if(sdl_event_ptr->jhat.value == SDL_HAT_DOWN)
			{
				thisEvent.event_id = Event_ID::JOYSTICK_HAT_DOWN;
			}
			
			else if(sdl_event_ptr->jhat.value == SDL_HAT_CENTERED)
			{
				thisEvent.event_id = Event_ID::JOYSTICK_HAT_NULL; 
			}
			else
			{
				thisEvent.event_id = Event_ID::NONE; 
			}
			
			pushEventInstance(thisEvent,player_num);
		}
		else if( sdl_event_ptr->jhat.which == 2 )
		{
			player_num = 4;
			
			//joystick hat
			if( sdl_event_ptr->jhat.value == SDL_HAT_LEFTUP )
			{
				thisEvent.event_id = Event_ID::JOYSTICK_HAT_UP_LEFT; 
			}
			
			else if(sdl_event_ptr->jhat.value == SDL_HAT_RIGHTUP)
			{
				thisEvent.event_id = Event_ID::JOYSTICK_HAT_UP_RIGHT;
			}
			
			else if(sdl_event_ptr->jhat.value == SDL_HAT_UP)
			{
				thisEvent.event_id = Event_ID::JOYSTICK_HAT_UP;
			}
			
			else if(sdl_event_ptr->jhat.value == SDL_HAT_LEFT)
			{
				thisEvent.event_id = Event_ID::JOYSTICK_HAT_LEFT;
			}
			
			else if(sdl_event_ptr->jhat.value == SDL_HAT_RIGHT)
			{
				thisEvent.event_id = Event_ID::JOYSTICK_HAT_RIGHT;
			}
			
			else if(sdl_event_ptr->jhat.value == SDL_HAT_LEFTDOWN)
			{
				thisEvent.event_id = Event_ID::JOYSTICK_HAT_DOWN_LEFT; 
			}
			
			else if(sdl_event_ptr->jhat.value == SDL_HAT_RIGHTDOWN)
			{
				thisEvent.event_id = Event_ID::JOYSTICK_HAT_DOWN_RIGHT;
			}
			
			else if(sdl_event_ptr->jhat.value == SDL_HAT_DOWN)
			{
				thisEvent.event_id = Event_ID::JOYSTICK_HAT_DOWN;
			}
			
			else if(sdl_event_ptr->jhat.value == SDL_HAT_CENTERED)
			{
				thisEvent.event_id = Event_ID::JOYSTICK_HAT_NULL; 
			}
			else
			{
				thisEvent.event_id = Event_ID::NONE; 
			}
			
			pushEventInstance(thisEvent,player_num);
		}
		
	}
	else if(sdl_event_ptr->type == SDL_JOYBUTTONDOWN)
	{
		if(sdl_event_ptr->jbutton.which == 0)
		{
			player_num = 2;
			
			if( sdl_event_ptr->jbutton.state == SDL_PRESSED )
			{
				thisEvent.event_id = Event_ID::JOYSTICK_BUTTON_DOWN_PRESSED; 
			}
			else if(sdl_event_ptr->jbutton.state == SDL_RELEASED)
			{
				thisEvent.event_id = Event_ID::JOYSTICK_BUTTON_DOWN_RELEASED;
			}
			
			pushEventInstance(thisEvent,player_num);
		}
		else if(sdl_event_ptr->jbutton.which == 1)
		{
			player_num = 3;
			
			if( sdl_event_ptr->jbutton.state == SDL_PRESSED )
			{
				thisEvent.event_id = Event_ID::JOYSTICK_BUTTON_DOWN_PRESSED; 
			}
			else if(sdl_event_ptr->jbutton.state == SDL_RELEASED)
			{
				thisEvent.event_id = Event_ID::JOYSTICK_BUTTON_DOWN_RELEASED;
			}
			
			pushEventInstance(thisEvent,player_num);
		}
		else if(sdl_event_ptr->jbutton.which == 2)
		{
			player_num = 4;
			
			if( sdl_event_ptr->jbutton.state == SDL_PRESSED )
			{
				thisEvent.event_id = Event_ID::JOYSTICK_BUTTON_DOWN_PRESSED; 
			}
			else if(sdl_event_ptr->jbutton.state == SDL_RELEASED)
			{
				thisEvent.event_id = Event_ID::JOYSTICK_BUTTON_DOWN_RELEASED;
			}
			
			pushEventInstance(thisEvent,player_num);
		}
		
		
	}
	else if(sdl_event_ptr->type == SDL_JOYBUTTONUP)
	{
		if(sdl_event_ptr->jbutton.which == 0)
		{
			player_num = 2;
			
			if( sdl_event_ptr->jbutton.state == SDL_PRESSED )
			{
				thisEvent.event_id = Event_ID::JOYSTICK_BUTTON_UP_PRESSED; 
			}
			else if(sdl_event_ptr->jbutton.state == SDL_RELEASED)
			{
				thisEvent.event_id = Event_ID::JOYSTICK_BUTTON_UP_RELEASED;
			}
			
			pushEventInstance(thisEvent,player_num);
		}
		else if(sdl_event_ptr->jbutton.which == 1)
		{
			player_num = 3;
			
			if( sdl_event_ptr->jbutton.state == SDL_PRESSED )
			{
				thisEvent.event_id = Event_ID::JOYSTICK_BUTTON_UP_PRESSED; 
			}
			else if(sdl_event_ptr->jbutton.state == SDL_RELEASED)
			{
				thisEvent.event_id = Event_ID::JOYSTICK_BUTTON_UP_RELEASED;
			}
			
			pushEventInstance(thisEvent,player_num);
		}
		else if(sdl_event_ptr->jbutton.which == 2)
		{
			player_num = 4;
			
			if( sdl_event_ptr->jbutton.state == SDL_PRESSED )
			{
				thisEvent.event_id = Event_ID::JOYSTICK_BUTTON_UP_PRESSED; 
			}
			else if(sdl_event_ptr->jbutton.state == SDL_RELEASED)
			{
				thisEvent.event_id = Event_ID::JOYSTICK_BUTTON_UP_RELEASED;
			}
			
			pushEventInstance(thisEvent,player_num);
		}
		
	}
    else
    {
		thisEvent.event_id = Event_ID::NONE;
		pushEventInstance(thisEvent,1);
		thisEvent.event_id = Event_ID::NONE;
		pushEventInstance(thisEvent,2);
		thisEvent.event_id = Event_ID::NONE;
		pushEventInstance(thisEvent,3); 
		thisEvent.event_id = Event_ID::NONE;
		pushEventInstance(thisEvent,4);
	}
}

void pushEventInstance(Event thisEvent, int player_num)
{
	thisEvent.player_num = player_num;
	
	switch(player_num)
	{
		case 1:{ event_instances_queue_p1.push(thisEvent); break;}
		case 2:{ event_instances_queue_p2.push(thisEvent); break;}
		case 3:{ event_instances_queue_p3.push(thisEvent); break;}
		case 4:{ event_instances_queue_p4.push(thisEvent); break;}
		
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
