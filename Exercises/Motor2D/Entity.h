#ifndef __Entity_H__
#define __Entity_H__

#include <list>

#include "PugiXml\src\pugixml.hpp"
#include "p2Point.h"
#include "j1EntityManager.h"

#include "j1PerfTimer.h"
#include "SDL/include/SDL_rect.h"

struct SDL_Texture;
class Camera;

class Entity 
{
public:

	Entity();

	Entity(fPoint pos);

	virtual ~Entity();
	
	virtual bool Start() { return true; };

	virtual bool PreUpdate() { return true; };

	virtual bool Update(float dt);

	//SDL_Rect * GetRect();

	virtual bool Draw(Camera * camera);

	//virtual bool DrawShadow(Camera * camera, float dt) { return true; }

	virtual bool CleanUp() { return true; };

	virtual bool Awake(pugi::xml_node&) { return true; };

	virtual bool Load(pugi::xml_node&) { return true; };

	virtual bool Save(pugi::xml_node&) const { return true; };

	virtual void DrawDebug(const Camera* camera) {};

public:

	EntityType type = EntityType::NO_TYPE;
	fPoint pos_map		= { 0.f, 0.f };			//The position in the isometric grid. Use app->map->MapToScreenF() to get the position in which to Blit() the Entity.
	fPoint pos_screen	= { 0.f, 0.f };			//The position in the screen. Is measured with pixels. Modifying this value wil have no effect because is overwritten in every frame. Use this instead of calling MapToScreenF.
	fPoint velocity		= { 0.f, 0.f };
	bool to_remove = false;						//Set it to true if you want the Entity to be removed



public:

	SDL_Texture * curr_tex	= nullptr;			//Points the current texture. Shouldn't allocate memory. Just assign the pointer to other textures already created. Used in Entity::PostUpdate(float dt)
	SDL_Rect frame			= { 0, 0, 0, 0 };	//A rect representing the sprite. Used for camera culling. Automatically set if you use curr_anim.
};

#endif
