/*
 * SpriteRect.cpp
 *
 *  Created on: 4 Dec 2015
 *      Author: jamesmcskeane
 */
#include "SpriteRect.h"
#include <iostream>

using namespace std;

// Constructor
SpriteRect::SpriteRect(Uint8 index,
					   int pos_x,
					   int pos_y,
					   int width,
					   int height,
					   SDL_Renderer* render,
					   Collision col,
					   SpriteList* list)
					   : SpriteBase(index, pos_x, pos_y, width, height, render, col, list, Rect)
					   , mMoving_left(false)
					   , mMoving_right(false)
					   , mMoving_up(false)
					   , mMoving_down(false)
					   , mTouch_top(false)
					   , mTouch_bottom(false)
					   , mTouch_left(false)
					   , mTouch_right(false)
					   , mOnClimbableObject(false)
					   , mSpeedPressed(false)
					   , mMoveLast(NONE)
					   , mSpriteSheetCounter(0)
					   , mSpriteSheetRowNum(0)
					   , mSpriteSheetColNum (0)
					   , mSpriteSheetRowPxSize(0)
					   , mSpriteSheetColPxSize(0)
					   , mSpriteSheetWidthOffset(0)
					   , mSpriteSheetHeightOffset(0)
					   , mCircleSpritePrecision(0)
					   , mContinuousKeyboardVer(0)
					   , mContinuousKeyboardHor(0)
					   , mJumpPower(0)
					   , mWorldPhysics(new WorldPhysics())
{

}

// Deconstructor
SpriteRect::~SpriteRect()
{

}

// Moving left value
void SpriteRect::setMovingLeft(bool val)
{
	mMoving_left = val;
}

// Are we moving left
bool SpriteRect::getMovingLeft()
{
	return mMoving_left;
}

// Moving right value
void SpriteRect::setMovingRight(bool val)
{
	mMoving_right = val;
}

// Are we moving right value
bool SpriteRect::getMovingRight()
{
	return mMoving_right;
}

// Moving up value
void SpriteRect::setMovingUp(bool val)
{
	mMoving_up = val;
}

// Moving down value
void SpriteRect::setMovingDown(bool val)
{
	mMoving_down = val;
}

// Speed pressed value
void SpriteRect::setSpeedPressed(bool val)
{
	mSpeedPressed = val;
}

// Set touch top
void SpriteRect::setTouchTop(bool val)
{
	mTouch_top = val;
}

// set touch bottom
void SpriteRect::setTouchBottom(bool val)
{
	mTouch_bottom = val;
}

// set touch left
void SpriteRect::setTouchLeft(bool val)
{
	mTouch_left = val;
}

// set touch right
void SpriteRect::setTouchRight(bool val)
{
	mTouch_right = val;
}

// set object speed
void SpriteRect::setObjectSpeed(int speed)
{
	//mObjectSpeed = speed;
}

// set position
void SpriteRect::setPos(int x, int y)
{
	int temp_x = getPosX() + x;
	int temp_y = getPosY() + y;

	//  Ensure position is on the window
	//if (temp_x > GLOBAL_WINDOW_WIDTH || temp_x < 0)
	//	return;

	//if (temp_y > GLOBAL_WINDOW_HEIGHT || temp_y < 0)
	//	return;

	//  Ensure we are not colliding with other sprite
	//  Check collision will return true if it is a full collision
	//  Would could have had a partial collision on one more more
	//  objects so we need to make sure we can move else change
	//  Direction.
	if(checkCollision(temp_x, temp_y) || (temp_x != getPosX() && temp_y !=  getPosY()))
	{
		//  Enemy has hit something change direction
		if(getCollision() == ENEMY)
		{
			randomMove();
			return;
		}
	}

	// Not touching until we say they are

	mTouch_bottom 	= false;
	mTouch_top		= false;
	mTouch_left		= false;
	mTouch_right	= false;

	// Means we are attempting to move down on the Y axis (With gravity)
	if(y > 0)
	{
		//  Attempt failed
		if(temp_y == getPosY())
		{
			mTouch_bottom = true;
			mContinuousKeyboardVer = 0;
			//mWorldPhysics->killFallSpeed();
			//mWorldPhysics->setJump(false);
		}
	}
	else if (y < 0) //Attempting to move up
	{
		//  Attempt failed
		if(temp_y == getPosY())
		{
			mTouch_top = true;
			mContinuousKeyboardVer = 0;
		}

		//  Come back to this
		//  we cannot move up unless we climb
		//  we would need to collide with a climbable object
		//return;
	}
	else
	{
		//  We did not move up or down but we need to assume we are still touching bottom
		mTouch_bottom = true;
	}

	//  Attempting to move right
	if(x > 0)
	{
		if(temp_x == getPosX())
		{
			mTouch_right = true;
		}

	}
	else if(x < 0)//  Attempting to move left
	{
		if(temp_x == getPosX())
		{
			mTouch_left = true;
		}

	}

	SpriteBase::setPos(temp_x, temp_y);
}

