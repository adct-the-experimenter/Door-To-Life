#include "DrawingManager.h"

DrawingManager::DrawingManager()
{
	draw_multiple_players_bool = false;
	m_num_players = 1;
	
	
}

DrawingManager::~DrawingManager()
{
	
}


//cameras

void DrawingManager::SetPointerToCameraOne(SDL_Rect* camera){camera_one_ptr = camera;}
void DrawingManager::SetPointerToCameraTwo(SDL_Rect* camera){camera_two_ptr = camera;}
void DrawingManager::SetPointerToCameraThree(SDL_Rect* camera){camera_three_ptr = camera;}
void DrawingManager::SetPointerToCameraFour(SDL_Rect* camera){camera_four_ptr = camera;}

SDL_Rect* DrawingManager::GetPointerToCameraOne(){return camera_one_ptr;}
SDL_Rect* DrawingManager::GetPointerToCameraTwo(){return camera_two_ptr;}
SDL_Rect* DrawingManager::GetPointerToCameraThree(){return camera_three_ptr;}
SDL_Rect* DrawingManager::GetPointerToCameraFour(){return camera_four_ptr;}

void DrawingManager::InitViewportsForThisNumberOfPlayers(int num, int screen_width, int screen_height)
{
	switch(num)
	{
		case 1:
		{
			player1Viewport.x = 0; player1Viewport.y = 0;
			player1Viewport.w = screen_width; player1Viewport.h = screen_height;  
			break;
		}
		case 2:
		{
			player1Viewport.x = 0; player1Viewport.y = 0;
			player1Viewport.w = screen_width / 2; player1Viewport.h = screen_height; 
			
			player2Viewport.x = screen_width / 2; player2Viewport.y = 0;
			player2Viewport.w = screen_width / 2; player2Viewport.h = screen_height;
			break;
		}
		case 3:
		{
			player1Viewport.x = 0; player1Viewport.y = 0;
			player1Viewport.w = screen_width / 2; player1Viewport.h = screen_height / 2; 
			
			player2Viewport.x = screen_width / 2; player2Viewport.y = 0;
			player2Viewport.w = screen_width / 2; player2Viewport.h = screen_height / 2;
			
			player3Viewport.x = screen_width / 4; player3Viewport.y = screen_height / 2;
			player3Viewport.w = screen_width / 2; player3Viewport.h = screen_height / 2; 
			break;
		}
		case 4:
		{
			player1Viewport.x = 0; player1Viewport.y = 0;
			player1Viewport.w = screen_width / 2; player1Viewport.h = screen_height / 2; 
			
			player2Viewport.x = screen_width / 2; player2Viewport.y = 0;
			player2Viewport.w = screen_width / 2; player2Viewport.h = screen_height / 2;
			
			player3Viewport.x = 0; player3Viewport.y = screen_height / 2;
			player3Viewport.w = screen_width / 2; player3Viewport.h = screen_height / 2; 
			
			player4Viewport.x = screen_width / 2; player4Viewport.y = screen_height / 2;
			player4Viewport.w = screen_width / 2; player4Viewport.h = screen_height / 2; 
			break;
		}
		
	}
}

void DrawingManager::InitCamerasForThisNumberOfPlayers(int num, int screen_width, int screen_height)
{
	switch(num)
	{
		case 1:
		{
			camera_one_ptr->w = screen_width; camera_one_ptr->h = screen_height;
			break;
		}
		case 2:
		{
			camera_one_ptr->w = screen_width / 2; camera_one_ptr->h = screen_height; 
			camera_two_ptr->w = screen_width / 2; camera_two_ptr->h = screen_height;
			break;
		}
		case 3:
		{
			camera_one_ptr->w = screen_width / 2; camera_one_ptr->h = screen_height / 2; 
			camera_two_ptr->w = screen_width / 2; camera_two_ptr->h = screen_height / 2; 
			camera_three_ptr->w = screen_width / 2; camera_three_ptr->h = screen_height / 2; 
			break;
		}
		case 4:
		{
			camera_one_ptr->w = screen_width / 2; camera_one_ptr->h = screen_height / 2; 
			camera_two_ptr->w = screen_width / 2; camera_two_ptr->h = screen_height / 2; 
			camera_three_ptr->w = screen_width / 2; camera_three_ptr->h = screen_height / 2; 
			camera_four_ptr->w = screen_width / 2; camera_four_ptr->h = screen_height / 2; 
			break;
		}
		
	}
}

void DrawingManager::SetToRenderViewPortPlayer1()
{
	SDL_RenderSetViewport( m_renderer_ptr, &player1Viewport );
}

void DrawingManager::SetToRenderViewPortPlayer2()
{
	SDL_RenderSetViewport( m_renderer_ptr, &player2Viewport );
}

void DrawingManager::SetToRenderViewPortPlayer3()
{
	SDL_RenderSetViewport( m_renderer_ptr, &player3Viewport );
}

void DrawingManager::SetToRenderViewPortPlayer4()
{
	SDL_RenderSetViewport( m_renderer_ptr, &player4Viewport );
}

//renderers

void DrawingManager::SetPointerToRenderer(SDL_Renderer* renderer){m_renderer_ptr = renderer;}

SDL_Renderer* DrawingManager::GetPointerToRenderer(){return m_renderer_ptr;}

void DrawingManager::SetMultiplePlayersBool(bool state){draw_multiple_players_bool = state;}
bool DrawingManager::GetMultiplePlayersBool(){return draw_multiple_players_bool;}

void DrawingManager::SetNumberOfPlayers(int num){m_num_players = num;}
int DrawingManager::GetNumberOfPlayers(){return m_num_players;}

