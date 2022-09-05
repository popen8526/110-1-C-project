#include "Object.h"

#ifndef LTEXTURE_H_INCLUDED
#include "LTexture.h"
#endif // LTEXTURE_H_INCLUDED

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

//The window we'll be rendering to
extern SDL_Window* gWindow;

//The window renderer
extern SDL_Renderer* gRenderer;

//Scene textures
extern LTexture gFooTexture[5];
extern LTexture gWoodTexture;
extern LTexture gBatTexture;
extern LTexture gStrikeTexture;
extern LTexture gWarningTexture;
extern LTexture gShieldTexture;


Wood::Wood() :height(20){
	mCollider.w = 0;
	mCollider.h = 0;
	mCollider.x = 0;
	mCollider.y = 0;
}

Wood::Wood(int x,int y):height(20){
    mCollider.x = x;
	mCollider.y = y;
}

Bat::Bat() {
    exist = false;
	mCollider.w = 50;
	mCollider.h = 50;
	mCollider.x = -50;
	mCollider.y = -50;
}

Bat::Bat(int x,int y){
    mCollider.x = x;
	mCollider.y = y;
}

Shield::Shield() {
	mCollider.w = 50;
	mCollider.h = 50;
	mCollider.x = -50;
	mCollider.y = -50;
}

void Wood::Init(int type)
{
    if(type == 1){
        mCollider.x = 0;
        mCollider.y = 0;
        mCollider.w = 75+(rand()%75);
        mCollider.h = height;
    }

    if(type == 2){
        mCollider.x = 175+(rand()%75);
        mCollider.y = 0;
        mCollider.w = 75+rand()%(250-mCollider.x);
        mCollider.h = height;
    }

    if(type == 3){
        mCollider.w = 75+rand()%75;
        mCollider.x = 500-mCollider.w;
        mCollider.y = 0;
        mCollider.h = height;
    }
}

Thunder::Thunder()
{
    strike = false;
    exist = false;
    cnt = 0;
    mCollider.w = 30 + rand()%40;
    mCollider.x = rand()%(SCREEN_WIDTH-mCollider.w);
    mCollider.y = 0;
    mCollider.h = 0;
}

void Wood::render() {
	//Show the dot
	gWoodTexture.render( mCollider.x, mCollider.y,&mCollider);
}

void Wood::reset()
{
    mCollider.x = 0;
    mCollider.y = -height;
    mCollider.w = 0;
    mCollider.h = height;
}

void Wood::operator+=(int t)
{
    mCollider.y += t;
    return ;
}

void Bat::render() {
	//Show the dot
	gBatTexture.render( mCollider.x, mCollider.y,&mCollider);
}

void Bat::init()
{
    exist = true;
    if(rand()%2==1){
        mCollider.x = 0;
        mCollider.y = 750;
    }
    else{
        mCollider.x = 450;
        mCollider.y = 750;
    }
}

void Bat::reset()
{
    exist = false;
    mCollider.x = -50;
    mCollider.y = -50;
}

void Bat::operator+=(int &direction)
{
    if(mCollider.x>=450)     direction = -1;
    else if(mCollider.x<=0)  direction = 1;

    mCollider.x += direction;
    mCollider.y -= 1;
    return ;
}

void Bat::operator=(Bat &temp)
{
    this->mCollider.x = temp.mCollider.x;
    this->mCollider.y = temp.mCollider.y;
    this->mCollider.h = temp.mCollider.h;
    this->mCollider.w = temp.mCollider.w;
    return ;
}

Thunder& Thunder::operator++()
{
    cnt++;
    if(cnt >= 100 && cnt<150)
    {
        strike = true;
        mCollider.h = SCREEN_HEIGHT/2;
    }
    else if(cnt >= 150 && cnt < 250)
    {
        mCollider.h = SCREEN_HEIGHT;
    }
    else if(cnt == 250)  this->reset();
    return *this;
}

void Thunder::reset()
{
    strike = false;
    exist = false;
    cnt = 0;
    mCollider.w = 30 + rand()%40;
    mCollider.x = rand()%(SCREEN_WIDTH-mCollider.w);
    mCollider.h = 0;
}

void Thunder::render(){

    if(strike && exist)  gStrikeTexture.render(mCollider.x, 0, &mCollider);
    else if(exist)
    {
        SDL_Rect pic = {mCollider.x, 50, 50, 50};
        gWarningTexture.render(mCollider.x, 50, &pic);
    }
}

void Shield::init()
{
    mCollider.x = rand()%450;
    mCollider.y = 0;
    exist = true;
}

void Shield::reset()
{
    mCollider.x = -50;
    mCollider.y = -50;
}

void Shield::operator+=(int t)
{
    mCollider.y += t;
    return ;
}

void Shield::render() {
	//Show the dot
	gShieldTexture.render( mCollider.x, mCollider.y,&mCollider);
}