// Sprite move function
void SpriteRect::move()
{
	int x = 0;
	int y = 0;
	bool changed = false;
	MoveLast temp = mMoveLast;
	if(mMoving_left)
	{
		if(mTouch_bottom)
		{
			x--;
			changed = true;
			mMoveLast = LEFT;
		}
	}

	if(mMoving_right)
	{
		if(mTouch_bottom)
		{
			x++;
			changed = true;
			mMoveLast = RIGHT;
		}
	}

	if(mMoving_up)
	{
		if(mOnClimbableObject)
		{
			y--;
			changed = true;
			mMoveLast = UP;
		}
	}

	if(mMoving_down)
	{
		y++;
		changed = true;
		mMoveLast = DOWN;
	}

	if(mJumpPower > 0)
	{
		y--;
	}

	if (changed)
	{
		//  Check to see if we have changed direction is so kill speed
		if(mMoveLast != temp )
		{
			if(!mTouch_bottom)
			{
				if(temp == LEFT)
				{
					x--;
				}
				if(temp ==RIGHT)
				{
					x++;
				}
			}
			else
			{
				mContinuousKeyboardHor = 0;
			}
		}
		//  We have continuously moved in a direction.
		if(mMoveLast == LEFT || mMoveLast == RIGHT)
			mContinuousKeyboardHor++;

		if(mMoveLast == UP || mMoveLast == DOWN)
			mContinuousKeyboardVer++;


		// Or maybe we can move left and right but only up if we can climb
		if(mMoveLast == UP && !mOnClimbableObject && mJumpPower >! 0)
			y = 0;

		applySpeed(x,y);
		//  Set the sprite image to transition through.
		if (getCollision() == PLAYER)
		{
			setSpriteSheetImage(mMoveLast);
		}
	}
	else // We have stopped pressing a direction though we should check the vertical vrs horizontal
	{
		if(mMoveLast == RIGHT)
		{
			x++;
		}
		else if (mMoveLast == LEFT)
		{
			x--;
		}

		//  Will move only if this has a value.
		if(mTouch_bottom)
		{
			if(mContinuousKeyboardHor > 0)
			{
				LOG("Decreasing");
				mContinuousKeyboardHor--;
			}
		}
		applySpeed(x,y);
		//  Tapering off the animation i.e. slowing to a stop
		if (getCollision() == PLAYER && mContinuousKeyboardHor > 0)
		{
			setSpriteSheetImage(mMoveLast);
		}
	}
}

// SDL scancode for keyboard inputs
void SpriteRect::keyboardControl()
{
	const Uint8 * keystate = SDL_GetKeyboardState(NULL);
	if (keystate[SDL_SCANCODE_LEFT] )
	{
		setMovingLeft(true);
	}
	else
	{
		setMovingLeft(false);
	}

	if (keystate[SDL_SCANCODE_RIGHT])
	{
		setMovingRight(true);
	}
	else
	{
		setMovingRight(false);
	}

	if (keystate[SDL_SCANCODE_UP])
	{
		//  Moving up top view vrs side view needs to be looked at.
		setMovingUp(true);
	}
	else
	{
		setMovingUp(false);
	}

	if (keystate[SDL_SCANCODE_DOWN])
	{
		setMovingDown(true);
	}
	else
	{
		setMovingDown(false);
	}

	if (keystate[SDL_SCANCODE_X])
	{
		setSpeedPressed(true);
	}
	else
	{
		setSpeedPressed(false);
	}

	if (keystate[SDL_SCANCODE_SPACE])
	{
		jump();
		//setMovingUp(true);
	}
}

// Enemy random direction changer
void SpriteRect::randomMove()
{
	int direction = rand() % 8 + 1;

	mMoving_left = false;
	mMoving_right = false;
	mMoving_up = false;
	mMoving_down = false;

	switch (direction)
	{
	case 1:
		mMoving_left = true;
		break;
	case 2:
		mMoving_left = true;
		mMoving_up = true;
		break;
	case 3:
		mMoving_left = true;
		mMoving_down = true;
		break;
	case 4:
		mMoving_right = true;
		break;
	case 5:
		mMoving_right = true;
		mMoving_up = true;
		break;
	case 6:
		mMoving_right = true;
		mMoving_down = true;
		break;
	case 7:
		mMoving_up = true;
		break;
	case 8:
		mMoving_down = true;
		break;
	}
}

