#include "Balloon.h"

#ifndef LTEXTURE_H_INCLUDED
#include "LTexture.h"
#endif // LTEXTURE_H_INCLUDED

#ifndef SCENE_H_INCLUDED
#include "scene.h"
#endif // SCENE_H_INCLUDED

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

//The window we'll be rendering to
extern SDL_Window* gWindow ;

//The window renderer
extern SDL_Renderer* gRenderer ;

//Scene textures
extern LTexture gFooTexture[5];
extern LTexture gShield2Texture;

extern bool checkCollision( SDL_Rect a, SDL_Rect b );

Balloon::Balloon() {
	//Initialize the offsets
	lives = 5;
	mPosX = 0;
	mPosY = 600;
	degrees=0;
	//Set collision box dimension
	mCollider.w = BALLOON_WIDTH;
	mCollider.h = BALLOON_HEIGHT/2;

	//Initialize the velocity
	mVelX = 0;
	mVelY = 0;
}

void Balloon::handleEvent( SDL_Event& e ) {
	//If a key was pressed
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 ) {
		//Adjust the velocity
		switch( e.key.keysym.sym ) {
			case SDLK_UP:
				mVelY -= BALLOON_VEL;
				break;
			case SDLK_DOWN:
				mVelY += BALLOON_VEL;
				break;
			case SDLK_LEFT:
				mVelX -= BALLOON_VEL;
				degrees = -45;
				break;
			case SDLK_RIGHT:
				mVelX += BALLOON_VEL;
				degrees = +45;
				break;
		}
	}
	//If a key was released
	else if( e.type == SDL_KEYUP && e.key.repeat == 0 ) {
		//Adjust the velocity
		switch( e.key.keysym.sym ) {

			case SDLK_UP:
				mVelY = 0;
				break;
			case SDLK_DOWN:
				mVelY = 0;
				break;
			case SDLK_LEFT:
				mVelX =0;
				degrees = 0;
				break;
			case SDLK_RIGHT:
				mVelX = 0;
				degrees = 0;
				break;
		}
	}
}

int Balloon::move( Wood walls[3][3] ,Bat bat, Thunder flash, Shield shield) {
	//Move the dot left or right
	mPosX += mVelX;
	mCollider.x = mPosX;

	//If the dot collided or went too far to the left or right
	if( ( mPosX < 0 ) || ( mPosX + BALLOON_WIDTH > SCREEN_WIDTH ) ) {
		//Move back
		mPosX -= mVelX;
		mCollider.x = mPosX;
	}
	//Move the dot up or down
	mPosY += mVelY;
	mCollider.y = mPosY;

	//If the dot collided or went too far up or down
	if( ( mPosY < 0 ) || ( mPosY + BALLOON_HEIGHT > SCREEN_HEIGHT ) ) {
		//Move back
		mPosY -= mVelY;
		mCollider.y = mPosY;
	}

	for(int i=0; i<3; i++) {
		for(int j=0; j<3; j++) {
			if(checkCollision( mCollider, walls[i][j].mCollider )) {
				return 1;
			}
		}
	}
	if(checkCollision( mCollider, bat.mCollider )) {
		return 1;
	}
	if(checkCollision( mCollider, flash.mCollider )) {
		return 1;
	}
	if(checkCollision( mCollider, shield.mCollider )) {
		return 3;
	}

	return 0;
}

void Balloon::render() {
	//Show the dot
	gFooTexture[lives-1].render( mPosX, mPosY, NULL, degrees);
}

void Balloon::protected_render()
{
    SDL_Rect pic = {mPosX, mPosY, 60, 60};
    gShield2Texture.render( mPosX, mPosY, &pic, degrees);
}

void Balloon::reset()
{
    mPosX = 0;
    mPosY = 600;
    mVelX = 0;
    mVelY = 0;
    degrees = 0;
}
