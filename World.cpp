/*
 * World.cpp
 *
 *  Created on: 4 Dec 2015
 *      Author: jamesmcskeane
 */

#include "World.h"
#include <iostream>

// Constructor
World::World() : mWindow(NULL)
			   , mRender(NULL)
			   , mWorldSurface(NULL)
			   , mPlayer(NULL)
			   , mEnemy(NULL)
{

}

// Deconstructor
World::~World()
{
	for(SpriteList::iterator it = mSpriteList.begin(); it != mSpriteList.end(); ++it)
	{
		delete *it;
	}
	mSpriteList.clear();
	SDL_DestroyTexture(mWorldSurface);
	SDL_DestroyRenderer(mRender);
}

// Initialize world
void World::init()
{
	mWindow = SDL_CreateWindow("VIEW INTO WORLD!",
	            				SDL_WINDOWPOS_CENTERED,
								SDL_WINDOWPOS_CENTERED,
								GLOBAL_WINDOW_WIDTH,
								GLOBAL_WINDOW_HEIGHT,
								SDL_WINDOW_SHOWN);

	mRender = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);

	mSpriteList.clear();
	//fillColor(240, 240, 245);
	setWorldObjects();
	createPlayer();
	//createEnemy();
}

// Set background
void World::setBackground()
{
	SDL_Surface * surface = SDL_LoadBMP("C:\\Users\\jamesmcskeane\\workspace\\GameEngine\\images\\background.bmp");
	mWorldSurface = SDL_CreateTextureFromSurface(mRender, surface);
	SDL_FreeSurface(surface);
}

// Fill color
void World::fillColor(Uint32 r, Uint32 b, Uint32 g)
{
	SDL_Surface* surface = SDL_CreateRGBSurface(0, GLOBAL_WINDOW_WIDTH, GLOBAL_WINDOW_HEIGHT, 32,0,0,0,0 );
	Uint32 background = SDL_MapRGB(surface->format, r, g, b);
	SDL_FillRect(surface, NULL, background);
	mWorldSurface = SDL_CreateTextureFromSurface(mRender, surface);
	SDL_FreeSurface(surface);

	//SDL_RenderCopy(mRender, mWorldSurface,NULL, NULL,);
}

// Build out world object by co-ordinates
void World::setWorldObjects()
{
	SDL_Surface* surface = SDL_CreateRGBSurface(0, GLOBAL_WINDOW_WIDTH, GLOBAL_WINDOW_HEIGHT, 32,0,0,0,0 );
	Uint32 blue 	= SDL_MapRGB(surface->format, 62, 142, 176);
	Uint32 red		= SDL_MapRGB(surface->format, 181,38,62);

	// create Sprite
	std::string path("C:\\Users\\jamesmcskeane\\workspace\\GameEngine\\images\\background.bmp");
	//new SpriteBase(3,
	//			   path,
	//			   0,
	//			   0,
	//			   GLOBAL_WINDOW_WIDTH,
	//			   GLOBAL_WINDOW_HEIGHT,
	//			   mRender,
	//			   NO_COLLISION,
	//			   &mSpriteList);

	new SpriteBase(4, blue, 10, 510, 7000, 7, mRender, NOTHING, &mSpriteList);
	new SpriteBase(5, blue, 10, 10, 7, 500, mRender, NOTHING, &mSpriteList);
	//new SpriteBase(6, blue, 703, 10, 7, 500, mRender, NOTHING, &mSpriteList);

	new SpriteBase(7, red, 1000, 465, 45, 45, mRender, NOTHING, &mSpriteList);
	new SpriteBase(8, blue, 150, 100, 45, 7, mRender, NOTHING, &mSpriteList);
	new SpriteBase(9, blue, 250, 150, 45, 7, mRender, NOTHING, &mSpriteList);
	new SpriteBase(10, blue, 350, 200, 45, 7, mRender, NOTHING, &mSpriteList);
	new SpriteBase(11, blue, 450, 250, 45, 7, mRender, NOTHING, &mSpriteList);
	new SpriteBase(12, blue, 550, 300, 45, 7, mRender, NOTHING, &mSpriteList);
	new SpriteBase(13, blue, 650, 350, 45, 7, mRender, NOTHING, &mSpriteList);
	new SpriteBase(14, blue, 550, 400, 45, 7, mRender, NOTHING, &mSpriteList);
	new SpriteBase(15, blue, 450, 450, 45, 7, mRender, NOTHING, &mSpriteList);

	new SpriteBase(16, red, 50, 200, 15, 300, mRender,CLIMBABLE, &mSpriteList);
	//std::string path("C:\\Users\\JM40379\\workspace\\SDLExamples\\image\\donkey.bmp");
	//new SpriteRect(17, 50, 200, 50, 50, NOTHING, path ,mWorldSurface, &mSpriteList);
	//new SpriteBase(10, blue, 32, 76, 500, 7, NOTHING, &mSpriteList);

	//SpriteCirc* spriteCircle = new SpriteCirc(17, 300, 300, 70, mRender, NOTHING, &mSpriteList);
	//spriteCircle->fillColor(214,32,72);

	SDL_FreeSurface(surface);
}

