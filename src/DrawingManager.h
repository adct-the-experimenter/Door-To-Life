#ifndef DRAWING_MANAGER_H
#define DRAWING_MANAGER_H

//for platform-specific SDL2 libraries
#include "globalvariables.h" 



class DrawingManager
{

public: 
	
	DrawingManager();
	~DrawingManager();
	
	
	//pointers to cameras
	
	void SetPointerToCameraOne(SDL_Rect* camera);
	void SetPointerToCameraTwo(SDL_Rect* camera);
	void SetPointerToCameraThree(SDL_Rect* camera);
	void SetPointerToCameraFour(SDL_Rect* camera);
	
	SDL_Rect* GetPointerToCameraOne();
	SDL_Rect* GetPointerToCameraTwo();
	SDL_Rect* GetPointerToCameraThree();
	SDL_Rect* GetPointerToCameraFour();
	
	//pointer to renderers
	void SetPointerToRenderer(SDL_Renderer* renderer);
	SDL_Renderer* GetPointerToRenderer();
	
	
	void SetMultiplePlayersBool(bool state);
	bool GetMultiplePlayersBool();
	
	void SetNumberOfPlayers(int num);
	int GetNumberOfPlayers();
	
private:
	
	
	//support rendering to 4 windows at most for now
	SDL_Renderer* m_renderer_ptr;
	
	
	SDL_Rect* camera_one_ptr;
	SDL_Rect* camera_two_ptr;
	SDL_Rect* camera_three_ptr;
	SDL_Rect* camera_four_ptr;
	
	bool draw_multiple_players_bool;
	int m_num_players;
};

#endif
