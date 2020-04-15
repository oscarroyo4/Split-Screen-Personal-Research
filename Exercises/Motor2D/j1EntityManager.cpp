
#include <string>
#include "PugiXml/src/pugiconfig.hpp"
#include "PugiXml/src/pugixml.hpp"

#include "j1EntityManager.h"
#include "App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "Entity.h"
#include "j1Window.h"
#include "j1Scene.h"

#include "PugiXml/src/pugiconfig.hpp"
#include "PugiXml/src/pugixml.hpp"

#include "Player.h"

#include "j1Map.h"
#include "Camera.h"


j1EntityManager::j1EntityManager()
{
	name.assign("Entity_manager");
}

// Destructor
j1EntityManager::~j1EntityManager()
{

}

bool j1EntityManager::PreUpdate()
{
	std::list<Entity*>::iterator iterator;

	for (iterator = Entitys.begin(); iterator != Entitys.end(); iterator++)
	{
		if ((*iterator) != nullptr)
		{
			(*iterator)->PreUpdate();
		}
	}
	return true;
}

bool j1EntityManager::Update(float dt)
{

	for (std::list<Entity*>::iterator iterator = Entitys.begin(); iterator != Entitys.end(); ++iterator)
	{
		if ((*iterator) != nullptr)
		{
			(*iterator)->Update(dt);
		}
	}
	
	return true;
}

bool j1EntityManager::PostUpdate()
{
	for (std::vector<Camera*>::iterator item_cam = App->render->cameras.begin(); item_cam != App->render->cameras.end(); ++item_cam)
	{
		SDL_RenderSetClipRect(App->render->renderer, &(*item_cam)->screen_section);
		
		for (std::list<Entity*>::iterator item = Entitys.begin(); item != Entitys.end(); ++item)
		{
			(*item)->Draw(*item_cam);
		}
    }
	SDL_RenderSetClipRect(App->render->renderer, nullptr);
   
	return true;
}

// Called before quitting
bool j1EntityManager::CleanUp()
{
	DeleteEntitys();

	return true;
}

Entity* j1EntityManager::CreateEntity(EntityType type, fPoint pos)
{
	Entity* ret = nullptr;
	switch (type)
	{
	case EntityType::PLAYER:
		ret = new Player(pos);
		ret->type = EntityType::PLAYER;
		break;
	}
	  
	if (ret != nullptr)
	{
		ret->Start();
		Entitys.push_back(ret);
	}
  
	return ret;
}


void j1EntityManager::DeleteEntitys()
{
	for (std::list<Entity*>::iterator iterator = Entitys.begin(); iterator != Entitys.end(); ++iterator)
	{
		if ((*iterator) != nullptr)
		{
			(*iterator)->CleanUp();
			delete (*iterator);
			(*iterator) = nullptr;
		}
	}

	Entitys.clear();
}

