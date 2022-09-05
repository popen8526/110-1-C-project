/*This source code copyrighted by Lazy Foo' Productions (2004-2020)
and may not be redistributed without written permission.*/

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

#include "LTexture.h"
#include "Object.h"
#include "Balloon.h"
#include "scene.h"

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
//Screen dimension constants
const int SCREEN_WIDTH = 500;
const int SCREEN_HEIGHT = 750;
enum Music_list
{
	lightning,boom,scream,Fukakouryoku,safe_sad2,moon14,safe_sad1,toss,selfact,comethru,bgm,happy
};
//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//Box collision detector
bool checkCollision( SDL_Rect a, SDL_Rect b );

int Game(Balloon &, Wood **, Bat &, Thunder &, int &, int);

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Scene textures
LTexture gFooTexture[5];
LTexture gBackgroundTexture;
LTexture gEndbackgroundTexture;
LTexture gWoodTexture;
LTexture gBatTexture;
LTexture gStrikeTexture;
LTexture gWarningTexture;
LTexture gShieldTexture;
LTexture gShield2Texture;
LTexture gLivesTexture;
LTexture gcRecordFontTexture;
LTexture gcRecordFontTexture2;
LTexture gsRecordFontTexture;
LTexture gEndFontTexture[6];
LTexture preface;
LTexture preface_background;
LTexture d_s_subtitle[5];
LTexture dead_scene[5];
LTexture success_subtitle;
LTexture success_scene;
LTexture challenge_mode;
LTexture c_m_subtitle;
LTexture red_hat;
LTexture preface_rules[2];
LTexture interface[3];
TTF_Font *gFont = NULL;

Mix_Music *gMusic[15];

bool x = false;
//The music that will be played

