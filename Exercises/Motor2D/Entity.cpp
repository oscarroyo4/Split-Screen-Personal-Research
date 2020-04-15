#include <list>

//#include "Brofiler/Brofiler.h"

#include "App.h"
#include "Entity.h"

#include "j1EntityManager.h"
#include "j1Render.h"
#include "j1Scene.h"
#include "j1Map.h"

Entity::Entity()
{
}

Entity::Entity(fPoint pos) : pos_map(pos)
{
}

Entity::~Entity()
{

}


bool Entity::Update(float dt)
{
	return true;
}

bool Entity::Draw(Camera * camera)
{

	pos_screen = App->map->MapToScreenF(pos_map);

	if (frame.w != 0 && frame.h != 0)
	{
		App->render->Blit(
			curr_tex,
			pos_screen.x,
			pos_screen.y,
			camera,
			&frame);
	}

	else
	{
		App->render->Blit(
			curr_tex,
			pos_screen.x,
			pos_screen.y,
			camera);
	}
	return true;
}

