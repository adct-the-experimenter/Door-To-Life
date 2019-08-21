#include "healthbar.h"



//constructor
HealthBar::HealthBar()
{
    healthClip.x = 0; healthClip.y = 0;
    healthClip.w = 0; healthClip.h = 0;

    health_per_bar = 10;
}
//destructor
HealthBar::~HealthBar()
{
    
}

//friend function to setup a texture for health bar
bool loadMedia_HealthBar(LTexture* healthTex,
                         SDL_Renderer* gRenderer)
{
    bool success = true;
    
    std::string path = DATADIR_STR +  std::string("/Graphics/health-bar.png");
    //initialize
    if(!healthTex->loadFromFile(path,gRenderer))
    {
        success = false;
        printf("Failed to load health bar texture! \n");
    }
    
    return success;
}

//friend function to free a texture for health bar
void freeMedia_HealthBar(LTexture* healthTex)
{
    //free health texture
    healthTex->free();
}

//function to set pointers to health texture and container texture
void HealthBar::setPointerToHealthTexture(LTexture* thisTexture){healthTexture = thisTexture;}

//function to set health clip dimensions
void HealthBar::setHealthRectClip(std::int16_t& x,std::int16_t& y,
                        std::int16_t& w, std::int16_t& h)
{
    healthClip.x = x;
    healthClip.y = y;
    healthClip.w = w;
    healthClip.h = h;
    originalHealthWidth = w;
    originalHealthXPos = x;
    
    //convert current health into rectangle clip height
    width_per_bar = originalHealthWidth / 10;
    
}

void HealthBar::setContainerRectClip(std::int16_t& x,std::int16_t& y,
                            std::int16_t& w, std::int16_t& h)
{
    containerClip.x = x;
    containerClip.y = y;
    containerClip.w = w;
    containerClip.h = h;
}

//function to update health
void HealthBar::updateHealthBar(std::int16_t& health)
{
    HealthBar::setHealthClip_FromHealth(health);
}

//function to set rectangle clip for health
void HealthBar::setHealthClip_FromHealth(std::int16_t& health)
{
    
    //health * (bar / health) * (width / bar) = width to cut
    std::int16_t  healthWidthToCut = ( (100 - health) / health_per_bar) * width_per_bar;
    std::int16_t newHealthWidth = originalHealthWidth - healthWidthToCut;

    //set new height for health clip
    healthClip.w = newHealthWidth;
}

//function to render health container and bar.
void HealthBar::render(std::int16_t& x, std::int16_t& y, SDL_Renderer* gRenderer)
{
    std::int16_t containerX = x - containerClip.w;
    if(containerX < 0){containerX = 0;}
    std::int16_t containerY = y - containerClip.h;
    if(containerY < 0){containerY = 0;}
    std::int16_t healthX = containerX + 6;
    std::int16_t healthY = containerY + 6;
    //render container clip
    healthTexture->render(containerX,containerY,gRenderer,&containerClip);
    //render health clip
    healthTexture->render(healthX,healthY,gRenderer,&healthClip);
}