// get the distanace squared
double SpriteRect::distanceSquared(int x1, int y1, int x2, int y2)
{
	int deltaX = x2 - x1;
	int deltaY = y2 - y1;
	return deltaX*deltaX + deltaY*deltaY;
}

// check collisions
bool SpriteRect::checkCollision(SpriteRect& rect, SpriteCirc& circle)
{
	int cX, cY;
	int cirX = circle.getPosX() + circle.getRadius();
	int cirY = circle.getPosY() + circle.getRadius();
	//LOG(" X : "<< circle.getPosX() << " Y : " << circle.getPosY() << " R : " << circle.getRadius());

	if( cirX < rect.getPosX())
	{
		cX = rect.getPosX();
	}
	else if(cirX > rect.getPosX() + rect.getWidth())
	{
		cX = rect.getPosX() + rect.getWidth();
	}
	else
	{
		cX = cirX;
	}

	if (cirY < rect.getPosY())
	{
		cY = rect.getPosY();
	}
	else if(cirY > rect.getPosY() + rect.getHeight())
	{
		cY = rect.getPosY() + rect.getHeight();
	}
	else
	{
		cY = cirY;
	}


	//LOG("CircX : " << cirX << " CircY : " << cirY << " BoxX : " << cX << " BoxY : " << cY);

	// There is an issue of precision here where we can get stuck
	// Need to come back to this.
	if(distanceSquared(cirX, cirY, cX, cY) < circle.getRadius() * circle.getRadius())
	{
		if(distanceSquared(cirX, cirY, cX, cY) >= mCircleSpritePrecision)
		{
			//  We could be moving away
			mCircleSpritePrecision = distanceSquared(cirX, cirY, cX, cY);
			return false;
		}
		mCircleSpritePrecision = distanceSquared(cirX, cirY, cX, cY);
		LOG(distanceSquared(cirX, cirY, cX, cY) << " : " << (circle.getRadius() * circle.getRadius()));
		// Rectangle and circle have hit
		return true;
	}
	return false;
}

