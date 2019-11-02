#ifndef LTEXTURE_H
#define LTEXTURE_H

#include "globalvariables.h"
#include <stdio.h>
#include <string.h>
#include <iostream>
//Texture Wrapper class for future SDL projects that need multiple images rendered

/*This wrapper class code was originally from Lazy Foo' Productions
(http://lazyfoo.net/)*/

class LTexture
{
    public:
    LTexture();
    ~LTexture();

    void allowTextureTarget(bool status);

    bool loadFromRenderedText(std::string textureText, SDL_Color textColor,TTF_Font* lFont,SDL_Renderer* lRenderer);

    bool loadFromFile(std::string path,SDL_Renderer* lRenderer,SDL_Window* lWindow = nullptr, bool manipulate = false); //added new bool manipulate to enable/disable texture manipulation for a loaded texture
    void free(); //deallocate textures
    void setColor(Uint8 red, Uint8 green, Uint8 bluee); // set color modulation to texture

    void setBlendMode(SDL_BlendMode blending); //set blending for alpha modulation
    void setAlpha(Uint8 alpha); //set alpha modulation

    void render(int x, int y,SDL_Renderer* lRenderer,SDL_Rect* clip = nullptr); //render texture at certain point

    //Pixel Manipulation
    bool lockTexture(); //lock textuer to change it's pixels
    bool unlockTexture(); //update texture's pixels
    void* getPixels();
    int getPitch();

    int getWidth();
    int getHeight();


    private:
    //Actual hardware texture
    SDL_Texture* mTexture;
    void* mPixels;
    int mPitch;


    int mWidth;
    int mHeight;

    //whether to set texture as render target
    bool targetStatus;



};

#endif
