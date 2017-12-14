/*
 * SpriteBase.h
 *
 *  Created on: 4 Dec 2015
 *      Author: jamesmcskeane
 */

#ifndef SPRITEBASE_H_
#define SPRITEBASE_H_

#include <SDL2/SDL.h>
//#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>
#include "GlobalDefinitions.h"

class SpriteBase;

typedef std::vector<SpriteBase*> SpriteList;

// Sprite is any object that can be drawn
class SpriteBase
{
public:
	// Basic geometrical sprite
	SpriteBase(Uint8 index,
			   int pos_x,
			   int pos_y,
			   int width,
			   int height,
			   SDL_Renderer* render,
			   Collision col,
			   SpriteList *list,
			   SpriteType type = Rect);

	// Color shape object
	SpriteBase(Uint8 index,
			   Uint32 color,
			   int pos_x,
			   int pos_y,
			   int width,
			   int height,
			   SDL_Renderer* render,
			   Collision col,
			   SpriteList *list,
			   SpriteType type = Rect);

	// Object that is loaded from file
	SpriteBase(Uint8 index,
			   std::string path,
			   int pos_x,
			   int pos_y,
			   int width,
			   int height,
			   SDL_Renderer* render,
			   Collision col,
			   SpriteList *list,
			   SpriteType type = Rect);


	// Deconstructor
	~SpriteBase();
	Uint8			getIndex();
	int				getPosX();
	int				getPosY();
	int				getHeight();
	int				getWidth();
	void			setPos(int x, int y);
	void			setTextRectPos(int x, int y);
	SDL_Rect * 		getTextRect();
	SDL_Rect *		getDestRect();
	SDL_Texture * 	getTexture();
	void			setTexture(SDL_Texture* text);
	SDL_Renderer*	getRenderer();

	// functions of base
	void loadImage  (std::string path);
	void fillColor	(Uint32 r, Uint32 g, Uint32 b);


	void 	setCollision(Collision col);
	Collision getCollision();

	SpriteType getType();

	void	setSpriteType(SpriteType type);
	SpriteType getSpriteType();

	SpriteList* getSpriteList();
	void	setSpriteList(SpriteList* list);

private:

	Uint8			mIndex;
	Collision 		mCollision;
	SDL_Texture* 	mTexture;
	SDL_Renderer*  	mRender;

	// This takes the chunk from a loaded texture
	SDL_Rect 		mTextRect;
	//  This specified the size and location of the texture to render.
	SDL_Rect		mDestRect;
	SpriteList		*mList;
	SpriteType 		mType;

};

#endif /* SPRITEBASE_H_ */