bool SpriteRect::checkCollision(int& x, int& y)
{
	//  I think this can be simplified.
	mOnClimbableObject = false;

	// Check other game objects and detect if he have hit one
	for(SpriteList::iterator it = getSpriteList()->begin(); it != getSpriteList()->end(); ++it)
	{
		//SpriteRect* sprite = static_cast<SpriteRect*>(*it);
		SpriteBase* sprite = (*it);

		// just and image with no collision
		if(sprite->getCollision() == NO_COLLISION)
			continue;

		if (sprite->getIndex() != getIndex())
		{
			// Check Collision will only ever get called for Rectangles
			// But we can still have other sprites like circles in our list
			if(sprite->getType() == Circle)
			{
				SpriteCirc* circle = static_cast<SpriteCirc*>(sprite);
				if(checkCollision(*this, *circle))
				{
					x = getPosX();
					y = getPosY();
					return true;
				}
				else
				{
					return false;
				}

			}
			// Visulisation of what we are trying to achieve
			/*
			    If the top left x---- object is less than the top right ----x off another object on the X axis.
			     				¦   ¦                            <--    ¦   ¦
								-----                                   -----
			    And greater than the top left of the same object        x---- on the X axis
			                                                     -->    ¦   ¦
			                                                            -----

			    And the top left x---- is less than  ^ the bottom left ----- on the Y axis
			                     ¦   ¦               ¦                 ¦   ¦
			                     -----                                 x----
			    And the bottom left ----- is greater ¦ than the top left x---- of the Y axis
			                        ¦   ¦            v                   ¦   ¦
			                        x----                                -----
			*/
			if ((x < sprite->getPosX() + sprite->getWidth() && x > sprite->getPosX()) &&
				(y < sprite->getPosY() + sprite->getHeight() && y + getHeight() > sprite->getPosY()))
			{
				if(this->getCollision() == PLAYER)
				{
					if (sprite->getCollision() == CLIMBABLE)
					{
						mOnClimbableObject = true;
						return false;
					}
				}
				bool not_diagonal = true;
				if (x != getPosX() && y != getPosY())
				{
					if(!((getPosY() < sprite->getPosY() + sprite->getHeight()) && (getPosY() + getHeight() > sprite->getPosY())))
					{
						y = getPosY();
						not_diagonal = false;
					}

					if (!((getPosX() < sprite->getPosX() + sprite->getWidth() && getPosX() > sprite->getPosX())) && not_diagonal)
					{
						x = getPosX();
						not_diagonal = false;
					}

				}

				//  Essentially not moving.
				if (not_diagonal)
				{
					x = getPosX();
					y = getPosY();
					return true;
				}
			}

			if((x + getWidth() > sprite->getPosX() && x + getWidth() < sprite->getPosX() + sprite->getWidth()) &&
			   (y < sprite->getPosY() + sprite->getHeight() && y + getHeight() > sprite->getPosY()))
			{
				if(this->getCollision() == PLAYER)
				{
					if (sprite->getCollision() == CLIMBABLE)
					{
						mOnClimbableObject = true;
						return false;
					}
				}

				bool not_diagonal = true;
				if (x != getPosX() && y != getPosY())
				{
					if(!((getPosY() < sprite->getPosY() + sprite->getHeight() && getPosY() + getHeight() > sprite->getPosY())))
					{
						y = getPosY();
						not_diagonal = false;
					}

					if(!((getPosX() + getWidth() > sprite->getPosX() && getPosX() + getWidth() < sprite->getPosX() + sprite->getWidth())) && not_diagonal)
					{
						x = getPosX();
						not_diagonal = false;
					}
				}
				//  Essentially not moving.
				if (not_diagonal)
				{
					x = getPosX();
					y = getPosY();
					return true;
				}
			}

			if((y < sprite->getPosY() + sprite->getHeight() && y > sprite->getPosY()) &&
			   (x < sprite->getPosX() + sprite->getWidth() && x + getWidth() > sprite->getPosX()))
			{
				if(this->getCollision() == PLAYER)
				{
					if (sprite->getCollision() == CLIMBABLE)
					{
						mOnClimbableObject = true;
						return false;
					}
				}

				bool not_diagonal = true;
				if (x != getPosX() && y != getPosY())
				{
					if(!((getPosY() < sprite->getPosY() + sprite->getHeight() && getPosY() > sprite->getPosY())))
					{
						y = getPosY();
						not_diagonal = false;
					}

					if (!(getPosX() < sprite->getPosX() + sprite->getWidth() && getPosX() + getWidth() > sprite->getPosX()) && not_diagonal)
					{
						x = getPosX();
						not_diagonal = false;
					}
				}

				if (not_diagonal)
				{
					x = getPosX();
					y = getPosY();
					return true;
				}
			}

			if((y + getHeight() > sprite->getPosY() && y + getHeight() < sprite->getPosY() + sprite->getHeight()) &&
			   (x < sprite->getPosX() + sprite->getWidth() && x + getWidth() > sprite->getPosX()))
			{
				if(this->getCollision() == PLAYER)
				{
					if (sprite->getCollision() == CLIMBABLE)
					{
						mOnClimbableObject = true;
						return false;
					}
				}

				bool not_diagonal = true;

				if (x != getPosX() && y != getPosY())
				{
					if(!(getPosY() + getHeight() > sprite->getPosY() && getPosY() + getHeight() < sprite->getPosY() + sprite->getHeight()))
					{
						y = getPosY();
						not_diagonal = false;
					}

					if(!(getPosX() < sprite->getPosX() + sprite->getWidth() && getPosX() + getWidth() > sprite->getPosX()) && not_diagonal)
					{
						x = getPosX();
						not_diagonal = false;
					}
				}

				if (not_diagonal)
				{
					x = getPosX();
					y = getPosY();
					return true;
				}
			}
		}
	}

	//  Does not mean we did not have a collision just means it was partial collision
	//  A partial collision only happens if object is moving diagonal.
	return false;
}

// Apply gravity to world
void SpriteRect::applyGravity()
{
	// Or we can just stop on the Climbable object so we stick to it
	if (mOnClimbableObject) // && mMoving_up)
	{
		//  Just in case we jump on a climbable object/
		if(mJumpPower > 0)
		{
			mJumpPower--;
		}
		return;
	}
	mContinuousKeyboardVer++;
	if(!mTouch_bottom)
	{
		if(mJumpPower > 0)
		{
			mJumpPower--;
			if(mJumpPower < 6)
				mContinuousKeyboardVer = 2;

			if(mJumpPower < 3)
				mContinuousKeyboardVer = 1;

			applySpeed(0,0);
		}
		else
		{
			applySpeed(0,1);
		}
	}
	else
	{
		applySpeed(0,1);
		mJumpPower = 0;
	}
}

