/*
/ * WorldPhysics.cpp
 *
 *  Created on: 24 Nov 2015
 *      Author: jamesmcskeane
 */
#include "WorldPhysics.h"
#include <iostream>

WorldPhysics::WorldPhysics() : mCurrSpeed(0)
							 , mAcceleration(0)
							 , mMotionCounter(0)
							 , mGravity(0)
							 , mFallCounter(0)
							 , mFallSpeed(0)
							 , mJump(false)

{
}

//  This simply sets the speed at which we update the position.
bool WorldPhysics::getMotionInterval(bool direction, bool speedPressed)
{
	mMotionCounter++;
	// Means direction is being applied we want to speed up and slow down
	if(direction)
	{
		if (mCurrSpeed <= GLOBAL_MAX_SPEED)
		{
			mCurrSpeed++;
		}
	}
	else
	{
		if (mCurrSpeed >= 0)
			mCurrSpeed--;
	}

	if (mCurrSpeed >= GLOBAL_MAX_SPEED)
	{
		if(speedPressed)
		{
			if(mMotionCounter % 10 == 0)
			{
				return true;
			}
		}
		else
		{

			if(mMotionCounter % 15 == 0)
			{
				return true;
			}
		}
	}

	if(mCurrSpeed <= ((GLOBAL_MAX_SPEED/100) * 90) && mCurrSpeed > ((GLOBAL_MAX_SPEED/100) * 80))
	{
		if (mMotionCounter % 20 == 0)
		{
			return true;
		}
	}
	if(mCurrSpeed <= ((GLOBAL_MAX_SPEED/100) * 80) && mCurrSpeed > ((GLOBAL_MAX_SPEED/100) * 70))
	{
		if (mMotionCounter % 25 == 0)
		{
			return true;
		}
	}
	if(mCurrSpeed <= ((GLOBAL_MAX_SPEED/100) * 70) && mCurrSpeed > ((GLOBAL_MAX_SPEED/100) * 60))
	{
		if (mMotionCounter % 30 == 0)
		{
			return true;
		}
	}
	if(mCurrSpeed <= ((GLOBAL_MAX_SPEED/100) * 60) && mCurrSpeed > ((GLOBAL_MAX_SPEED/100) * 50))
	{
		if (mMotionCounter % 35 == 0)
		{
			return true;
		}

	}
	if(mCurrSpeed <= ((GLOBAL_MAX_SPEED/100) * 50) && mCurrSpeed > ((GLOBAL_MAX_SPEED/100) * 40))
	{
		if (mMotionCounter % 38 == 0)
		{
			return true;
		}

	}
	if(mCurrSpeed <= ((GLOBAL_MAX_SPEED/100) * 40) && mCurrSpeed > ((GLOBAL_MAX_SPEED/100) * 30))
	{
		if (mMotionCounter % 40 == 0)
		{
			return true;
		}
	}
	if(mCurrSpeed <= ((GLOBAL_MAX_SPEED/100) * 30) && mCurrSpeed > ((GLOBAL_MAX_SPEED/100) * 20))
	{
		if(mMotionCounter % 45 == 0)
		{
			return true;
		}
	}
	if(mCurrSpeed <= ((GLOBAL_MAX_SPEED/100) * 20) && mCurrSpeed > ((GLOBAL_MAX_SPEED/100) * 10))
	{
		if(mMotionCounter % 50 == 0)
		{
			return true;
		}
	}
	if(mCurrSpeed <= ((GLOBAL_MAX_SPEED/100) * 10) && mCurrSpeed >= 1)
	{
		if(mMotionCounter % 50 == 0)
		{
			return true;
		}
	}

	if(mMotionCounter > GLOBAL_MAX_SPEED)
	{
		//  Reset this does not need to grow
		mMotionCounter = 0;
	}

	return false;
}

bool WorldPhysics::getGravityInterval(bool grav)
{
	mFallCounter++;
	if(grav)
	{
		if (mFallSpeed <= GLOBAL_MAX_SPEED)
			mFallSpeed++;
	}
	else
	{
		if (mFallSpeed >= 0)
			mFallSpeed--;
	}

	if (mFallSpeed >= GLOBAL_MAX_SPEED)
	{
		if(mFallCounter % 10 == 0)
		{
			return true;
		}
	}
	if(mFallSpeed <= ((GLOBAL_MAX_SPEED/100) * 90) && mFallSpeed > ((GLOBAL_MAX_SPEED/100) * 80))
	{
		if (mFallCounter % 20 == 0)
		{
			return true;
		}
	}
	if(mFallSpeed <= ((GLOBAL_MAX_SPEED/100) * 80) && mFallSpeed > ((GLOBAL_MAX_SPEED/100) * 70))
	{
		if (mFallCounter % 25 == 0)
		{
			return true;
		}
	}
	if(mFallSpeed <= ((GLOBAL_MAX_SPEED/100) * 70) && mFallSpeed > ((GLOBAL_MAX_SPEED/100) * 60))
	{
		if (mFallCounter % 30 == 0)
		{
			return true;
		}
	}
	if(mFallSpeed <= ((GLOBAL_MAX_SPEED/100) * 60) && mFallSpeed > ((GLOBAL_MAX_SPEED/100) * 50))
	{
		if (mFallCounter % 35 == 0)
		{
			return true;
		}
	}
	if(mFallSpeed <= ((GLOBAL_MAX_SPEED/100) * 50) && mFallSpeed > ((GLOBAL_MAX_SPEED/100) * 40))
	{
		if (mFallCounter % 38 == 0)
		{
			return true;
		}
	}
	if(mFallSpeed <= ((GLOBAL_MAX_SPEED/100) * 40) && mFallSpeed > ((GLOBAL_MAX_SPEED/100) * 30))
	{
		if (mFallCounter % 40 == 0)
		{
			return true;
		}
	}
	if(mFallSpeed <= ((GLOBAL_MAX_SPEED/100) * 30) && mFallSpeed > ((GLOBAL_MAX_SPEED/100) * 20))
	{
		if (mFallCounter % 45 == 0)
		{
			return true;
		}
	}
	if(mFallSpeed <= ((GLOBAL_MAX_SPEED/100) * 20) && mFallSpeed > ((GLOBAL_MAX_SPEED/100) * 10))
	{
		if(mFallCounter % 50 == 0)
		{
			return true;
		}
	}
	if(mFallSpeed <= ((GLOBAL_MAX_SPEED/100) * 10) && mFallSpeed >= 1)
	{
		if(mFallCounter % 50 == 0)
		{
			return true;
		}
	}

	// Means we have stopped but if jumping it means we hit the tip of our arc
	// We need to set jump to false so we can fall back with gravity
	if(mFallSpeed <= 0)
	{
		mJump = false;
	}

	if(mFallCounter > GLOBAL_MAX_SPEED)
	{
		//  Reset this does not need to grow
		mFallCounter = 0;
	}

	return false;
}

void WorldPhysics::killSpeed()
{
	mCurrSpeed = 0;
}

void WorldPhysics::killFallSpeed()
{
	mFallSpeed = 0;
}

bool WorldPhysics::applyMotionSpeed()
{
	if (mCurrSpeed >= 200)
	{
		if(mCurrSpeed % 3 == 0)
		{
			return true;
		}
	}

	return false;
}

void WorldPhysics::setMotionInterval(int speed)
{
	mCurrSpeed = speed;
}

void WorldPhysics::setFallInterval(int speed)
{
	mFallSpeed = speed;
}

void WorldPhysics::setJump(bool jump)
{
	mJump = jump;
}

bool WorldPhysics::getJump()
{
	return mJump;
}


