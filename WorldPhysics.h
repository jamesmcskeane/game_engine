/*
 * WorldPhysics.h
 *
 *  Created on: 24 Nov 2015
 *      Author: jamesmcskeane
 */

#ifndef WORLDPHYSICS_H_
#define WORLDPHYSICS_H_

#include "GlobalDefinitions.h"

class WorldPhysics
{
public:
	WorldPhysics();


	bool getMotionInterval(bool direction, bool speedPressed);
	bool applyMotionSpeed();
	void setMotionInterval(int speed);
	void setFallInterval(int speed);
	void killSpeed();
	void killFallSpeed();
	bool getGravityInterval(bool grav);
	void setJump(bool jump);
	bool getJump();

private:

	int 	mCurrSpeed;
	int 	mAcceleration;
	int 	mMotionCounter;
	int 	mGravity;
	int 	mFallCounter;
	int 	mFallSpeed;
	bool 	mJump;
};


#endif /* WORLDPHYSICS_H_ */
