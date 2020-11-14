#include "event_handler.h"

std::queue <Event> event_instances_queue;
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
    if(sdl_event_ptr->type == SDL_QUIT){pushEventInstance(Event::QUIT_WINDOW);}
    //If key was pressed
    else if(sdl_event_ptr->type == SDL_KEYDOWN && sdl_event_ptr->key.repeat == 0)
    {
        switch(sdl_event_ptr->key.keysym.sym)
        {
            case SDLK_UP: {pushEventInstance(Event::UP_ARROW); break;}
            case SDLK_w: {pushEventInstance(Event::UP_ARROW); break;}
            
            case SDLK_DOWN: {pushEventInstance(Event::DOWN_ARROW); break;}
            case SDLK_s: {pushEventInstance(Event::DOWN_ARROW); break;}
            
            case SDLK_LEFT: {pushEventInstance(Event::LEFT_ARROW); break;}
            case SDLK_a: {pushEventInstance(Event::LEFT_ARROW); break;}
            
            case SDLK_RIGHT: {pushEventInstance(Event::RIGHT_ARROW); break;}
            case SDLK_d: {pushEventInstance(Event::RIGHT_ARROW); break;}
            
            case SDLK_SPACE:{ pushEventInstance(Event::SPACE); break;}
            case SDLK_RETURN:{pushEventInstance(Event::ENTER); break;}
            case SDLK_ESCAPE:{pushEventInstance(Event::ESCAPE); break;}
            case SDLK_g:{pushEventInstance(Event::G); break;}
            case SDLK_v:{pushEventInstance(Event::V); break;}
            case SDLK_b:{pushEventInstance(Event::B); break;}
            case SDLK_n:{pushEventInstance(Event::N); break;}
            case SDLK_r:{pushEventInstance(Event::R); break;}
            default:{pushEventInstance(Event::NONE); break;}
        }
    }
    //if key was pressed and repeated
    else if(sdl_event_ptr->type == SDL_KEYDOWN && sdl_event_ptr->key.repeat >= 1)
    {
        switch(sdl_event_ptr->key.keysym.sym)
        {
            case SDLK_UP: {pushEventInstance(Event::UP_ARROW_REPEAT); break;}
            case SDLK_w: {pushEventInstance(Event::UP_ARROW_REPEAT); break;}
            
            case SDLK_DOWN: {pushEventInstance(Event::DOWN_ARROW_REPEAT); break;}
            case SDLK_s: {pushEventInstance(Event::DOWN_ARROW_REPEAT); break;}
            
            case SDLK_LEFT: {pushEventInstance(Event::LEFT_ARROW_REPEAT); break;}
            case SDLK_a: {pushEventInstance(Event::LEFT_ARROW_REPEAT); break;}
            
            case SDLK_RIGHT: {pushEventInstance(Event::RIGHT_ARROW_REPEAT); break;}
            case SDLK_d: {pushEventInstance(Event::RIGHT_ARROW_REPEAT); break;}
            
            case SDLK_SPACE:{ pushEventInstance(Event::SPACE_REPEAT); break;}
            default:{pushEventInstance(Event::NONE); break;}
        }
    }
    //if a key was released
    else if(sdl_event_ptr->type == SDL_KEYUP && sdl_event_ptr->key.repeat == 0)
    {
        switch(sdl_event_ptr->key.keysym.sym )//slow down dot if key is released
        {
            case SDLK_UP: {pushEventInstance(Event::UP_ARROW_RELEASE); break;}
            case SDLK_w: {pushEventInstance(Event::UP_ARROW_RELEASE); break;}
            
            case SDLK_DOWN: {pushEventInstance(Event::DOWN_ARROW_RELEASE); break;}
			case SDLK_s: {pushEventInstance(Event::DOWN_ARROW_RELEASE); break;}
			
            case SDLK_LEFT: {pushEventInstance(Event::LEFT_ARROW_RELEASE); break;}
			case SDLK_a: {pushEventInstance(Event::LEFT_ARROW_RELEASE); break;}
			
            case SDLK_RIGHT: {pushEventInstance(Event::RIGHT_ARROW_RELEASE); break;}
            case SDLK_d: {pushEventInstance(Event::RIGHT_ARROW_RELEASE); break;}
  
            case SDLK_SPACE:{ pushEventInstance(Event::SPACE_RELEASE); break;}
            default:{pushEventInstance(Event::NONE); break;}
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
				if(yDir == 0){pushEventInstance(Event::JOYSTICK_0_NULL);}
				if(yDir == -1){pushEventInstance(Event::JOYSTICK_0_LEFT);}
				if(yDir == 1){pushEventInstance(Event::JOYSTICK_0_RIGHT);}
			}
			else if(xDir == -1)
			{
				if(yDir == 0){pushEventInstance(Event::JOYSTICK_0_LEFT);}
				if(yDir == -1){pushEventInstance(Event::JOYSTICK_0_DOWN_LEFT);}
				if(yDir == 1){pushEventInstance(Event::JOYSTICK_0_UP_LEFT);}
			}
			else if(xDir == 1)
			{
				if(yDir == 0){pushEventInstance(Event::JOYSTICK_0_RIGHT);}
				if(yDir == -1){pushEventInstance(Event::JOYSTICK_0_DOWN_RIGHT);}
				if(yDir == 1){pushEventInstance(Event::JOYSTICK_0_UP_RIGHT);}
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
				pushEventInstance(Event::JOYSTICK_0_HAT_UP_LEFT);
			}
			
			else if(sdl_event_ptr->jhat.value == SDL_HAT_RIGHTUP)
			{
				pushEventInstance(Event::JOYSTICK_0_HAT_UP_RIGHT);
			}
			
			else if(sdl_event_ptr->jhat.value == SDL_HAT_UP)
			{
				pushEventInstance(Event::JOYSTICK_0_HAT_UP);
			}
			
			else if(sdl_event_ptr->jhat.value == SDL_HAT_LEFT)
			{
				pushEventInstance(Event::JOYSTICK_0_HAT_LEFT);
			}
			
			else if(sdl_event_ptr->jhat.value == SDL_HAT_RIGHT)
			{
				pushEventInstance(Event::JOYSTICK_0_HAT_RIGHT);
			}
			
			else if(sdl_event_ptr->jhat.value == SDL_HAT_LEFTDOWN)
			{
				pushEventInstance(Event::JOYSTICK_0_HAT_DOWN_LEFT);
			}
			
			else if(sdl_event_ptr->jhat.value == SDL_HAT_RIGHTDOWN)
			{
				pushEventInstance(Event::JOYSTICK_0_HAT_DOWN_RIGHT);
			}
			
			else if(sdl_event_ptr->jhat.value == SDL_HAT_DOWN)
			{
				pushEventInstance(Event::JOYSTICK_0_HAT_DOWN);
			}
			
			else if(sdl_event_ptr->jhat.value == SDL_HAT_CENTERED)
			{
				pushEventInstance(Event::JOYSTICK_0_HAT_NULL);
			}
			else
			{
				pushEventInstance(Event::NONE);
			}
		}
		else if( sdl_event_ptr->jhat.which == 1 )
		{
			//joystick hat
			if( sdl_event_ptr->jhat.value == SDL_HAT_LEFTUP )
			{
				pushEventInstance(Event::JOYSTICK_1_HAT_UP_LEFT);
			}
			
			else if(sdl_event_ptr->jhat.value == SDL_HAT_RIGHTUP)
			{
				pushEventInstance(Event::JOYSTICK_1_HAT_UP_RIGHT);
			}
			
			else if(sdl_event_ptr->jhat.value == SDL_HAT_UP)
			{
				pushEventInstance(Event::JOYSTICK_1_HAT_UP);
			}
			
			else if(sdl_event_ptr->jhat.value == SDL_HAT_LEFT)
			{
				pushEventInstance(Event::JOYSTICK_1_HAT_LEFT);
			}
			
			else if(sdl_event_ptr->jhat.value == SDL_HAT_RIGHT)
			{
				pushEventInstance(Event::JOYSTICK_1_HAT_RIGHT);
			}
			
			else if(sdl_event_ptr->jhat.value == SDL_HAT_LEFTDOWN)
			{
				pushEventInstance(Event::JOYSTICK_1_HAT_DOWN_LEFT);
			}
			
			else if(sdl_event_ptr->jhat.value == SDL_HAT_RIGHTDOWN)
			{
				pushEventInstance(Event::JOYSTICK_1_HAT_DOWN_RIGHT);
			}
			
			else if(sdl_event_ptr->jhat.value == SDL_HAT_DOWN)
			{
				pushEventInstance(Event::JOYSTICK_1_HAT_DOWN);
			}
			
			else if(sdl_event_ptr->jhat.value == SDL_HAT_CENTERED)
			{
				pushEventInstance(Event::JOYSTICK_1_HAT_NULL);
			}
			else
			{
				pushEventInstance(Event::NONE);
			}
		}
	}
	
    else{pushEventInstance(Event::NONE);}
}

void pushEventInstance(Event thisEvent){event_instances_queue.push(thisEvent);}
void popEventInstanceFromFront(){event_instances_queue.pop();}

Event& getEventInstanceFront(){return event_instances_queue.front();}

bool isEventQueueEmpty(){return event_instances_queue.empty();}

void clearEventsQueue()
{
    std::queue <Event> empty_queue;
    //swap with empty queue
    event_instances_queue.swap(empty_queue);
}
