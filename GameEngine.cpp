//============================================================================
// Name        : GameEngine.cpp
// Author      : James McSkeane
// Version     :
// Copyright   : Your copyright notice
// Description : Game Engine C++, Ansi-style
//============================================================================

#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include <sstream>
#include "GlobalDefinitions.h"
#include "SpriteRect.h"
#include "World.h"
#include "LTimer.h"
using namespace std;

// Set frame rate of refresh
void setRate(Uint32 start_tick)
{
	if((1000/GLOBAL_FRAMES_PER_SEC) > SDL_GetTicks() - start_tick)
	{
		SDL_Delay(1000/GLOBAL_FRAMES_PER_SEC -(SDL_GetTicks() - start_tick));
	}
}

// Main thread
int main(int argc, char* argv[]) {

	// Start SDL2
	SDL_Init(SDL_INIT_EVERYTHING);

	// create world instance initalize and render game world
	World world;
	world.init();
	world.renderWorld();

	SDL_Event event;
	bool running = true;
	//Uint32 start_tick = 0;

	// create two timers for frame rate and cap
	LTimer fpsTimer;
	LTimer capTimer;

	std::stringstream timeString;
	int count = 0;
	fpsTimer.start();

	// while our game is running
	while(running)
	{
		capTimer.start();
		//Calculate and correct fps

		// SDL implementation around even run until we get SDL_QUIT
		// which is assigned to X on event window
		while(SDL_PollEvent(&event))
		{
	       	if(event.type == SDL_QUIT)
	        {
	       		running = false;
	       		break;
	        }

	       	world.getPlayer()->keyboardControl();
		}

		// Apply functions to game render has user moved player
		// is gravity being applied to user
		world.getPlayer()->move();
		world.getPlayer()->applyGravity();
		//world.getEnemy()->move();
		world.renderWorld();

		// Work out the frame rate per second, set to around 60
		// frames per second
		float avgFPS = count / ( fpsTimer.getTicks() / 1000.f );
		if( avgFPS > 2000000 )
		{
			avgFPS = 0;
		}

		timeString.str("");
		timeString << "Average Frames Per Second " << avgFPS;

		// Logging the frame rate to terminal
		LOG("Frame per seconds are" << timeString.str());

		count++;
		//setRate(start_tick);

		// If frame finished early
		int frameTicks = capTimer.getTicks();
		if( frameTicks < GLOBAL_FRAME_TICKS_PER_FRAME )
		{
			// Wait remaining time
			// Reason we wait is frame rate impacts on speed and speed impacts
			// on dynamics of the game, we want as close to 60 frames per second as
			// we can get to the game dynamics are cohesive
			SDL_Delay( GLOBAL_FRAME_TICKS_PER_FRAME - frameTicks );
		}
	}

	// Cleanup and Quit
	SDL_Quit();

	return 0;
}
