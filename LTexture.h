#ifndef HEADERS
#define HEADERS
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"
#include <stdio.h>
#include <string>
#include <ctime>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "SDL2/SDL_ttf.h"
#endif

#ifndef LTEXTURE_H_INCLUDED
#define LTEXTURE_H_INCLUDED

//Texture wrapper class
class LTexture {
	public:
		//Initializes variables
		LTexture();

		//Deallocates memory
		~LTexture();

		//Loads image at specified path
		bool loadFromFile( std::string path );

//#if defined(SDL_TTF_MAJOR_VERSION)
		//Creates image from font string
		bool loadFromRenderedText( std::string textureText, SDL_Color textColor );
//#endif

		//Deallocates texture
		void free();

		//Set color modulation
		void setColor( Uint8 red, Uint8 green, Uint8 blue );

		//Set blending
		void setBlendMode( SDL_BlendMode blending );

		//Set alpha modulation
		void setAlpha( Uint8 alpha );

		//Renders texture at given point
		void render( int x, int y, SDL_Rect* clip, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );
		void render2( int x, int y, SDL_Rect* clip );
		//Gets image dimensions
		int getWidth();
		int getHeight();

		SDL_Texture* mTexture;
	private:
		//The actual hardware texture
		//SDL_Texture* mTexture;

		//Image dimensions
		int mWidth;
		int mHeight;
};

#endif // LTEXTURE_H_INCLUDED
