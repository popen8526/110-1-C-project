#include "scene.h"

#ifndef LTEXTURE_H_INCLUDED
#include "LTexture.h"
#endif // LTEXTURE_H_INCLUDED

extern bool x;
extern SDL_Renderer* gRenderer;

extern LTexture preface_background;
extern LTexture red_hat;
extern LTexture gBatTexture;
extern LTexture interface[3];
extern LTexture preface_rules[2];
extern Mix_Music *gMusic[15];

extern void close();

void Sound_effect::play_music(int index) const
{
	//If there is no music playing
	if( Mix_PlayingMusic() == 0 )
	{
		//Play the music
		Mix_PlayMusic( gMusic[index], 1);
	}
	return;
}

void Sound_effect::pause_and_resume() const
{
	//If the music is paused
	if( Mix_PausedMusic() == 1 )
	{
		//Resume the music
		Mix_ResumeMusic();
	}
	//If the music is playing
	else
	{
		//Pause the music
		Mix_PauseMusic();
	}
	return;
}

void Sound_effect::stopmusic() const
{
	//Stop the music
	Mix_HaltMusic();
	return;
}

scene::scene(): soundtrack()
{
	Background.x = 0;
	Background.y = 0;
	Background.w = 500;
	Background.h = 750;
	operating_quit = false;
	count = 0;
	//Set up preface
	for(int i=0;i<8;i++)
	{
		subtitle[i].x = 0;
		subtitle[i].y = 40*i;
		subtitle[i].w = 500;
		subtitle[i].h = 40;
	}
}

void scene::operating(LTexture &preface_background,LTexture &preface, int index)
{
	operating_quit = false;
	//While application is running
        while( !operating_quit )
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
                        case SDLK_UP:
                        if((count-1)>=0)
                        count--;
                        break;
                        case SDLK_DOWN:
                        count++;
                        break;
                        // pass the scene
                        case SDLK_p:
                        operating_quit = true;
                        break;
                        case SDLK_m:
                        soundtrack.pause_and_resume();
                    }
                }
            }
            //play soundtrack
            soundtrack.play_music(index);
            //Clear screen
            SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
            SDL_RenderClear( gRenderer );
            //Render background
            preface_background.render2(0,0,&Background);
            //subtitle finished
            if(count==8)
            {
                break;
            }
            //Render subtitle
            preface.render2(0,710,&subtitle[count]);
            //Update screen
            SDL_RenderPresent( gRenderer );
            if(x)   close();
        }


	soundtrack.stopmusic();
	return;
}

preface_scene::preface_scene()
{
	sc = 0;
	// set red_hat
	frame_f.x = 0;
	frame_f.y = 0;
	frame_f.w = 97;
	frame_f.h = 189;
	// set interface
	frame_t.x = 0;
	frame_t.y = 0;
	frame_t.w = 400;
	frame_t.h = 100;
}

void preface_scene::interface_operating()
{
		operating_quit = false;
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
						case SDLK_s:
						setsc(1);
						operating_quit = true;
						break;
						case SDLK_c:
						setsc(2);
						operating_quit = true;
						break;
					}
				}
			}
			//Clear screen
			SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
			SDL_RenderClear( gRenderer );
			//Render background
			preface_background.render2(0,0,&Background);
			//Render interface
			interface[0].render2(50, 100, &frame_t);
			interface[1].render2(50, 400, &frame_t);
			interface[2].render2(50, 500, &frame_t);
			//Update screen
			SDL_RenderPresent( gRenderer );
			if(x) close();
		}
	return;
}

void preface_scene::operating(LTexture &preface_background,LTexture &preface,int index)
{

		operating_quit = false;
		//While application is running
		while( (!operating_quit) )
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
						case SDLK_UP:
						if((count-1)>=0)
						count--;
						break;
						case SDLK_DOWN:
						count++;
						break;
						// pass the scene
						case SDLK_p:
						operating_quit = true;
						break;
						case SDLK_m:
						soundtrack.pause_and_resume();
					}
				}
			}
			//play soundtrack
			soundtrack.play_music(index);
			//Clear screen
			SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
			SDL_RenderClear( gRenderer );
			//Render background
            preface_background.render2(0,0,&Background);
			//Render figure
			red_hat.render2(201, 521, &frame_f);
			//subtitle finished
			if(count==8)
			{
				break;
			}
			//Render subtitle
			preface.render2(0,710,&subtitle[count]);
			//Update screen
			SDL_RenderPresent( gRenderer );
			if(x)
            {
                soundtrack.stopmusic();
                close();
            }
		}
		soundtrack.stopmusic();

	return;
}

void preface_scene::rules_operating()
{
    operating_quit = false;
		//While application is running
		while( (!operating_quit) )
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
						case SDLK_DOWN:
						operating_quit = true;
					}
				}
			}
			//Clear screen
			SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
			SDL_RenderClear( gRenderer );
			//Render background
            if(sc == 1)         preface_rules[0].render2(0,0,&Background);
            else if(sc == 2)    preface_rules[1].render2(0,0,&Background);
			//Render figure
			SDL_RenderPresent( gRenderer );
			if(x)
            {
                close();
            }
		}

	return;
}

