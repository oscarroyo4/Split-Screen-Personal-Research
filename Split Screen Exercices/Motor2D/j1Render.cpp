#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Window.h"
#include "j1Render.h"

#define VSYNC true

j1Render::j1Render() : j1Module()
{
	name.create("renderer");
	background.r = 0;
	background.g = 0;
	background.b = 0;
	background.a = 0;
}

// Destructor
j1Render::~j1Render()
{}

// Called before render is available
bool j1Render::Awake(pugi::xml_node& config)
{
	LOG("Create SDL rendering context");
	bool ret = true;
	// load flags
	Uint32 flags = SDL_RENDERER_ACCELERATED;

	if(config.child("vsync").attribute("value").as_bool(true) == true)
	{
		flags |= SDL_RENDERER_PRESENTVSYNC;
		LOG("Using vsync");
	}

	renderer = SDL_CreateRenderer(App->win->window, -1, flags);

	if(renderer == NULL)
	{
		LOG("Could not create the renderer! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	else
	{
		//TODO 3: Load the two variables from the config file into the created variables and execute the function to create the cameras.



	}

	return ret;
}

bool j1Render::CreateCameras() 
{
	bool ret = true;

	if (num_of_cameras > max_cameras || num_of_cameras == 0) 
	{
		LOG("Wrong number of cameras");
		ret = false;
	}
	else 
	{
		//TODO 4: Store the screen width and height in local variables. Create four local variables for: the number of columns, the current column,
		// the number of rows and the current row. Also we need a bool to know if we need to resize any of the cameras or not.








		//TODO 5: If the width of each camera is smaller than half of the screen height, we add a row, else columns will be the number of cameras. 
		//Inside the if, if the number of cameras is pair, the number of columns will depend in the rows, else we add a column and set the resize variable to true.










		/*
		//TODO 6: Uncomment this hole part. You will need to adapt the name of some variables.
		for (int num = 0; num < num_of_cameras; num++) 
		{
			Camera* camera_aux = new Camera();

			//Assigning width for each camera
			if (num == num_of_cameras - 1 && resize == true) 
			{
				//If the last camera has to be resized
				camera_aux->rect.w = screen_width;
				camera_aux->screen_section.w = screen_width - (margin * 2);
				camera_aux->screen_section.x = margin;
			}
			else 
			{
				//If the last camera doesn't have to be resized
				camera_aux->rect.w = screen_width / columns;
				camera_aux->screen_section.w = (screen_width / columns) - (margin*2);
				camera_aux->screen_section.x = (camera_aux->screen_section.w * current_column) + (margin * ((current_column*2)+1));
			}
			//Assigning height for each camera
			camera_aux->rect.h = screen_height / rows;
			camera_aux->rect.x = 0;
			camera_aux->rect.y = 0;
			camera_aux->screen_section.h = (screen_height / rows) - (margin*2);
			camera_aux->screen_section.y = (camera_aux->screen_section.h * current_row) + (margin * ((current_row*2)+1));
			
			//TODO 6.1: Here we need to change the current column and current row when we finish each loop. Remember that if we change the current row 
			// the current column has to be 0 again.







			//We add the auxiliar camera to the cameras list.
			cameras.add(camera_aux);
		}
		*/
	}
	return ret;
}

// Called before the first frame
bool j1Render::Start()
{
	LOG("render start");
	// back background
	SDL_RenderGetViewport(renderer, &viewport);
	return true;
}

// Called each loop iteration
bool j1Render::PreUpdate()
{
	SDL_RenderClear(renderer);
	return true;
}

bool j1Render::PostUpdate()
{
	SDL_SetRenderDrawColor(renderer, background.r, background.g, background.g, background.a);
	SDL_RenderPresent(renderer);
	return true;
}

// Called before quitting
bool j1Render::CleanUp()
{
	LOG("Destroying SDL render");
	SDL_DestroyRenderer(renderer);
	return true;
}

// Load Game State
bool j1Render::Load(pugi::xml_node& data)
{

	//camera.x = data.child("camera").attribute("x").as_int();
	//camera.y = data.child("camera").attribute("y").as_int();

	return true;
}

// Save Game State
bool j1Render::Save(pugi::xml_node& data) const
{
	pugi::xml_node cam = data.append_child("camera");

	//cam.append_attribute("x") = camera.x;
	//cam.append_attribute("y") = camera.y;

	return true;
}

void j1Render::SetBackgroundColor(SDL_Color color)
{
	background = color;
}

void j1Render::SetViewPort(const SDL_Rect& rect)
{
	SDL_RenderSetViewport(renderer, &rect);
}

void j1Render::ResetViewPort()
{
	SDL_RenderSetViewport(renderer, &viewport);
}

iPoint j1Render::ScreenToWorld(Camera* cam, int x, int y) const
{
	iPoint ret;
	int scale = App->win->GetScale();

	ret.x = (x - cam->rect.x / scale);
	ret.y = (y - cam->rect.y / scale);

	return ret;
}

// Blit to screen
bool j1Render::Blit(SDL_Texture* texture, int x, int y, Camera* cam, const SDL_Rect* section, float speed, double angle, int pivot_x, int pivot_y) const
{
	bool ret = true;
	uint scale = App->win->GetScale();

	SDL_Rect rect;
	rect.x = (int)(-cam->rect.x * speed) + x * scale;
	rect.y = (int)(-cam->rect.y * speed) + y * scale;
	if(section != NULL)
	{
		rect.w = section->w;
		rect.h = section->h;
	}
	else
	{
		SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
	}

	rect.w *= scale;
	rect.h *= scale;

	SDL_Point* p = NULL;
	SDL_Point pivot;

	if(pivot_x != INT_MAX && pivot_y != INT_MAX)
	{
		pivot.x = pivot_x;
		pivot.y = pivot_y;
		p = &pivot;
	}

	if(SDL_RenderCopyEx(renderer, texture, section, &rect, angle, p, SDL_FLIP_NONE) != 0)
	{
		LOG("Cannot blit to screen. SDL_RenderCopy error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}

bool j1Render::IsOnCamera(const int& x, const int& y, const int& w, const int& h, Camera* cam) const
{
	float scale = App->win->GetScale();
	//TODO 7: Create two local rects, one for the texture we are checking and one for the camera position in screen. After this, check if they intersect with eachother.




}

Camera::Camera()
{

}
