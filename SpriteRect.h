/*
 * SpriteRect.h
 *
 *  Created on: 4 Dec 2015
 *      Author: jamesmcskeane
 */

#ifndef SPRITERECT_H_
#define SPRITERECT_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>
#include "SpriteBase.h"
#include "SpriteCirc.h"
#include "WorldPhysics.h"

class SpriteRect : public SpriteBase
{
public:
	SpriteRect(Uint8 index,
			   int pos_x,
			   int pos_y,
			   int width,
			   int height,
			   SDL_Renderer* render,
			   Collision col,
			   SpriteList* list);

	virtual ~SpriteRect();

	void move();
	void keyboardControl();
	void randomMove();
	void setPos(int x, int y);
	double distanceSquared(int x1, int y1, int x2, int y2);
	bool checkCollision(int& x, int& y);
	bool checkCollision(SpriteRect& rect, SpriteCirc& circle);
	void setObjectSpeed(int speed);
	void applyGravity();
	void jump();
	void applySpeed(int x, int y);

	void setMovingLeft(bool val);
	bool getMovingLeft();
	void setMovingRight(bool val);
	bool getMovingRight();
	void setMovingUp(bool val);
	void setMovingDown(bool val);
	void setSpeedPressed(bool val);
	void setTouchTop(bool val);
	void setTouchBottom(bool val);
	void setTouchLeft(bool val);
	void setTouchRight(bool val);

	enum MoveLast{
			NONE,
			DOWN,
			LEFT,
			RIGHT,
			UP
				};

	void setSpriteSheetImage(MoveLast val);
	using SpriteBase::loadImage;
	void loadImage  (std::string path, int rowNum, int colNum, int rowPx, int colPx, int width_offset, int height_offset);
private:

	bool 			mMoving_left;
	bool 			mMoving_right;
	bool 			mMoving_up;
	bool 			mMoving_down;
	bool 			mTouch_top;
	bool 			mTouch_bottom;
	bool 			mTouch_left;
	bool 			mTouch_right;
	bool			mOnClimbableObject;
	bool			mSpeedPressed;
	MoveLast		mMoveLast;

	//  This is used for iterating through a sprite sheet.
	int				mSpriteSheetCounter;
	int				mSpriteSheetRowNum;
	int				mSpriteSheetColNum;
	int				mSpriteSheetRowPxSize;
	int				mSpriteSheetColPxSize;
	int				mSpriteSheetWidthOffset;
	int				mSpriteSheetHeightOffset;
	int				mCircleSpritePrecision;

	int				mContinuousKeyboardVer;
	int				mContinuousKeyboardHor;

	int				mJumpPower;

	WorldPhysics*	mWorldPhysics;

};

#endif
