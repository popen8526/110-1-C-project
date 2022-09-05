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
#define OBJECT_H_INCLUDED

class obstacle{
	private:
        SDL_Rect mCollider;
        bool exist;
    public:
        virtual void render() = 0;
        virtual void init() = 0;
        virtual void reset()  = 0;
        virtual void set_false() = 0;
        virtual int get_y() = 0;
        virtual bool get_exist() = 0;
};

class Wood {
    friend class Balloon;
    private:
        const int height;
        SDL_Rect mCollider;
    public:
        Wood();
        Wood(int x,int y);
        ~Wood(){}
        void render();
        void reset();
        void operator+=(int t);
        void Init(int);
};

class Bat :public obstacle{
    friend class Balloon;
    private:
        SDL_Rect mCollider;
        bool exist;
    public:
        Bat();
        Bat(int x,int y);
        ~Bat(){}
        void render();
        void init();
        void reset();
        void set_false()    {exist = false;}
        int get_y()         {return mCollider.y;}
        bool get_exist()    {return exist;}
        void operator+=(int &t);
        void operator=(Bat &t);
};

class Shield :public obstacle{
    friend class Balloon;
    private:
        SDL_Rect mCollider;
        bool exist;
    public:
        Shield();
        ~Shield(){}
        void render();
        void init();
        void reset();
        void set_false()    {exist = false;}
        int get_y()         {return mCollider.y;}
        bool get_exist()    {return exist;}
        void operator+=(int t);
};

class Thunder
{
    friend class Balloon;
    private:
        bool strike;
        bool exist;
        int cnt;
        SDL_Rect mCollider;
    public:
        Thunder();
        Thunder& operator++();
        void set_true() {exist = true;}
        void reset();
        void render();
};
#endif // OBJECT_H_INCLUDED
