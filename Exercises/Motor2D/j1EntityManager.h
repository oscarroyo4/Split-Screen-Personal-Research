#ifndef __j1EntityManager_H__
#define __j1EntityManager_H__

#include <list>
#include <vector>

#include "PugiXml/src/pugiconfig.hpp"
#include "PugiXml/src/pugixml.hpp"

#include "j1Module.h"
#include "p2Point.h"

enum class EntityType
{
	NO_TYPE,
	PLAYER
};

class Entity;
class Camera;
class Player;

class j1EntityManager : public j1Module
{
public:

	j1EntityManager();
	~j1EntityManager();

	bool PreUpdate() override;

	bool Update(float dt) override;

	bool PostUpdate() override;

	bool CleanUp() override;

	Entity* CreateEntity(EntityType type, fPoint map_pos);

	void DeleteEntitys();


private:
	std::list<Entity*> Entitys;


};

#endif

