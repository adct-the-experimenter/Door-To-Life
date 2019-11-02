#include "LTexture.h"

/*This wrapper class code was originally from Lazy Foo' Productions
(http://lazyfoo.net/)*/

LTexture::LTexture()
{
    /*This piece of code was originally from Lazy Foo' Productions
(http://lazyfoo.net/)*/
    //Initialize
	mTexture = nullptr;
	mWidth = 0;
	mHeight = 0;
	mPixels = nullptr;
	mPitch = 0;

	targetStatus = false;


}

LTexture::~LTexture()
{
    free();
}


bool LTexture::loadFromRenderedText(std::string textureText,SDL_Color textColor, TTF_Font* lFont,SDL_Renderer* lRenderer)
{
    //Get rid of preexisting texture
	free();

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid( lFont, textureText.c_str(), textColor );
	if( textSurface == nullptr )
	{
		printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
	}
	else
	{
		//Create texture from surface pixels
        mTexture = SDL_CreateTextureFromSurface( lRenderer, textSurface );
		if( mTexture == nullptr )
		{
			printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface( textSurface );
	}
	return mTexture != nullptr;
}


void LTexture::allowTextureTarget(bool status)
{
    targetStatus = status;
}


bool LTexture::loadFromFile(std::string path,SDL_Renderer* lRenderer,SDL_Window* lWindow, bool manipulate)
{
    /*This piece of code was originally from Lazy Foo' Productions
(http://lazyfoo.net/)*/
    //Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = nullptr;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == nullptr )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	//No Texture manipulation
	else if(manipulate == false && lWindow == nullptr)
    {
//Color key image
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( lRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
			return false;
		}
		else
		{
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;

			//make newTexture a target texture to ber rendered over if targetStatus is true
			if(targetStatus == true)
			{
			    SDL_SetRenderTarget(lRenderer,newTexture);
			}
		}
    }

	//Texture manipulation
	else if(manipulate == true && lWindow != nullptr)
	{
		//Convert surface to display format
		SDL_Surface* formattedSurface = SDL_ConvertSurface( loadedSurface, SDL_GetWindowSurface( lWindow )->format,0 );
		if( formattedSurface == NULL )
		{
			printf( "Unable to convert loaded surface to display format! SDL Error: %s\n", SDL_GetError() );
		}
		else
		{
			//Create blank streamable texture
			if(targetStatus == false)
			{
			    newTexture = SDL_CreateTexture( lRenderer, SDL_GetWindowPixelFormat( lWindow ), SDL_TEXTUREACCESS_STREAMING , formattedSurface->w, formattedSurface->h );
			}
			else if(targetStatus == true)
			{
			    newTexture = SDL_CreateTexture( lRenderer, SDL_GetWindowPixelFormat( lWindow ), SDL_TEXTUREACCESS_TARGET, formattedSurface->w, formattedSurface->h );
			    std::cout << " Texture created with target flag! \n";
			}

			if( newTexture == nullptr )
			{
				printf( "Unable to create blank texture! SDL Error: %s\n", SDL_GetError() );
			}
			else
			{
				//Lock texture for manipulation
				SDL_LockTexture( newTexture, NULL, &mPixels, &mPitch );

				//Copy loaded/formatted surface pixels
				memcpy( mPixels, formattedSurface->pixels, formattedSurface->pitch * formattedSurface->h );

				//Unlock texture to update
				SDL_UnlockTexture( newTexture );
				mPixels = NULL;

				//Get image dimensions
				mWidth = formattedSurface->w;
				mHeight = formattedSurface->h;

                //make newTexturea target texture to be rendered over if targetStatus is true
                if(targetStatus == true)
                {

                    SDL_SetRenderTarget(lRenderer,newTexture);
                    std::cout << "render target set! \n";
                }
			}
		}
        //Get rid of old formatted surface
        SDL_FreeSurface( formattedSurface );

	}
	//Get rid of old loaded surface
    SDL_FreeSurface( loadedSurface );


	//Return success
	mTexture = newTexture;
	return mTexture != NULL;

}

void LTexture::free()
{
    /*This piece of code was originally from Lazy Foo' Productions
(http://lazyfoo.net/)*/
    //Free texture if it exists
	if( mTexture != NULL )
	{
		SDL_DestroyTexture( mTexture );
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
		mPixels = NULL;
		mPitch = 0;
	}
}

void LTexture::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
    /*This piece of code was originally from Lazy Foo' Productions
(http://lazyfoo.net/)*/
    //modulate texture
    SDL_SetTextureColorMod(mTexture,red,green,blue);
}

void LTexture::setBlendMode(SDL_BlendMode blending)
{
    /*This piece of code was originally from Lazy Foo' Productions
(http://lazyfoo.net/)*/
    SDL_SetTextureBlendMode(mTexture,blending); //set blending function
}

void LTexture::setAlpha(Uint8 alpha)
{
    /*This piece of code was originally from Lazy Foo' Productions
(http://lazyfoo.net/)*/
    SDL_SetTextureAlphaMod(mTexture, alpha); //modulate texture alpha
}

void LTexture::render(int x, int y,SDL_Renderer* lRenderer, SDL_Rect* clip)
{
    //set rendering space and render to screen
    SDL_Rect renderQuad = {x,y,mWidth,mHeight}; //destination recctangle
    //SDL clip rendering dimensions
    if(clip != NULL)
    {
        //std::cout << "clip address passed is not NULL! Success!";
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }
    SDL_RenderCopy(lRenderer,mTexture,clip,&renderQuad);

    //std::cout<< "object rendered! \n";
}

int LTexture::getWidth()
{
    
    return mWidth;
}

int LTexture::getHeight()
{
    return mHeight;
}

bool LTexture::lockTexture()
{
    /*This piece of code was originally from Lazy Foo' Productions
(http://lazyfoo.net/)*/
	bool success = true;

	//Texture is already locked
	if( mPixels != NULL )
	{
		printf( "Texture is already locked!\n" );
		success = false;
	}
	//Lock texture
	else
	{
		if( SDL_LockTexture( mTexture, NULL, &mPixels, &mPitch ) != 0 )
		{
			printf( "Unable to lock texture! %s\n", SDL_GetError() );
			success = false;
		}
	}

	return success;
}

bool LTexture::unlockTexture()
{
    /*This piece of code was originally from Lazy Foo' Productions
(http://lazyfoo.net/)*/
	bool success = true;

	//Texture is not locked
	if( mPixels == NULL )
	{
		printf( "Texture is not locked!\n" );
		success = false;
	}
	//Unlock texture
	else
	{
		SDL_UnlockTexture( mTexture );
		mPixels = NULL;
		mPitch = 0;
	}

	return success;
}

void* LTexture::getPixels()
{
    /*This piece of code was originally from Lazy Foo' Productions
(http://lazyfoo.net/)*/
	return mPixels;
}

int LTexture::getPitch()
{
    /*This piece of code was originally from Lazy Foo' Productions
(http://lazyfoo.net/)*/
	return mPitch;
}
