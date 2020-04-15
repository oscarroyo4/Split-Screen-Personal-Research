#ifndef __j1RENDER_H__
#define __j1RENDER_H__

#include "SDL/include/SDL.h"
#include "p2Point.h"
#include "p2List.h"
#include "j1Module.h"

enum class RESIZETYPE
{
	NO_TYPE = 0,
	SQUARE_ORDER,			//All cameras have the same width and height, even if it is not square order the maximum number of cameras.
	HORIZONTAL,				//The cameras aux will have more width than the rest to occupy the whole row.
	VERTICAL,				//The cameras aux will have more height than the rest to occupy the whole column.
};

class Camera
{
public:
	Camera();

	//void FollowPlayer(float dt, fPoint player);

public:
	SDL_Rect rect = { 0, 0, 0, 0 };//The actual camera coordinates in the world
	SDL_Rect screen_section = { 0, 0, 0, 0 };//The section on the screen it covers (ex. player one gets 0, 0, w/2, h/2)
	bool assigned = false;
	uint number_player = 0u;

private:
	float lerp_factor = 0.f;
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

	//void CreateCameras();

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
	iPoint ScreenToWorld(int x, int y) const;

	// Draw & Blit
	bool Blit(SDL_Texture* texture, int x, int y, Camera* cam, const SDL_Rect* section = NULL, float speed = 1.f, double angle = 0, int pivot_x = INT_MAX, int pivot_y = INT_MAX) const;
	bool DrawQuad(const SDL_Rect& rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255, bool filled = true, bool use_camera = true) const;
	bool DrawLine(int x1, int y1, int x2, int y2, Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255, bool use_camera = true) const;
	bool DrawCircle(int x1, int y1, int redius, Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255, bool use_camera = true) const;

	bool IsOnCamera(const int& x, const int& y, const int& w, const int& h, Camera* camera) const;

	// Set background color
	void SetBackgroundColor(SDL_Color color);

public:

	SDL_Renderer*		renderer;
	Camera*				camera;
	Camera*				camera2;
	SDL_Rect			viewport;
	SDL_Color			background;
};

#endif // __j1RENDER_H__