// Jump function
void SpriteRect::jump()
{
	//LOG("JUMPING" << mTouch_bottom);
	applySpeed(0,1);
	if(mTouch_bottom || mOnClimbableObject)
	{
		if(mSpeedPressed)
		{
			mJumpPower = 13;
		}
		else
		{
			mJumpPower = 10;
		}

		mContinuousKeyboardVer = GLOBAL_MAX_SPEED;
		applySpeed(0,-1); // Need to move off the bottom before the anti-gravity logic gets hit.
	}
}

// Sprite logic so move between sprite images to give the illusion of animated characters
void SpriteRect::setSpriteSheetImage(MoveLast val)
{
	if (val == UP)
	{
		int y = 0; //
		int max_lenth = mSpriteSheetRowNum * mSpriteSheetRowPxSize;
		int x = (getTextRect()->x - mSpriteSheetWidthOffset) + mSpriteSheetRowPxSize;

		if (x >= max_lenth)
			x = 0;

		setTextRectPos(x+mSpriteSheetWidthOffset,y+mSpriteSheetWidthOffset);
	}
	if (val == LEFT)
	{
		int y = mSpriteSheetColPxSize; //
		int max_lenth = mSpriteSheetRowNum * mSpriteSheetRowPxSize;
		int x = (getTextRect()->x - mSpriteSheetWidthOffset) + mSpriteSheetRowPxSize;

		if (x >= max_lenth)
			x = 0;

		setTextRectPos(x+mSpriteSheetWidthOffset,y+mSpriteSheetWidthOffset);
	}
	if (val == DOWN)
	{
		int y = mSpriteSheetColPxSize * 2;
		int max_lenth = mSpriteSheetRowNum * mSpriteSheetRowPxSize;
		int x = (getTextRect()->x - mSpriteSheetWidthOffset) + mSpriteSheetRowPxSize;

		if (x >= max_lenth)
			x = 0;

		setTextRectPos(x+mSpriteSheetWidthOffset,y+mSpriteSheetWidthOffset);
	}
	if (val == RIGHT)
	{
		int y = mSpriteSheetColPxSize * 3;
		int max_lenth = mSpriteSheetRowNum * mSpriteSheetRowPxSize;
		int x = (getTextRect()->x - mSpriteSheetWidthOffset) + mSpriteSheetRowPxSize;

		if (x >= max_lenth)
			x = 0;

		setTextRectPos(x+mSpriteSheetWidthOffset,y+mSpriteSheetWidthOffset);
	}
}

// Load image
void SpriteRect::loadImage  (std::string path, int rowNum, int colNum, int rowPx, int colPx, int width_offset, int height_offset)
{
	SpriteBase::loadImage(path);
	mSpriteSheetRowNum = rowNum;
	mSpriteSheetColNum = colNum;
	mSpriteSheetRowPxSize = rowPx;
	mSpriteSheetColPxSize = colPx;
	mSpriteSheetWidthOffset = width_offset;
	mSpriteSheetHeightOffset = height_offset;

}

// apply speed to actions
void SpriteRect::applySpeed(int x, int y)
{
	//  This means we are moving left or right walking
	if(mSpeedPressed && mContinuousKeyboardHor > GLOBAL_RUN_SPEED)
	{
		mContinuousKeyboardHor = GLOBAL_RUN_SPEED;
	}

	//  This means we are moving up on something
	if( mMoveLast == UP && mContinuousKeyboardVer > GLOBAL_WALK_SPEED)
	{
		mContinuousKeyboardVer = GLOBAL_WALK_SPEED;
	}
	//  This should mean we are falling and we want a max fall speed
	if( (!mTouch_bottom && !mOnClimbableObject) && mContinuousKeyboardVer > GLOBAL_FALL_SPEED)
	{
		mContinuousKeyboardVer = GLOBAL_FALL_SPEED;
	}

	//  This means we are pressing x so we are running
	if(!mSpeedPressed && mContinuousKeyboardHor > GLOBAL_WALK_SPEED)
	{
		mContinuousKeyboardHor = GLOBAL_WALK_SPEED;
	}

	int temp_x = x * mContinuousKeyboardHor;
	int temp_y = y * mContinuousKeyboardVer;

	setPos(temp_x, temp_y);
}
