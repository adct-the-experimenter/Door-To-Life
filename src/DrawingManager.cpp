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


//renderers

void DrawingManager::SetPointerToRendererOne(SDL_Renderer* renderer){gRenderer_one_ptr = renderer;}
void DrawingManager::SetPointerToRendererTwo(SDL_Renderer* renderer){gRenderer_two_ptr = renderer;}
void DrawingManager::SetPointerToRendererThree(SDL_Renderer* renderer){gRenderer_three_ptr = renderer;}
void DrawingManager::SetPointerToRendererFour(SDL_Renderer* renderer){gRenderer_four_ptr = renderer;}


SDL_Renderer* DrawingManager::GetPointerToRendererOne(){return gRenderer_one_ptr;}
SDL_Renderer* DrawingManager::GetPointerToRendererTwo(){return gRenderer_two_ptr;}
SDL_Renderer* DrawingManager::GetPointerToRendererThree(){return gRenderer_three_ptr;}
SDL_Renderer* DrawingManager::GetPointerToRendererFour(){return gRenderer_four_ptr;}

void DrawingManager::SetMultiplePlayersBool(bool state){draw_multiple_players_bool = state;}
bool DrawingManager::GetMultiplePlayersBool(){return draw_multiple_players_bool;}

void DrawingManager::SetNumberOfPlayers(int num){m_num_players = num;}
int DrawingManager::GetNumberOfPlayers(){return m_num_players;}
