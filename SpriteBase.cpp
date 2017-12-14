/*
 * SpriteBase.cpp
 *
 *  Created on: 4 Dec 2015
 *      Author: jamesmcskeane
 */
#include "SpriteBase.h"

// Constructor
SpriteBase::SpriteBase(Uint8 index,
					   int pos_x,
					   int pos_y,
					   int width,
					   int height,
					   SDL_Renderer* render,
					   Collision col,
					   SpriteList *list,
					   SpriteType type)
					   : mIndex(index)
					   , mCollision(col)
					   , mTexture(NULL)
					   , mRender(render)
					   , mType(type)

{
	mDestRect.x = pos_x;
	mDestRect.y = pos_y;
	mDestRect.w = width;
	mDestRect.h = height;



	mTextRect.x = 0;
	mTextRect.y = 0;
	mTextRect.w = width;
	mTextRect.h = height;

	mList = list;
	mList->push_back(this);
}

// Constructor overload with color
SpriteBase::SpriteBase(Uint8 index,
					   Uint32 color,
					   int pos_x,
					   int pos_y,
					   int width,
					   int height,
					   SDL_Renderer* render,
					   Collision col,
					   SpriteList *list,
					   SpriteType type)
					   : mIndex(index)
					   , mCollision(col)
					   , mTexture(NULL)
					   , mRender(render)
					   , mType(type)

{

	mDestRect.x = pos_x;
	mDestRect.y = pos_y;
	mDestRect.w = width;
	mDestRect.h = height;

	mTextRect.x = 0;
	mTextRect.y = 0;
	mTextRect.w = width;
	mTextRect.h = height;

	SDL_Surface* surface = SDL_CreateRGBSurface(0, mTextRect.w, mTextRect.h, 32,0,0,0,0 );
	SDL_FillRect(surface, NULL, color);
	mTexture = SDL_CreateTextureFromSurface(mRender, surface);
	SDL_FreeSurface(surface);

	mList = list;
	mList->push_back(this);
}

// Constructor overload with path to file
SpriteBase::SpriteBase(Uint8 index,
					   std::string path,
					   int pos_x,
					   int pos_y,
					   int width,
					   int height,
					   SDL_Renderer* render,
					   Collision col,
					   SpriteList *list,
					   SpriteType type)
					   : mIndex(index)
					   , mCollision(col)
					   , mTexture(NULL)
					   , mRender(render)
					   , mType(type)

{
	mDestRect.x = pos_x;
	mDestRect.y = pos_y;
	mDestRect.w = width;
	mDestRect.h = height;

	mTextRect.x = 0;
	mTextRect.y = 0;
	mTextRect.w = width;
	mTextRect.h = height;

	SDL_Surface * surface = SDL_LoadBMP(path.c_str());
	mTexture = SDL_CreateTextureFromSurface(mRender, surface);
	SDL_FreeSurface(surface);

	mList = list;
	mList->push_back(this);
}

// get index
Uint8 SpriteBase::getIndex()
{
	return mIndex;
}

// set sprite position
void SpriteBase::setPos(int x, int y)
{
	mDestRect.x =  x;
	mDestRect.y =  y;
}

// get sprite position x axis
int SpriteBase::getPosX()
{
	return mDestRect.x;
}

// get sprite position y axis
int SpriteBase::getPosY()
{
	return mDestRect.y;
}

// get sprite width
int SpriteBase::getWidth()
{
	return mDestRect.w;
}

// get sprite height
int SpriteBase::getHeight()
{
	return mDestRect.h;
}

// set texture positions x and y
void SpriteBase::setTextRectPos(int x, int y)
{
	mTextRect.x = x;
	mTextRect.y = y;
}

// get SDL rect texture object
SDL_Rect* SpriteBase::getTextRect()
{
	return &mTextRect;
}

// get SDL location of rect to apply texture
SDL_Rect* SpriteBase::getDestRect()
{
	return &mDestRect;
}

// get texture
SDL_Texture* SpriteBase::getTexture()
{
	return mTexture;
}

// set texture
void SpriteBase::setTexture(SDL_Texture* text)
{
	mTexture = text;
}

// get renderer
SDL_Renderer* SpriteBase::getRenderer()
{
	return mRender;
}

// load imagale from file to surface object
void SpriteBase::loadImage(std::string path)
{
	SDL_Surface * surface = SDL_LoadBMP(path.c_str());
	//  This makes a color transparent.
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 255, 255, 255));
	mTexture = SDL_CreateTextureFromSurface(mRender, surface);
	SDL_FreeSurface(surface);
}

// fill color to object surface
void SpriteBase::fillColor(Uint32 r, Uint32 g, Uint32 b)
{
	SDL_Surface* surface = SDL_CreateRGBSurface(0, mTextRect.w, mTextRect.h, 32,0,0,0,0 );
	Uint32 background = SDL_MapRGB(surface->format, r, g, b);
	SDL_FillRect(surface, NULL, background);
	mTexture = SDL_CreateTextureFromSurface(mRender, surface);
	SDL_FreeSurface(surface);
}

// set collision
void SpriteBase::setCollision(Collision col)
{
	mCollision = col;
}

// get collision
Collision SpriteBase::getCollision()
{
	return mCollision;
}

// get sprite type
SpriteType SpriteBase::getType()
{
	return mType;
}

// get sprite list
SpriteList* SpriteBase::getSpriteList()
{
	return mList;
}

// set sprite list
void SpriteBase::setSpriteList(SpriteList* list)
{
	mList = list;
}

// deconstruct sprite
SpriteBase::~SpriteBase()
{
	SDL_DestroyTexture(mTexture);
}