bool init() {
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "Sadness balloon", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG(orjpg) loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_mage Error: %s\n", IMG_GetError() );
					success = false;
				}

				//Initialize SDL_mixer
				if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
				{
					printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
					success = false;
				}
				if( TTF_Init() == -1 )
				{
					printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia() {
	//Loading success flag
	bool success = true;

	//Load press texture
	if( !gFooTexture[0].loadFromFile( "Media/image/balloon-1.png" ) ) {
		printf( "Failed to load Foo' texture image!\n" );
		success = false;
	}
	if( !gFooTexture[1].loadFromFile( "Media/image/balloon-2.png" ) ) {
		printf( "Failed to load Foo' texture image!\n" );
		success = false;
	}
	if( !gFooTexture[2].loadFromFile( "Media/image/balloon-3.png" ) ) {
		printf( "Failed to load Foo' texture image!\n" );
		success = false;
	}
	if( !gFooTexture[3].loadFromFile( "Media/image/balloon-4.png" ) ) {
		printf( "Failed to load Foo' texture image!\n" );
		success = false;
	}
	if( !gFooTexture[4].loadFromFile( "Media/image/balloon-5.png" ) ) {
		printf( "Failed to load Foo' texture image!\n" );
		success = false;
	}
    if( !gStrikeTexture.loadFromFile( "Media/image/thunder.png" ) ) {
		printf( "Failed to load Foo' texture image!\n" );
		success = false;
	}
	if( !gWarningTexture.loadFromFile( "Media/image/Warning.png" ) ) {
		printf( "Failed to load Foo' texture image!\n" );
		success = false;
	}
	if( !gBackgroundTexture.loadFromFile( "Media/image/forest-1.png" ) ) {
		printf( "Failed to load background texture image!\n" );
		success = false;
	}
    if( !gEndbackgroundTexture.loadFromFile( "Media/image/end_background.jpg" ) ) {
		printf( "Failed to load background texture image!\n" );
		success = false;
	}
	if( !gWoodTexture.loadFromFile( "Media/image/wood-4.png"  )) {
		printf( "Failed to load texture image!\n" );
		success = false;
	}

	if( !gBatTexture.loadFromFile( "Media/image/bat-1.png"  )) {
		printf( "Failed to load texture image!\n" );
		success = false;
	}

    if( !gShieldTexture.loadFromFile( "Media/image/shield.png"  )) {
		printf( "Failed to load texture image!\n" );
		success = false;
	}

    if( !gShield2Texture.loadFromFile( "Media/image/shield2.png"  )) {
		printf( "Failed to load texture image!\n" );
		success = false;
	}

	if( !gLivesTexture.loadFromFile( "Media/image/Lives.png"  )) {
		printf( "Failed to load texture image!\n" );
		success = false;
	}
	//Load background texture
	if( !preface_rules[0].loadFromFile( "Media/image/s_m_rule.png" ) )
	{
		printf( "Failed to load forest texture!\n" );
		success = false;
	}
	if( !preface_rules[1].loadFromFile( "Media/image/c_m_rule.png" ) )
	{
		printf( "Failed to load forest texture!\n" );
		success = false;
	}
	if( !preface_background.loadFromFile( "Media/image/forest-1.png" ) )
	{
		printf( "Failed to load forest texture!\n" );
		success = false;
	}
	if( !dead_scene[0].loadFromFile( "Media/image/bed.png" ) )
	{
		printf( "Failed to load bed texture!\n" );
		success = false;
	}
	if( !dead_scene[1].loadFromFile( "Media/image/sleep.png" ) )
	{
		printf( "Failed to load sleep texture!\n" );
		success = false;
	}
	if( !dead_scene[2].loadFromFile( "Media/image/x_mas.png" ) )
	{
		printf( "Failed to load x_mas texture!\n" );
		success = false;
	}
	if( !dead_scene[3].loadFromFile( "Media/image/101.png" ) )
	{
		printf( "Failed to load 101 texture!\n" );
		success = false;
	}
	if( !dead_scene[4].loadFromFile( "Media/image/mind.png" ) )
	{
		printf( "Failed to load mind texture!\n" );
		success = false;
	}
	if( !success_scene.loadFromFile( "Media/image/sky.jpg" ) )
	{
		printf( "Failed to load sky texture!\n" );
		success = false;
	}
	if( !challenge_mode.loadFromFile( "Media/image/soldier.png" ) )
	{
		printf( "Failed to load soldier texture!\n" );
		success = false;
	}
	//Load subtitle texture
	if( !preface.loadFromFile( "Media/image/preface.png" ) )
	{
		printf( "Failed to load preface texture!\n" );
		success = false;
	}
	if( !d_s_subtitle[0].loadFromFile( "Media/image/dss1.png" ) )
	{
		printf( "Failed to load dss1 texture!\n" );
		success = false;
	}
	if( !d_s_subtitle[1].loadFromFile( "Media/image/dss2.png" ) )
	{
		printf( "Failed to load dss2 texture!\n" );
		success = false;
	}
	if( !d_s_subtitle[2].loadFromFile( "Media/image/dss3.png" ) )
	{
		printf( "Failed to load dss3 texture!\n" );
		success = false;
	}
	if( !d_s_subtitle[3].loadFromFile( "Media/image/dss4.png" ) )
	{
		printf( "Failed to load dss4 texture!\n" );
		success = false;
	}
	if( !d_s_subtitle[4].loadFromFile( "Media/image/dss5.png" ) )
	{
		printf( "Failed to load dss5 texture!\n" );
		success = false;
	}
	if( !success_subtitle.loadFromFile( "Media/image/sss.png" ) )
	{
		printf( "Failed to load sss texture!\n" );
		success = false;
	}
	if( !c_m_subtitle.loadFromFile( "Media/image/c_m_subtitle.png" ) )
	{
		printf( "Failed to load c_m_subtitle texture!\n" );
		success = false;
	}
	if( !red_hat.loadFromFile( "Media/image/red_hat.png" ) )
	{
		printf( "Failed to load red_hat texture!\n" );
		success = false;
	}
	if( !interface[0].loadFromFile( "Media/image/s_b.png" ) )
	{
		printf( "Failed to load interface texture!\n" );
		success = false;
	}
	if( !interface[1].loadFromFile( "Media/image/s_m.png" ) )
	{
		printf( "Failed to load interface texture!\n" );
		success = false;
	}
	if( !interface[2].loadFromFile( "Media/image/c_m.png" ) )
	{
		printf( "Failed to load interface texture!\n" );
		success = false;
	}
	//Load music
	gMusic[0] = Mix_LoadMUS( "Media/music/lightning.mp3" );
	if( gMusic[0] == NULL )
	{
		printf( "Failed to load music0! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}
	gMusic[1] = Mix_LoadMUS( "Media/music/boom.mp3" );
	if( gMusic[1] == NULL )
	{
		printf( "Failed to load music1! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}
	gMusic[2] = Mix_LoadMUS( "Media/music/scream_new.mp3" );
	if( gMusic[2] == NULL )
	{
		printf( "Failed to load music2! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}
	gMusic[3] = Mix_LoadMUS( "Media/music/Fukakouryoku.mp3" );
	if( gMusic[3] == NULL )
	{
		printf( "Failed to load music3! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}
	gMusic[4] = Mix_LoadMUS( "Media/music/safe_sad2.mp3" );
	if( gMusic[4] == NULL )
	{
		printf( "Failed to load music4! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}
	gMusic[5] = Mix_LoadMUS( "Media/music/moon14.mp3" );
	if( gMusic[5] == NULL )
	{
		printf( "Failed to load music5! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}
	gMusic[6] = Mix_LoadMUS( "Media/music/safe_sad1.mp3" );
	if( gMusic[6] == NULL )
	{
		printf( "Failed to load music6! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}
	gMusic[7] = Mix_LoadMUS( "Media/music/toss.mp3" );
	if( gMusic[7] == NULL )
	{
		printf( "Failed to load music7! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}
	gMusic[8] = Mix_LoadMUS( "Media/music/selfact.mp3" );
	if( gMusic[8] == NULL )
	{
		printf( "Failed to load music8! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}
	gMusic[9] = Mix_LoadMUS( "Media/music/comethru.mp3" );
	if( gMusic[9] == NULL )
	{
		printf( "Failed to load music9! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}
	gMusic[10] = Mix_LoadMUS( "Media/music/bgm.mp3" );
	if( gMusic[10] == NULL )
	{
		printf( "Failed to load music10! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}
	gMusic[11] = Mix_LoadMUS( "Media/music/happy.mp3" );
	if( gMusic[11] == NULL )
	{
		printf( "Failed to load music9! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}

    //Open the font
    gFont = TTF_OpenFont( "Media/CollegiateFLF.ttf", 100 );
    if( gFont == NULL )
    {
        printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
        success = false;
    }
    else
    {
        SDL_Color textColor = { 0xFF, 0xFF, 0xFF };
        if( !gcRecordFontTexture2.loadFromRenderedText( "Current Score :", textColor ) )
        {
            printf( "Failed to render text texture!\n" );
            success = false;
        }
        if( !gsRecordFontTexture.loadFromRenderedText( "Lives Left :", textColor ) )
        {
            printf( "Failed to render text texture!\n" );
            success = false;
        }
    }

	//load other picture
	return success;
}



void close() {
	//Free loaded images
	for(int i=0;i<5;i++)
    {
        gFooTexture[i].free();
	}
	gBackgroundTexture.free();
	gWoodTexture.free();
	gBatTexture.free();
	gStrikeTexture.free();
	gWarningTexture.free();
	gShieldTexture.free();
	preface_background.free();
	preface.free();
	for(int i=0;i<5;i++)
	{
		dead_scene[i].free();
		d_s_subtitle[i].free();
	}
	success_scene.free();
	success_subtitle.free();
	//Free the music
	Mix_FreeMusic( *gMusic );
	*gMusic = NULL;
	//Destroy window
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}

bool checkCollision( SDL_Rect a, SDL_Rect b) {
	//The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = a.x;
	rightA = a.x + a.w;
	topA = a.y;
	bottomA = a.y + a.h;

	//Calculate the sides of rect B
	leftB = b.x;
	rightB = b.x + b.w;
	topB = b.y;
	bottomB = b.y + b.h;

	//If any of the sides from A are outside of B
	if( bottomA <= topB ) {
		return false;
	}

	if( topA >= bottomB ) {
		return false;
	}

	if( rightA <= leftB ) {
		return false;
	}

	if( leftA >= rightB ) {
		return false;
	}

	//If none of the sides from A are outside B
	/*std::cout << a.x << ' ' << a.y << ' ' << a.w << ' ' << a.h << std::endl;
	std::cout << b.x << ' ' << b.y << ' ' << b.w << ' ' << b.h << std::endl;
	*/
	return true;
}


void save(int record)
{
    record=record/10;
	std::stringstream s2;
	s2.str("");
	s2.clear();
	std::string loadt;
	s2 << record;
	s2 >> loadt;
	std::string s1;
	std::ofstream outfile("Media/record-1.txt");
	s1.erase();
	s1 = loadt;
	outfile << s1 << std::endl;
	outfile.close();
}

void load(int &record){
	std::stringstream s2,s3;
	s3.str("");
	s3.clear();
	std::string s1;
	std::ifstream infile("Media/record-1.txt");
	getline(infile, s1,'\n');
	s3<<s1;
	s3>>record;
	infile.close();
}

bool beginning()
{
    preface_scene begin;
    scene c_m;
    begin.interface_operating();
    if(begin.getsc() == 1)
    {
        begin.rules_operating();
        begin.operating(preface_background, preface, safe_sad2);
        return true;
    }
    else if(begin.getsc() == 2)
    {
        begin.rules_operating();
        c_m.operating(challenge_mode, c_m_subtitle, Fukakouryoku);
        return false;
    }
    return false;
}

int c_m_ending(int score, int record)
{
    bool operating_quit = false;
    int value = 0;
    SDL_Event e;
    SDL_Rect Background = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    SDL_Color textColor = { 0xFF, 0xFF, 0xFF };
    std::stringstream string1;
    string1.str("");
    string1.clear();
    std::string show_score;
    string1 << score/10;
    string1 >> show_score;
    std::stringstream string2;
    string2.str("");
    string2.clear();
    std::string show_record;
    string2 << record;
    string2 >> show_record;
    SDL_Rect End[8];
    End[0] = {30,530,170,30};
    End[1] = {60,580,160,60};
    End[2] = {250,530,190,30};
    End[3] = {280,580,160,60};
    End[4] = {20,680,460,40};
    End[5] = {20,500,460,50};
    End[6] = {30,560,170,30};
    End[7] = {250,570,180,90};
    if( !gEndFontTexture[0].loadFromRenderedText( "Your Score: ", textColor ) )
    {
        printf( "Failed to render text texture!\n" );
    }
    if( !gEndFontTexture[1].loadFromRenderedText( show_score, textColor ) )
    {
        printf( "Failed to render text texture!\n" );
    }
    if( !gEndFontTexture[2].loadFromRenderedText( "Current Record: ", textColor ) )
    {
        printf( "Failed to render text texture!\n" );
    }
    if( !gEndFontTexture[3].loadFromRenderedText( show_record, textColor ) )
    {
        printf( "Failed to render text texture!\n" );
    }
    if( !gEndFontTexture[4].loadFromRenderedText( "Restart Press Z, Main Page Press X", textColor ) )
    {
        printf( "Failed to render text texture!\n" );
    }
    if( !gEndFontTexture[5].loadFromRenderedText( "Congratulations! New High Score!", textColor ) )
    {
        printf( "Failed to render text texture!\n" );
    }
    if(score/100 == 0)
    {
        End[1].w = 40;
        End[1].x = 100;
        End[7].w = 45;
    }
    else if(score/1000 == 0)
    {
        End[1].w = 80;
        End[1].x = 80;
        End[7].w = 90;
    }
    else if(score/10000 == 0)
    {
        End[1].w = 120;
        End[1].x = 60;
        End[7].w = 135;
    }
    if(record/10 == 0)
    {
        End[3].w = 40;
        End[3].x = 320;
    }
    else if(record/100 == 0)
    {
        End[3].w = 80;
        End[3].x = 300;
    }
    else if(record/1000 == 0)
    {
        End[3].w = 120;
        End[3].x = 280;
    }
    if(score/10 < record)
    {
		//While application is running
		while( (!operating_quit))
		{
			//Handle events on queue
			while( SDL_PollEvent( &e ) != 0 )
			{
				//User requests quit
				if( e.type == SDL_QUIT )
				{
					operating_quit = true;
					x = true;
				}
				else if( e.type == SDL_KEYDOWN )
				{
					switch( e.key.keysym.sym )
					{
						case SDLK_z:
                            operating_quit = true;
                            value = 0;
                            break;
						case SDLK_x:
						    operating_quit = true;
                            value = 1;
                            break;
					}
				}
			}
			//Clear screen
            SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
            SDL_RenderClear( gRenderer );
            gEndbackgroundTexture.render(0, 0, &Background);
            //"Your Score: "
            gEndFontTexture[0].render(30,530,&End[0]);
            //show_score
            gEndFontTexture[1].render(End[1].x,End[1].y,&End[1]);
            //"Current Record: "
            gEndFontTexture[2].render(250,530,&End[2]);
            //show_record
            gEndFontTexture[3].render(End[3].x,End[3].y,&End[3]);
            //"Restart Press Z, Main Page Press X"
            gEndFontTexture[4].render(20,680,&End[4]);

            SDL_RenderPresent( gRenderer );
			if(x) close();
		}
    }
    else
    {
        save(score);
        //While application is running
		while( (!operating_quit))
		{
			//Handle events on queue
			while( SDL_PollEvent( &e ) != 0 )
			{
				//User requests quit
				if( e.type == SDL_QUIT )
				{
					operating_quit = true;
					x = true;
				}
				else if( e.type == SDL_KEYDOWN )
				{
					switch( e.key.keysym.sym )
					{
						case SDLK_z:
                            operating_quit = true;
                            value = 0;
                            break;
						case SDLK_x:
						    operating_quit = true;
                            value = 1;
                            break;
					}
				}
			}
			//Clear screen
            SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
            SDL_RenderClear( gRenderer );
            gEndbackgroundTexture.render(0, 0, &Background);
            //"Congratulations! New High Score!"
            gEndFontTexture[5].render(20,500,&End[5]);
            //"Your Score: "
            gEndFontTexture[0].render(30,560,&End[6]);
            //show_score
            gEndFontTexture[1].render(250,570,&End[7]);
            //"Restart Press Z, Main Page Press X"
            gEndFontTexture[4].render(20,680,&End[4]);

            SDL_RenderPresent( gRenderer );
			if(x) close();
		}
    }
    return value;
}

int main(int argc, char* args[]) {

	//Start up SDL and create window
	if( !init() ) {
		printf( "Failed to initialize!\n" );
	}
	else {
		//Load media
		if( !loadMedia() ) {
			printf( "Failed to load media!\n" );
		}
		else {
			//Main loop flag
            bool quit = false;
            bool pass = false;
            bool music_playing = true;
            srand(time(0));
            SDL_Event e;
            Balloon balloon;
            //Set the wall
            Wood walls[3][3];
            Bat bat;
            Thunder flash;
            Shield shield;
            int clock = 0, speed=1;
            int score=0,direction=1;
            bool protect=0;
            bool touched = false;
            SDL_Rect endline = {0, 0, SCREEN_WIDTH, 10};
            int shieldcount=0;
            while(1)
            {
                if(beginning())
                {
                    scene mid[5];
                    scene end;
                    //While application is running
                    Uint32 time0 = SDL_GetTicks();
                        while( !quit ) {
                            if((SDL_GetTicks()-time0)%23 == 0)
                            {
                                while( SDL_PollEvent( &e ) != 0 ) {
                                        //User requests quit
                                        if( e.type == SDL_QUIT ) {
                                            quit = true;
                                            x = true;
                                        }
                                        //Handle input for the dot
                                        balloon.handleEvent( e );
                                        if(e.type == SDL_KEYDOWN)
                                        {
                                            switch( e.key.keysym.sym )
                                            {
                                                case SDLK_m:
                                                mid[4-balloon.lives].soundtrack.pause_and_resume();
                                                if(Mix_PlayingMusic() == 0) music_playing = true;
                                                else                        music_playing = false;
                                            }
                                        }

                                    }
                                if(music_playing)   mid[4-balloon.lives].soundtrack.play_music(bgm);
                                if(x)
                                {
                                    mid[4-balloon.lives].soundtrack.stopmusic();
                                    //music_playing = true;
                                    goto ending;
                                }
                                //Handle events on queue
                                if(clock%750 == 0) {
                                    int temp1=rand()%3;
                                    int temp2=rand()%3;
                                    int temp3=rand()%3;
                                    if(temp1==0) {
                                        walls[0][0].Init(1);
                                    }
                                    if(temp1==1) {
                                        walls[0][1].Init(2);
                                    }
                                    if(temp1==2) {
                                        walls[0][2].Init(3);
                                    }
                                    if(temp2!=temp1) {
                                        if(temp2==0) {
                                            walls[0][0].Init(1);
                                        }
                                        if(temp2==1) {
                                            walls[0][1].Init(2);
                                        }
                                        if(temp2==2) {
                                            walls[0][2].Init(3);
                                        }
                                    }
                                    if(temp3!=temp1&&temp3!=temp2&&rand()%100<10) {
                                        if(temp3==0) {
                                            walls[0][0].Init(1);
                                        }
                                        if(temp3==1) {
                                            walls[0][1].Init(2);
                                        }
                                        if(temp3==2) {
                                            walls[0][2].Init(3);
                                        }
                                    }
                                }
                                else if(clock%(750/speed)== 250/speed) {
                                    int temp1=rand()%3;
                                    int temp2=rand()%3;
                                    int temp3=rand()%3;
                                    if(temp1==0) {
                                        walls[1][0].Init(1);
                                    }
                                    if(temp1==1) {
                                        walls[1][1].Init(2);
                                    }
                                    if(temp1==2) {
                                        walls[1][2].Init(3);
                                    }
                                    if(temp2!=temp1) {
                                        if(temp2==0) {
                                            walls[1][0].Init(1);
                                        }
                                        if(temp2==1) {
                                            walls[1][1].Init(2);
                                        }
                                        if(temp2==2) {
                                            walls[1][2].Init(3);
                                        }
                                    }
                                    if(temp3!=temp1&&temp3!=temp2&&rand()%100<10) {
                                        if(temp3==0) {
                                            walls[1][0].Init(1);
                                        }
                                        if(temp3==1) {
                                            walls[1][1].Init(2);
                                        }
                                        if(temp3==2) {
                                            walls[1][2].Init(3);
                                        }
                                    }
                                }
                                else if(clock%(750/speed)== 500/speed) {
                                    int temp1=rand()%3;
                                    int temp2=rand()%3;
                                    int temp3=rand()%3;
                                    if(temp1==0) {
                                        walls[2][0].Init(1);
                                    }
                                    if(temp1==1) {
                                        walls[2][1].Init(2);
                                    }
                                    if(temp1==2) {
                                        walls[2][2].Init(3);
                                    }
                                    if(temp2!=temp1) {
                                        if(temp2==0) {
                                            walls[2][0].Init(1);
                                        }
                                        if(temp2==1) {
                                            walls[2][1].Init(2);
                                        }
                                        if(temp2==2) {
                                            walls[2][2].Init(3);
                                        }
                                    }
                                    if(temp3!=temp1&&temp3!=temp2&&rand()%100<10) {
                                        if(temp3==0) {
                                            walls[2][0].Init(1);
                                        }
                                        if(temp3==1) {
                                            walls[2][1].Init(2);
                                        }
                                        if(temp3==2) {
                                            walls[2][2].Init(3);
                                        }
                                    }
                                }
                                else {
                                    if(rand()%1000==2 && !bat.get_exist()){
                                        bat.init();
                                        score += 50;
                                    }
                                    if(rand()%5000==2500 && !shield.get_exist()){
                                        shield.init();
                                    }
                                }
                                for(int i=0; i<3; i++) {
                                    for(int j=0; j<3; j++) {
                                        walls[i][j]+=speed;
                                    }
                                }
                                if(bat.get_exist()){
                                    bat+=direction;
                                    if(bat.get_y()<-50){
                                        bat.set_false();
                                    }
                                }
                                if(shield.get_exist()){
                                    if(speed == 1)
                                    {
                                        shield+=speed;
                                    }
                                    else
                                    {
                                        shield+=speed-1;
                                    }
                                    if(shield.get_y()>800){
                                        shield.set_false();
                                    }
                                }
                                if(clock%1200 < 250 && clock >= 2400)
                                {
                                    flash.set_true();
                                    ++flash;
                                }

                                clock++;
                                score+=speed;
                                if(clock%1500==0 && speed<3) {
                                    speed++;
                                }

                                if(balloon.move( walls,bat,flash, shield)==3) {
                                    if(!protect)    protect = true;
                                    else            score += 50;
                                    shield.set_false();
                                    shield.reset();
                                }
                                //Move the dot and check collision
                                if(balloon.move( walls,bat,flash, shield)==1){
                                    touched = true;
                                    if(touched && !protect){
                                        balloon.lives --;
                                        mid[4-balloon.lives].soundtrack.stopmusic();
                                        mid[4-balloon.lives].soundtrack.play_music(scream);
                                        SDL_Delay(1500);
                                        if(balloon.lives >= 0)
                                        {
                                            clock = 0;
                                            speed = 1;
                                            score = 0;
                                            pass = false;
                                            if(balloon.lives == 1)  protect=true;
                                            else                    protect=false;
                                            touched = false;
                                            endline.x = -10;
                                            balloon.reset();
                                            bat.reset();
                                            flash.reset();
                                            shield.reset();
                                            for(int i=0; i<3; i++)
                                            {
                                                for(int j=0; j<3; j++)
                                                {
                                                    walls[i][j].reset();
                                                }
                                            }
                                            mid[4-balloon.lives].operating(dead_scene[4-balloon.lives], d_s_subtitle[4-balloon.lives], 9-balloon.lives);
                                        }
                                        if(balloon.lives == 0)
                                        {

                                            balloon.lives = 5;
                                            x = false;
                                            //replay();
                                            for(int i=0; i<5; i++)
                                            {
                                                mid[i].count = 0;
                                            }
                                            goto finish;
                                        }
                                    }
                                }
                                if(touched){
                                    shieldcount++;
                                    if(shieldcount==60){
                                        shieldcount=0;
                                        protect=0;
                                        touched=false;
                                    }
                                }
                                if(score >= 25000 && !pass)
                                {
                                    pass = true;
                                }
                                //Clear screen
                                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                                SDL_RenderClear( gRenderer );
                                SDL_Rect square = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT,};
                                gBackgroundTexture.render( 0, 0, &square);
                                //Render wall
                                if(pass)
                                {
                                    endline.y += speed;
                                    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0x00, 0xFF );
                                    SDL_RenderFillRect(gRenderer, &endline);
                                    if(endline.y > balloon.get_y())
                                    {
                                        mid[4-balloon.lives].soundtrack.stopmusic();
                                        end.operating(success_scene, success_subtitle, happy);
                                        clock = 0;
                                            speed = 1;
                                            score = 0;
                                            pass = false;
                                            protect=false;
                                            touched = false;
                                            endline.x = -10;
                                            balloon.reset();
                                            bat.reset();
                                            flash.reset();
                                            shield.reset();
                                            for(int i=0; i<3; i++)
                                            {
                                                for(int j=0; j<3; j++)
                                                {
                                                    walls[i][j].reset();
                                                }
                                            }
                                        balloon.lives = 5;
                                        x = false;
                                        goto finish;
                                    }
                                }
                                if(touched){
                                    shieldcount++;
                                    if(shieldcount==100){
                                        shieldcount=0;
                                        protect=0;
                                        touched=false;
                                    }
                                }
                                //Render wall
                                for(int i=0; i<3; i++) {
                                    for(int j=0; j<3; j++){
                                        walls[i][j].render();
                                    }
                                }
                                if(shield.get_exist()) shield.render();
                                if(bat.get_exist())    bat.render();
                                //Render text
                                for(int i=0; i<balloon.lives; i++)
                                {
                                    SDL_Rect pos = {470-(35*i), 5, 30, 70};
                                    gLivesTexture.render(pos.x, pos.y, &pos);
                                }
                                SDL_Rect word ={0,5,280,50};
                                gsRecordFontTexture.render(0,0,&word);
                                //Render dot
                                balloon.render();
                                if(protect)     balloon.protected_render();
                                flash.render();
                                //Update screen
                                SDL_RenderPresent( gRenderer );
                            }
                    }
                    close();
                }
                else
                {
                    bool restart = true;
                    while(restart)
                    {
                        int record = 1;
                        load(record);
                        scene mid;
                        scene end;
                        //While application is running
                        Uint32 time0 = SDL_GetTicks();
                        while( !quit ) {
                            if((SDL_GetTicks()-time0)%23 == 0)
                            {
                                while( SDL_PollEvent( &e ) != 0 ) {
                                        //User requests quit
                                        if( e.type == SDL_QUIT ) {
                                            quit = true;
                                            x = true;
                                        }
                                        //Handle input for the dot
                                        balloon.handleEvent( e );
                                        if(e.type == SDL_KEYDOWN)
                                        {
                                            switch( e.key.keysym.sym )
                                            {
                                                case SDLK_m:
                                                mid.soundtrack.pause_and_resume();
                                                if(Mix_PlayingMusic() == 0) music_playing = true;
                                                else                        music_playing = false;
                                            }
                                        }

                                    }
                                if(music_playing)   mid.soundtrack.play_music(Fukakouryoku);
                                if(x)
                                {
                                    mid.soundtrack.stopmusic();
                                    //music_playing = true;
                                    goto ending;
                                }
                                //Handle events on queue
                                if(clock%750 == 0) {
                                    int temp1=rand()%3;
                                    int temp2=rand()%3;
                                    int temp3=rand()%3;
                                    if(temp1==0) {
                                        walls[0][0].Init(1);
                                    }
                                    if(temp1==1) {
                                        walls[0][1].Init(2);
                                    }
                                    if(temp1==2) {
                                        walls[0][2].Init(3);
                                    }
                                    if(temp2!=temp1) {
                                        if(temp2==0) {
                                            walls[0][0].Init(1);
                                        }
                                        if(temp2==1) {
                                            walls[0][1].Init(2);
                                        }
                                        if(temp2==2) {
                                            walls[0][2].Init(3);
                                        }
                                    }
                                    if(temp3!=temp1&&temp3!=temp2&&rand()%100<10) {
                                        if(temp3==0) {
                                            walls[0][0].Init(1);
                                        }
                                        if(temp3==1) {
                                            walls[0][1].Init(2);
                                        }
                                        if(temp3==2) {
                                            walls[0][2].Init(3);
                                        }
                                    }
                                }
                                else if(clock%(750/speed)== 250/speed) {
                                    int temp1=rand()%3;
                                    int temp2=rand()%3;
                                    int temp3=rand()%3;
                                    if(temp1==0) {
                                        walls[1][0].Init(1);
                                    }
                                    if(temp1==1) {
                                        walls[1][1].Init(2);
                                    }
                                    if(temp1==2) {
                                        walls[1][2].Init(3);
                                    }
                                    if(temp2!=temp1) {
                                        if(temp2==0) {
                                            walls[1][0].Init(1);
                                        }
                                        if(temp2==1) {
                                            walls[1][1].Init(2);
                                        }
                                        if(temp2==2) {
                                            walls[1][2].Init(3);
                                        }
                                    }
                                    if(temp3!=temp1&&temp3!=temp2&&rand()%100<10) {
                                        if(temp3==0) {
                                            walls[1][0].Init(1);
                                        }
                                        if(temp3==1) {
                                            walls[1][1].Init(2);
                                        }
                                        if(temp3==2) {
                                            walls[1][2].Init(3);
                                        }
                                    }
                                }
                                else if(clock%(750/speed)== 500/speed) {
                                    int temp1=rand()%3;
                                    int temp2=rand()%3;
                                    int temp3=rand()%3;
                                    if(temp1==0) {
                                        walls[2][0].Init(1);
                                    }
                                    if(temp1==1) {
                                        walls[2][1].Init(2);
                                    }
                                    if(temp1==2) {
                                        walls[2][2].Init(3);
                                    }
                                    if(temp2!=temp1) {
                                        if(temp2==0) {
                                            walls[2][0].Init(1);
                                        }
                                        if(temp2==1) {
                                            walls[2][1].Init(2);
                                        }
                                        if(temp2==2) {
                                            walls[2][2].Init(3);
                                        }
                                    }
                                    if(temp3!=temp1&&temp3!=temp2&&rand()%100<10) {
                                        if(temp3==0) {
                                            walls[2][0].Init(1);
                                        }
                                        if(temp3==1) {
                                            walls[2][1].Init(2);
                                        }
                                        if(temp3==2) {
                                            walls[2][2].Init(3);
                                        }
                                    }
                                }
                                else {
                                    if(rand()%1000==2 && !bat.get_exist()){
                                        bat.init();
                                        score += 50;
                                    }
                                    if(rand()%5000==2500 && !shield.get_exist()){
                                        shield.init();
                                    }
                                }
                                for(int i=0; i<3; i++) {
                                    for(int j=0; j<3; j++) {
                                        walls[i][j]+=speed;
                                    }
                                }
                                if(bat.get_exist()){
                                    bat+=direction;
                                    if(bat.get_y()<-50){
                                        bat.set_false();
                                    }
                                }
                                if(shield.get_exist()){
                                    if(speed == 1)
                                    {
                                        shield+=speed;
                                    }
                                    else
                                    {
                                        shield+=speed-1;
                                    }
                                    if(shield.get_y()>800){
                                        shield.set_false();
                                    }
                                }
                                if(clock%1200 < 250 && clock >= 2400)
                                {
                                    flash.set_true();
                                    ++flash;
                                }

                                clock++;
                                score+=speed;
                                if(clock%1500==0 && speed<3) {
                                    speed++;
                                }

                                if(balloon.move( walls,bat,flash, shield)==3) {
                                    if(!protect)    protect = true;
                                    else            score += 50;
                                    shield.set_false();
                                    shield.reset();
                                }
                                //Move the dot and check collision
                                if(balloon.move( walls,bat,flash, shield)==1){
                                    touched = true;
                                    if(touched && !protect){
                                        mid.soundtrack.stopmusic();
                                        mid.soundtrack.play_music(boom);
                                        SDL_Delay(500);
                                        x = false;
                                        //replay();
                                        clock = 0;
                                            speed = 1;
                                            pass = false;
                                            touched = false;
                                            int value = c_m_ending(score, record);
                                            if(value == 0)  restart = true;
                                            else            restart = false;
                                            score = 0;
                                            endline = {0, 0, SCREEN_WIDTH, 10};
                                            balloon.reset();
                                            for(int i=0; i<3; i++)
                                            {
                                                for(int j=0; j<3; j++)
                                                {
                                                    walls[i][j].reset();
                                                }
                                            }
                                            bat.reset();
                                            flash.reset();
                                            shield.reset();
                                        goto next;
                                    }
                                }
                                if(touched){
                                    shieldcount++;
                                    if(shieldcount==100){
                                        shieldcount=0;
                                        protect=0;
                                        touched=false;
                                    }
                                }
                                //Clear screen
                                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                                SDL_RenderClear( gRenderer );
                                SDL_Rect Background = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
                                gBackgroundTexture.render( 0, 0, &Background);
                                //Render wall
                                for(int i=0; i<3; i++) {
                                    for(int j=0; j<3; j++){
                                        walls[i][j].render();
                                    }
                                }
                                if(shield.get_exist()) shield.render();
                                if(bat.get_exist())    bat.render();
                                //Render score
                                //Render text
                                std::stringstream s1;
                                s1.str("");
                                s1.clear();
                                std::string showscore;
                                s1 << score/10;
                                s1 >> showscore;
                                SDL_Color textColor = { 0XFF, 0XFF,0XFF  };
                                if( !gcRecordFontTexture.loadFromRenderedText( showscore, textColor ) )
                                {
                                    printf( "Failed to render text texture!\n" );
                                }
                                SDL_Rect number ={340,5,140,50};
                                SDL_Rect word ={0,5,310,50};
                                if(score/100 == 0)
                                {
                                    number.w = 35;
                                    number.x = 445;
                                }
                                else if(score/1000 == 0)
                                {
                                    number.w = 70;
                                    number.x = 410;
                                }
                                else if(score/10000 == 0)
                                {
                                    number.w = 105;
                                    number.x = 375;
                                }
                                gcRecordFontTexture.render(number.x, number.y, &number);
                                gcRecordFontTexture2.render(0,0,&word);
                                //Render dot
                                balloon.render();
                                if(protect)     balloon.protected_render();
                                flash.render();
                                //Update screen
                                SDL_RenderPresent( gRenderer );

                            }
                        }
                        next:
                            continue;
                    }

                }
                finish:
                    continue;
            }
            ending:
                close();
                return 0;
		}
	}
	return 0;
}

