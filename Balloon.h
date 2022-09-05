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

#ifndef OBJECT_H_INCLUDED
#include "Object.h"
#endif // OBJECT_H_INCLUDED

#ifndef BALLOON_H_INCLUDED
#define BALLOON_H_INCLUDED

class Balloon {
	public:
		//The dimensions of the dot
		static const int BALLOON_WIDTH = 60;
		static const int BALLOON_HEIGHT = 125;

		//Maximum axis velocity of the dot
		static const int BALLOON_VEL = 4;
		int lives;

		//Initializes the variables
		Balloon();
		~Balloon(){};

		//Takes key presses and adjusts the dot's velocity
		void handleEvent( SDL_Event& e );

		//Moves the dot and checks collision
		int move( Wood walls[3][3],Bat bat, Thunder flash, Shield shield);
        int get_y() {return mCollider.y;}

		void render();
		void protected_render();
		void reset();

	private:
		//The X and Y offsets of the dot
        SDL_Rect mCollider;

        int mPosX, mPosY;
        int mVelX, mVelY;
		double degrees;
};


#endif // BALLOON_H_INCLUDED
