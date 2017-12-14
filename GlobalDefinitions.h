/*
 * GlobalDefinitions.h
 *
 *  Created on: 28 Oct 2015
 *      Author: jamesmcskeane
 */

#ifndef GLOBALDEFINITIONS_H_
#define GLOBALDEFINITIONS_H_

#include <iostream>

#define LOG(x) std::cout << x << std::endl

// create global definitions to out game worlds
const int GLOBAL_WINDOW_HEIGHT 	= 600;
const int GLOBAL_WINDOW_WIDTH	= 700;
const int GLOBAL_WORLD_HEIGHT	= 600;
const int GLOBAL_WORLD_WIDTH	= 2100;
const int GLOBAL_FRAMES_PER_SEC = 60;
const int GLOBAL_FRAME_TICKS_PER_FRAME = 1000 / GLOBAL_FRAMES_PER_SEC;
const int GLOBAL_MAX_SPEED		= 4;
const int GLOBAL_WALK_SPEED		= 4;
const int GLOBAL_RUN_SPEED		= 6;
const int GLOBAL_FALL_SPEED		= 10;

// global collision state for objects
enum Collision{
			NOTHING,
			ENEMY,
			BOUNCE,
			CLIMBABLE,
			PLAYER,
			NO_COLLISION
		};

// object for now will be of two types rectangle
// and circle
enum SpriteType{
			Rect,
			Circle
};

#endif /* GLOBALDEFINITIONS_H_ */
