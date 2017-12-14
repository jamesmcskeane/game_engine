/*
 * SpriteCirc.h
 *
 *  Created on: 15 Dec 2015
 *      Author: jamesmcskeane
 */

#ifndef SPRITECIRC_H_
#define SPRITECIRC_H_
#include "SpriteBase.h"

class SpriteCirc : public SpriteBase
{
	public:
		SpriteCirc(Uint8 index,
			   	   int pos_x,
				   int pos_y,
				   int radius,
				   SDL_Renderer* render,
				   Collision col,
				   SpriteList* list);

		int getRadius();

		~SpriteCirc();

		void fillColor	(Uint32 r, Uint32 g, Uint32 b);

	private:

		int mRadius;
};

#endif /* SPRITECIRC_H_ */