// Create player object
void World::createPlayer()
{
	mPlayer = new SpriteRect(1, 200, 200, 34, 34, mRender, PLAYER, &mSpriteList);
	mPlayer->fillColor(120, 214, 128);
	mPlayer->setObjectSpeed(5);
	//mPlayer->loadImage("C:\\Users\\jamesmcskeane\\workspace\\GameEngine\\images\\spriteSheet.bmp",9,4,64,64,15,12);
	mPlayer->setTextRectPos(15,12);
}

// Create enemy object
void World::createEnemy()
{
	mEnemy = new SpriteRect(2, 270, 259, 15, 15, mRender, ENEMY, &mSpriteList);
	mEnemy->fillColor(196, 200, 15);
	mEnemy->setObjectSpeed(200);
	mEnemy->randomMove();
}

// Get player
SpriteRect* World::getPlayer()
{
	return mPlayer;
}

// Get enemy
SpriteRect* World::getEnemy()
{
	return mEnemy;
}

// Render world
void World::renderWorld()
{
	SDL_RenderClear(mRender);
	SDL_SetRenderDrawColor(mRender, 240, 240, 240, 240);
	int h_offset = 0;
	int l_offset = 0;
	for(SpriteList::iterator it = mSpriteList.begin(); it != mSpriteList.end(); ++it)
	{
		SpriteRect* sprite = static_cast<SpriteRect*>(*it);

		//  This allows me to scroll
		if(sprite->getIndex() == 1)
		{
			int high = (GLOBAL_WINDOW_WIDTH / 10) * 7;
			int low = (GLOBAL_WINDOW_WIDTH / 10) * 2;
			//  Scrolling right.
			if(sprite->getPosX() > high)
			{
				h_offset = sprite->getPosX() - high;
				for(SpriteList::iterator tempIt = mSpriteList.begin(); tempIt != mSpriteList.end(); ++tempIt)
				{
					SpriteBase* tempSp = (*tempIt);
					int x = tempSp->getPosX() - h_offset;
					int y = tempSp->getPosY();
					tempSp->setPos(x,y);
				}

			}

			//  Scrolling left.
			if(sprite->getPosX() < low)
			{
				l_offset = low - sprite->getPosX();
				for(SpriteList::iterator tempIt = mSpriteList.begin(); tempIt != mSpriteList.end(); ++tempIt)
				{
					SpriteBase* tempSp = (*tempIt);
					int x = tempSp->getPosX() + l_offset;
					int y = tempSp->getPosY();
					tempSp->setPos(x,y);
				}

			}

		} // End of scrolling

		//if(sprite->getMovingLeft() && sprite->getIndex() == 1)
		//{
		//SDL_Point center;
		//center.x = 22;
		//center.y = 19;
		//SDL_RendererFlip flip = SDL_FLIP_VERTICAL;
		//SDL_RenderCopyEx(mRender, sprite->getTexture(),sprite->getTextRect(), sprite->getDestRect(), 180, &center, flip);

		//SDL_SetRenderDrawBlendMode(mRender, SDL_BLENDMODE_NONE);
		SDL_RenderCopy(mRender, sprite->getTexture(),sprite->getTextRect(), sprite->getDestRect());

	}

	SDL_RenderPresent(mRender);
}
