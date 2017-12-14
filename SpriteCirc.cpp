/*
 * SpriteCirc.cpp
 *
 *  Created on: 15 Dec 2015
 *      Author: jamesmcskeane
 */

#include "SpriteCirc.h"
#include <iostream>
#include <math.h>
#include <cmath>

using namespace std;

// Constructor
SpriteCirc::SpriteCirc(Uint8 index,
					   int pos_x,
					   int pos_y,
					   int radius,
					   SDL_Renderer* render,
					   Collision col,
					   SpriteList* list)
					   : SpriteBase(index, pos_x, pos_y, radius*2, radius*2, render, col, list, Circle)
					   , mRadius(radius)

{

}

// Deconstructor
SpriteCirc::~SpriteCirc()
{

}

// Fill color fills the color of circle
void SpriteCirc::fillColor(Uint32 r, Uint32 g, Uint32 b)
{
	SDL_Surface* surface = SDL_CreateRGBSurface(0, getTextRect()->w, getTextRect()->h, 32,0,0,0,0 );
	Uint32 background = SDL_MapRGB(surface->format, 255, 255, 255);
	SDL_FillRect(surface, NULL, background);

	int total = getTextRect()->w * getTextRect()->h;
	int middle = total/2;

	Uint32* pix = (Uint32*)surface->pixels;
	pix[middle] = SDL_MapRGB(surface->format, 181,38,62);

	//TODO work in progress

	/*int cx = getTextRect()->x;
	int cy =  getTextRect()->y;

	static const int BPP = 4;
	double rad = (double)mRadius;

	for(double dy = 1; dy <= rad; dy += 1.0)
	{
		double dx = floor(sqrt((2.0 * rad * dy) - (dy * dy)));
		int x = cx - dx;

		// Grab a pointer to the left-most pixel for each half of the circle
		Uint32 *target_pixel_a = (Uint32 *)surface->pixels + ((int)(cy + rad - dy)) * surface->pitch + x * BPP;
		Uint32 *target_pixel_b = (Uint32 *)surface->pixels + ((int)(cy - rad + dy)) * surface->pitch + x * BPP;

		for (; x <= cx + dx; x++)
		{
			*(Uint32 *)target_pixel_a = SDL_MapRGB(surface->format, 181,38,62);
			*(Uint32 *)target_pixel_b = SDL_MapRGB(surface->format, 181,38,62);
			target_pixel_a += BPP;
			target_pixel_b += BPP;
		}

	}*/

	//SDL_FillRect(surface, NULL, background);
	setTexture(SDL_CreateTextureFromSurface(getRenderer(), surface));
	SDL_FreeSurface(surface);
}

// get radius of Circle object
int SpriteCirc::getRadius()
{
	return mRadius;
}

