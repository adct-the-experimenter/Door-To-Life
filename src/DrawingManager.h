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
	
	//pointers to renderers
	void SetPointerToRendererOne(SDL_Renderer* renderer);
	void SetPointerToRendererTwo(SDL_Renderer* renderer);
	void SetPointerToRendererThree(SDL_Renderer* renderer);
	void SetPointerToRendererFour(SDL_Renderer* renderer);
	
	
	SDL_Renderer* GetPointerToRendererOne();
	SDL_Renderer* GetPointerToRendererTwo();
	SDL_Renderer* GetPointerToRendererThree();
	SDL_Renderer* GetPointerToRendererFour();
	
private:
	
	
	//support rendering to 4 windows at most for now
	
	SDL_Renderer* gRenderer_one_ptr;
	SDL_Renderer* gRenderer_two_ptr;
	SDL_Renderer* gRenderer_three_ptr;
	SDL_Renderer* gRenderer_four_ptr;
	
	SDL_Rect* camera_one_ptr;
	SDL_Rect* camera_two_ptr;
	SDL_Rect* camera_three_ptr;
	SDL_Rect* camera_four_ptr;
	
};

#endif
