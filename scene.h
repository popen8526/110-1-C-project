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
#include "LTexture.h"
#endif // LTEXTURE_H_INCLUDED

#ifndef SCENE_H_INCLUDED
#define SCENE_H_INCLUDED

class Sound_effect
{
	public:
		void play_music(int index) const;
		void pause_and_resume() const;
		void stopmusic() const;
};

class scene
{
    public:
        //counter
		int count;
	protected:
		SDL_Rect subtitle[8];
		SDL_Rect Background;
		//Main loop flag
		bool operating_quit;
	public:
		scene();
		//Event handler
		SDL_Event e;
		virtual void operating(LTexture &preface_background,LTexture &preface,int index);
		//composition
		const Sound_effect soundtrack;
};

class preface_scene: public scene
{
	private:
		//story or challenge
		int sc;
		SDL_Rect frame_f;
		SDL_Rect frame_t;
	public:
		void setsc(int i)   {sc = i;}
		int getsc() {return sc;}
		preface_scene();
		void interface_operating();
        void rules_operating();
		void operating(LTexture &preface_background,LTexture &preface,int index);
};

#endif // SCENE_H_INCLUDED
