#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Map.h"
#include "j1PathFinding.h"
#include "j1Gui.h"
#include "j1Scene.h"

j1Scene::j1Scene() : j1Module()
{
	name.create("scene");
}

// Destructor
j1Scene::~j1Scene()
{}

// Called before render is available
bool j1Scene::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool j1Scene::Start()
{
	if(App->map->Load("iso_walk.tmx") == true)
	{
		int w, h;
		uchar* data = NULL;
		if(App->map->CreateWalkabilityMap(w, h, &data))
			App->pathfinding->SetMap(w, h, data);

		RELEASE_ARRAY(data);
	}

	debug_tex = App->tex->Load("maps/path2.png");

	return true;
}

// Called each loop iteration
bool j1Scene::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool j1Scene::Update(float dt)
{
	//TODO 7: Uncomment this part and every camera will move with their respective keys.
	/*
	if (App->render->num_of_cameras >= 1) 
	{
		if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) App->render->cameras.At(0)->data->rect.y -= floor(200.0f * dt);
		if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) App->render->cameras.At(0)->data->rect.y += floor(200.0f * dt);
		if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) App->render->cameras.At(0)->data->rect.x -= floor(200.0f * dt);
		if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) App->render->cameras.At(0)->data->rect.x += floor(200.0f * dt);
	}
	if (App->render->num_of_cameras >= 2) 
	{
		if (App->input->GetKey(SDL_SCANCODE_T) == KEY_REPEAT) App->render->cameras.At(1)->data->rect.y -= floor(200.0f * dt);
		if (App->input->GetKey(SDL_SCANCODE_G) == KEY_REPEAT) App->render->cameras.At(1)->data->rect.y += floor(200.0f * dt);
		if (App->input->GetKey(SDL_SCANCODE_F) == KEY_REPEAT) App->render->cameras.At(1)->data->rect.x -= floor(200.0f * dt);
		if (App->input->GetKey(SDL_SCANCODE_H) == KEY_REPEAT) App->render->cameras.At(1)->data->rect.x += floor(200.0f * dt);
	}
	if (App->render->num_of_cameras >= 3)
	{
		if (App->input->GetKey(SDL_SCANCODE_I) == KEY_REPEAT) App->render->cameras.At(2)->data->rect.y -= floor(200.0f * dt);
		if (App->input->GetKey(SDL_SCANCODE_K) == KEY_REPEAT) App->render->cameras.At(2)->data->rect.y += floor(200.0f * dt);
		if (App->input->GetKey(SDL_SCANCODE_J) == KEY_REPEAT) App->render->cameras.At(2)->data->rect.x -= floor(200.0f * dt);
		if (App->input->GetKey(SDL_SCANCODE_L) == KEY_REPEAT) App->render->cameras.At(2)->data->rect.x += floor(200.0f * dt);
	}
	if (App->render->num_of_cameras >= 4)
	{
		if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT) App->render->cameras.At(3)->data->rect.y += floor(200.0f * dt);
		if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT) App->render->cameras.At(3)->data->rect.y -= floor(200.0f * dt);
		if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT) App->render->cameras.At(3)->data->rect.x += floor(200.0f * dt);
		if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT) App->render->cameras.At(3)->data->rect.x -= floor(200.0f * dt);
	}
	*/
	App->map->Draw();

	return true;
}

// Called each loop iteration
bool j1Scene::PostUpdate()
{
	bool ret = true;

	if(App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool j1Scene::CleanUp()
{
	LOG("Freeing scene");

	return true;
}
