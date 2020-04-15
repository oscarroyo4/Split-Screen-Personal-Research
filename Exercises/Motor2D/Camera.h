#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "SDL/include/SDL.h"
#include "Player.h"
#include "p2Point.h"

class Camera
{
public:
	Camera();

	void FollowPlayer(float dt, Player * player);
	fPoint lerp(fPoint v0, fPoint v1, float t);

public:
	SDL_Rect rect					= { 0, 0, 0, 0 };//The actual camera coordinates in the world
	SDL_Rect screen_section			= { 0, 0, 0, 0 };//The section on the screen it covers (ex. player one gets 0, 0, w/2, h/2)
	bool assigned					= false;
	uint number_player				= 0u;

private:
	float lerp_factor		= 0.f;
};

#endif // !__CAMERA_H__
