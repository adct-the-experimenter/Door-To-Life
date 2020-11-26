#ifndef HEALTHBAR_H
#define HEALTHBAR_H

#include "LTexture.h"

class HealthBar
{
    
public:
    //constructor
    HealthBar();
    //destructor
    ~HealthBar();
    
    //friend function to setup a texture for health bar
    friend bool loadMedia_HealthBar(LTexture* healthTex,
                         SDL_Renderer* gRenderer);
    //friend function to free a texture for health bar
    friend void freeMedia_HealthBar(LTexture* healthTex);
    
    //function to set health clip dimensions
    void setHealthRectClip(std::int16_t& x,std::int16_t& y,
                            std::int16_t& w, std::int16_t& h);
    
    //function to set container clip dimensions
    void setContainerRectClip(std::int16_t& x,std::int16_t& y,
                            std::int16_t& w, std::int16_t& h);
    
    //function to update health
    void updateHealthBar(std::int16_t& health);
    
    //function to render health container and bar.
    void render(std::int16_t& x, std::int16_t& y, SDL_Renderer* gRenderer);
    
    void render(SDL_Renderer* gRenderer);
    
    //function to set pointers to health texture and container texture
    void setPointerToHealthTexture(LTexture* thisTexture);
    
    //function to set position of health bar
    void SetPosition(std::int16_t x, std::int16_t y);
    
private:
    //pointer to texture for health
    LTexture* healthTexture;
    
    //function to set rectangle clip for health based on current health
    void setHealthClip_FromHealth(std::int16_t& health);
    
    SDL_Rect containerClip;
    SDL_Rect healthClip;
    
    std::int16_t originalHealthWidth;
    std::int16_t originalHealthXPos;
    
    std::int16_t width_per_bar;
    std::int16_t health_per_bar;
    
    std::int16_t xPos;
    std::int16_t yPos;
};

#endif
