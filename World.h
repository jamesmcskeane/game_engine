/*
 * World.h
 *
 *  Created on: 4 Dec 2015
 *      Author: jamesmcskeane
 */

#ifndef WORLD_H_
#define WORLD_H_
#include <SDL2/SDL.h>
#include "SpriteRect.h"
#include "SpriteCirc.h"
#include "GlobalDefinitions.h"

class World
{
public:
	World();
	~World();
	void init();
	void fillColor(Uint32 r, Uint32 b, Uint32 g);
	void renderWorld();


	SpriteRect* getPlayer();
	SpriteRect* getEnemy();

	void setWorldObjects();
	void createPlayer();
	void createEnemy();
	void setBackground();

private:

	SDL_Window *	mWindow;
	SDL_Renderer *	mRender;
	SDL_Texture* 	mWorldSurface;
	SpriteList 		mSpriteList;
	SpriteRect* 	mPlayer;
	SpriteRect*		mEnemy;
};

#endif /* WORLD_H_ */
