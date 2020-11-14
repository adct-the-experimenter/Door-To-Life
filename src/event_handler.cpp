#include "event_handler.h"

std::queue <Event> event_instances_queue_p1;
std::queue <Event> event_instances_queue_p2;
std::queue <Event> event_instances_queue_p3;
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
    if(sdl_event_ptr->type == SDL_QUIT){pushEventInstance(Event::QUIT_WINDOW,1);}
    //If key was pressed
    else if(sdl_event_ptr->type == SDL_KEYDOWN && sdl_event_ptr->key.repeat == 0)
    {
        switch(sdl_event_ptr->key.keysym.sym)
        {
            case SDLK_UP: {pushEventInstance(Event::UP_ARROW,1); break;}
            case SDLK_w: {pushEventInstance(Event::UP_ARROW,1); break;}
            
            case SDLK_DOWN: {pushEventInstance(Event::DOWN_ARROW,1); break;}
            case SDLK_s: {pushEventInstance(Event::DOWN_ARROW,1); break;}
            
            case SDLK_LEFT: {pushEventInstance(Event::LEFT_ARROW,1); break;}
            case SDLK_a: {pushEventInstance(Event::LEFT_ARROW,1); break;}
            
            case SDLK_RIGHT: {pushEventInstance(Event::RIGHT_ARROW,1); break;}
            case SDLK_d: {pushEventInstance(Event::RIGHT_ARROW,1); break;}
            
            case SDLK_SPACE:{ pushEventInstance(Event::SPACE,1); break;}
            case SDLK_RETURN:{pushEventInstance(Event::ENTER,1); break;}
            case SDLK_ESCAPE:{pushEventInstance(Event::ESCAPE,1); break;}
            case SDLK_g:{pushEventInstance(Event::G,1); break;}
            case SDLK_v:{pushEventInstance(Event::V,1); break;}
            case SDLK_b:{pushEventInstance(Event::B,1); break;}
            case SDLK_n:{pushEventInstance(Event::N,1); break;}
            case SDLK_r:{pushEventInstance(Event::R,1); break;}
            default:{pushEventInstance(Event::NONE,1); break;}
        }
    }
    //if key was pressed and repeated
    else if(sdl_event_ptr->type == SDL_KEYDOWN && sdl_event_ptr->key.repeat >= 1)
    {
        switch(sdl_event_ptr->key.keysym.sym)
        {
            case SDLK_UP: {pushEventInstance(Event::UP_ARROW_REPEAT,1); break;}
            case SDLK_w: {pushEventInstance(Event::UP_ARROW_REPEAT,1); break;}
            
            case SDLK_DOWN: {pushEventInstance(Event::DOWN_ARROW_REPEAT,1); break;}
            case SDLK_s: {pushEventInstance(Event::DOWN_ARROW_REPEAT,1); break;}
            
            case SDLK_LEFT: {pushEventInstance(Event::LEFT_ARROW_REPEAT,1); break;}
            case SDLK_a: {pushEventInstance(Event::LEFT_ARROW_REPEAT,1); break;}
            
            case SDLK_RIGHT: {pushEventInstance(Event::RIGHT_ARROW_REPEAT,1); break;}
            case SDLK_d: {pushEventInstance(Event::RIGHT_ARROW_REPEAT,1); break;}
            
            case SDLK_SPACE:{ pushEventInstance(Event::SPACE_REPEAT,1); break;}
            default:{pushEventInstance(Event::NONE,1); break;}
        }
    }
    //if a key was released
    else if(sdl_event_ptr->type == SDL_KEYUP && sdl_event_ptr->key.repeat == 0)
    {
        switch(sdl_event_ptr->key.keysym.sym )//slow down dot if key is released
        {
            case SDLK_UP: {pushEventInstance(Event::UP_ARROW_RELEASE,1); break;}
            case SDLK_w: {pushEventInstance(Event::UP_ARROW_RELEASE,1); break;}
            
            case SDLK_DOWN: {pushEventInstance(Event::DOWN_ARROW_RELEASE,1); break;}
			case SDLK_s: {pushEventInstance(Event::DOWN_ARROW_RELEASE,1); break;}
			
            case SDLK_LEFT: {pushEventInstance(Event::LEFT_ARROW_RELEASE,1); break;}
			case SDLK_a: {pushEventInstance(Event::LEFT_ARROW_RELEASE,1); break;}
			
            case SDLK_RIGHT: {pushEventInstance(Event::RIGHT_ARROW_RELEASE,1); break;}
            case SDLK_d: {pushEventInstance(Event::RIGHT_ARROW_RELEASE,1); break;}
  
            case SDLK_SPACE:{ pushEventInstance(Event::SPACE_RELEASE,1); break;}
            default:{pushEventInstance(Event::NONE,1); break;}
        }
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
				if(yDir == 0){pushEventInstance(Event::JOYSTICK_0_NULL,2);}
				if(yDir == -1){pushEventInstance(Event::JOYSTICK_0_LEFT,2);}
				if(yDir == 1){pushEventInstance(Event::JOYSTICK_0_RIGHT,2);}
			}
			else if(xDir == -1)
			{
				if(yDir == 0){pushEventInstance(Event::JOYSTICK_0_LEFT,2);}
				if(yDir == -1){pushEventInstance(Event::JOYSTICK_0_DOWN_LEFT,2);}
				if(yDir == 1){pushEventInstance(Event::JOYSTICK_0_UP_LEFT,2);}
			}
			else if(xDir == 1)
			{
				if(yDir == 0){pushEventInstance(Event::JOYSTICK_0_RIGHT,2);}
				if(yDir == -1){pushEventInstance(Event::JOYSTICK_0_DOWN_RIGHT,2);}
				if(yDir == 1){pushEventInstance(Event::JOYSTICK_0_UP_RIGHT,2);}
			}
		}
	}
	else if(sdl_event_ptr->type == SDL_JOYHATMOTION)
	{
		
		
		if( sdl_event_ptr->jhat.which == 0 )
		{
			//joystick hat
			if( sdl_event_ptr->jhat.value == SDL_HAT_LEFTUP )
			{
				pushEventInstance(Event::JOYSTICK_0_HAT_UP_LEFT,2);
			}
			
			else if(sdl_event_ptr->jhat.value == SDL_HAT_RIGHTUP)
			{
				pushEventInstance(Event::JOYSTICK_0_HAT_UP_RIGHT,2);
			}
			
			else if(sdl_event_ptr->jhat.value == SDL_HAT_UP)
			{
				pushEventInstance(Event::JOYSTICK_0_HAT_UP,2);
			}
			
			else if(sdl_event_ptr->jhat.value == SDL_HAT_LEFT)
			{
				pushEventInstance(Event::JOYSTICK_0_HAT_LEFT,2);
			}
			
			else if(sdl_event_ptr->jhat.value == SDL_HAT_RIGHT)
			{
				pushEventInstance(Event::JOYSTICK_0_HAT_RIGHT,2);
			}
			
			else if(sdl_event_ptr->jhat.value == SDL_HAT_LEFTDOWN)
			{
				pushEventInstance(Event::JOYSTICK_0_HAT_DOWN_LEFT,2);
			}
			
			else if(sdl_event_ptr->jhat.value == SDL_HAT_RIGHTDOWN)
			{
				pushEventInstance(Event::JOYSTICK_0_HAT_DOWN_RIGHT,2);
			}
			
			else if(sdl_event_ptr->jhat.value == SDL_HAT_DOWN)
			{
				pushEventInstance(Event::JOYSTICK_0_HAT_DOWN,2);
			}
			
			else if(sdl_event_ptr->jhat.value == SDL_HAT_CENTERED)
			{
				pushEventInstance(Event::JOYSTICK_0_HAT_NULL,2);
			}
			else
			{
				pushEventInstance(Event::NONE,2);
			}
		}
		else if( sdl_event_ptr->jhat.which == 1 )
		{
			//joystick hat
			if( sdl_event_ptr->jhat.value == SDL_HAT_LEFTUP )
			{
				pushEventInstance(Event::JOYSTICK_1_HAT_UP_LEFT,3);
			}
			
			else if(sdl_event_ptr->jhat.value == SDL_HAT_RIGHTUP)
			{
				pushEventInstance(Event::JOYSTICK_1_HAT_UP_RIGHT,3);
			}
			
			else if(sdl_event_ptr->jhat.value == SDL_HAT_UP)
			{
				pushEventInstance(Event::JOYSTICK_1_HAT_UP,3);
			}
			
			else if(sdl_event_ptr->jhat.value == SDL_HAT_LEFT)
			{
				pushEventInstance(Event::JOYSTICK_1_HAT_LEFT,3);
			}
			
			else if(sdl_event_ptr->jhat.value == SDL_HAT_RIGHT)
			{
				pushEventInstance(Event::JOYSTICK_1_HAT_RIGHT,3);
			}
			
			else if(sdl_event_ptr->jhat.value == SDL_HAT_LEFTDOWN)
			{
				pushEventInstance(Event::JOYSTICK_1_HAT_DOWN_LEFT,3);
			}
			
			else if(sdl_event_ptr->jhat.value == SDL_HAT_RIGHTDOWN)
			{
				pushEventInstance(Event::JOYSTICK_1_HAT_DOWN_RIGHT,3);
			}
			
			else if(sdl_event_ptr->jhat.value == SDL_HAT_DOWN)
			{
				pushEventInstance(Event::JOYSTICK_1_HAT_DOWN,3);
			}
			
			else if(sdl_event_ptr->jhat.value == SDL_HAT_CENTERED)
			{
				pushEventInstance(Event::JOYSTICK_1_HAT_NULL,3);
			}
			else
			{
				pushEventInstance(Event::NONE,3);
			}
		}
	}
	else if(sdl_event_ptr->type == SDL_JOYBUTTONDOWN)
	{
		if(sdl_event_ptr->button.which == 0)
		{
			if( sdl_event_ptr->button.state == SDL_PRESSED )
			{
				pushEventInstance(Event::JOYSTICK_0_BUTTON_DOWN_PRESSED,2);
			}
			else if(sdl_event_ptr->button.state == SDL_RELEASED)
			{
				pushEventInstance(Event::JOYSTICK_0_BUTTON_DOWN_RELEASED,2);
			}
		}
		else if(sdl_event_ptr->button.which == 1)
		{
			if( sdl_event_ptr->button.state == SDL_PRESSED )
			{
				pushEventInstance(Event::JOYSTICK_1_BUTTON_DOWN_PRESSED,3);
			}
			else if( sdl_event_ptr->button.state == SDL_RELEASED )
			{
				pushEventInstance(Event::JOYSTICK_1_BUTTON_DOWN_RELEASED,3);
			}
		}
	}
	else if(sdl_event_ptr->type == SDL_JOYBUTTONUP)
	{
		if(sdl_event_ptr->button.which == 0)
		{
			if( sdl_event_ptr->button.state == SDL_PRESSED )
			{
				pushEventInstance(Event::JOYSTICK_0_BUTTON_UP_PRESSED,2);
			}
			else if(sdl_event_ptr->button.state == SDL_RELEASED)
			{
				pushEventInstance(Event::JOYSTICK_0_BUTTON_UP_RELEASED,2);
			}
		}
		else if(sdl_event_ptr->button.which == 1)
		{
			if( sdl_event_ptr->button.state == SDL_PRESSED )
			{
				pushEventInstance(Event::JOYSTICK_1_BUTTON_UP_PRESSED,3);
			}
			else if( sdl_event_ptr->button.state == SDL_RELEASED )
			{
				pushEventInstance(Event::JOYSTICK_1_BUTTON_UP_RELEASED,3);
			}
		}
	}
    else{pushEventInstance(Event::NONE,3); pushEventInstance(Event::NONE,2); pushEventInstance(Event::NONE,1);}
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

Event& getEventInstanceFront(){return event_instances_queue_p1.front();}
Event& getEventInstanceFront_Player1(){return event_instances_queue_p1.front();}
Event& getEventInstanceFront_Player2(){return event_instances_queue_p2.front();}
Event& getEventInstanceFront_Player3(){return event_instances_queue_p3.front();}

bool isEventQueueEmpty(){return event_instances_queue_p1.empty();}
bool isEventQueueEmpty_Player1(){return event_instances_queue_p1.empty();}
bool isEventQueueEmpty_Player2(){return event_instances_queue_p2.empty();}
bool isEventQueueEmpty_Player3(){return event_instances_queue_p3.empty();}

void clearEventsQueue()
{
    std::queue <Event> empty_queue;
    //swap with empty queue
    event_instances_queue_p1.swap(empty_queue);
    event_instances_queue_p2.swap(empty_queue);
}
