#ifndef __j1RENDER_H__
#define __j1RENDER_H__

#include "SDL/include/SDL.h"
#include "p2Point.h"
#include "p2List.h"
#include "j1Module.h"

class Camera
{
public:
	Camera();

public:
	SDL_Rect rect = { 0, 0, 0, 0 };//The actual camera coordinates in the world
	SDL_Rect screen_section = { 0, 0, 0, 0 };//The section on the screen it covers (ex. player one gets 0, 0, w/2, h/2)
};

class j1Render : public j1Module
{
public:

	j1Render();

	// Destructor
	virtual ~j1Render();

	// Called before render is available
	bool Awake(pugi::xml_node&);

	// Called before the first frame
	bool Start();

	bool CreateCameras();

	// Called each loop iteration
	bool PreUpdate();
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	// Load / Save
	bool Load(pugi::xml_node&);
	bool Save(pugi::xml_node&) const;

	// Utils
	void SetViewPort(const SDL_Rect& rect);
	void ResetViewPort();
	iPoint ScreenToWorld(Camera* cam, int x, int y) const;

	// Draw & Blit
	bool Blit(SDL_Texture* texture, int x, int y, Camera* cam, const SDL_Rect* section = NULL, float speed = 1.f, double angle = 0, int pivot_x = INT_MAX, int pivot_y = INT_MAX) const;

	bool IsOnCamera(const int& x, const int& y, const int& w, const int& h, Camera* camera) const;

	// Set background color
	void SetBackgroundColor(SDL_Color color);

public:
	int max_cameras = 4;
	int num_of_cameras;
	int margin;
	p2List<Camera*>		cameras;
	SDL_Renderer*		renderer;
	SDL_Rect			viewport;
	SDL_Color			background;
};

#endif // __j1RENDER_H__