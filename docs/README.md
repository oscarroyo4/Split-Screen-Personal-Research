I am [Oscar Royo](https://github.com/oscarroyo4) , student of the [Bachelor’s Degree in Video Games by UPC at CITM](https://www.citm.upc.edu/ing/estudis/graus-videojocs/). This content is generated for the second year’s
subject Project 2, under supervision of lecturer [Marc Garrigó](https://www.linkedin.com/in/mgarrigo/).

To see the full github project go to the repository of the [Split Screen](https://github.com/oscarroyo4/Split_Screen-Personal_Research).

To do the exercises, download the repository and go to the *Exercises* folder.

If you want to see the solution, you can download the repository and go to the *Solution* folder.

There is a presentation for this project. You can check it out [here](https://docs.google.com/presentation/d/1DIwF2yxN7bLa2aXyK9HJKx6QBOugMJ8Q1V9O3mZr850/edit?usp=sharing).


# Split Screen
Split screen is the capacity of a software to split X times their window with a horizontal or vertical orientation. The objective is that the user or player can see different areas of the same or other softwares at the same time.

## When we need a split screen?
It's an option to implement when we have multiple primary focus points that we need to have at the same time on the screen and under control. Some exemples of software that use this technique can be any 3D modeling program. In video games, the common case is a game with local multiplayer, but not all local multiplayer games need a split screen. If the players can not separate from each other and leave the screen on the stage, you can search for an alternative to the split screen.

Some exemples of this are the games *overcoocked* or *Cuphead*, that the players can not go out off the screen. Examples of local multiplayer games that need a split screen are any racing game or shooter, both players need the control of their character and camera.

## Alternatives to the split screen
Depending of the game, we don't need to implement a split screen, we can take an alternative that fulfills the function we need. Here are some alternatives and their advantages and disadvantages.

**The screen blocks the player if he tries to pass it.**
This is the tipically option that developers do when they don't want to imlement a split screen. Games like *Wizard of Legends* or *Unravel* want the players to stay together, blocking the option to separate.

**Players can move off the screen.**
This is a terrible option. The players can go off the screen and they can not see where they are. Practically no game uses this option.

**Kill the player if he tries to pass the screen.**
This is a radical option. Only usefull in games that we want to punish the player for going off screen. Competitive fighting games like *Smash Bros* implement this option because the objective is to avoid leaving the map and throwing the opponent out. In general cases, it's very anoying to the player.

**Teleport the player to the group.**
This option also feels anoying, but at least we don't kill the player. When a player goes too far away from the other ones, it is teleported to the group.

**The player can drag the screen and the other players.**
If the player is pushing an edge of the screen he drags it, and the other players too. This option affects the player's gameplay, not only his own gameplay, but also the other player's gameplay. 

**Zoom out to keep players inside the screen.**
In this option, the camera zooms out when the players move away from each other to keep the players inside the screen up to a limit, but it doesn't resolve the problems.

**Split screen.**
If we choose this option, we resolve the previous problems and we don't affect the gameplay of the players, but we find other problems. We can give to each player their own camera and the total control of it, but they will lose a 50% or 75% of their screen depending if they are 2, 3 or more players. An example is any game in first person with local multiplayer, it needs a split screen because each player needs to have their own camera but every player will lose part of his screen. Another problem is the large amount of resources we spend on the split screen, because it is necessary to paint the game more times per frame, one time for each camera. This is one of the most important reasons why the split screen is not used in this days. 

In most cases in local multiplayer games, more exactly in cooperative games, most of the time the players are together, and we are spending a lot of resources needlessly. If we have this situation, we can imeplement the Voronoi split screen.

## Voronoi Split Screen
In the Voronoi split screen, when the players are together, the screen is not splitted. But when the players are outside the range of the camera, the screen is splitted between them, indicating the direction of where the other players are. With this technique, when the players are together, we are not spending unnecessary resources and we are not limiting the size of their screen because they share the same camera until they separate. Many games are using Voronoi with 2 players, for example someones of the saga "*Lego*" like *LEGO Marvel Super Heroes*.

![](Voronoi_2_Players.gif)

*Test of Voronoi with 2 players in Unreal.*

With two players, Voronoi works pretty well. But when we add 4 players in total its a little bit caothic, because all cameras are moving between them and changing their position or mergering between each other. The shape and size of each camera is different and strange, causing confusion to the players. Personally, i don't recommend to use Voronoi with more than 2 players. Practically, no game is using Voronoi with more than 2 players.

![](Voronoi_4_Players.gif)

*Test of Voronoi with 4 players in c++.*

## Games that create new windows
Some games have multiple primary focus points, but don't have a local multiplayer mode. In this cases, this games can create new windows with their own camera, to see the primary focus points that the player wants. This games don't need a split screen and the player can chose what points and how meny he wants to have. They are usually management games, an example is *Roller Coaster Tycoon*, the first one.

![](MultipleWindows.jpg)

*Gif of Roller Coaster Tycoon with some windows.*

# Our Split Screen and implementation
We will make a normal split screen capable of splitting 1, 2, 3 or 4 cameras (camera quantity is limited to 4 because of the screen size). It will not be Voronoi because they don't use rects and it's very complex. Also we will add a camera culling system to increase performance.

3 Cameras | 4 Cameras
![alt](Solution_3Cams.PNG) | ![alt](Solution_4Cams.PNG)

## Important changes (code)
1. Now we have a new class Camera in the j1Render.h that has two Rects. The rect is the actual coordinates of the camera in the world, and the screen_section is the size and position of each camera in the screen.

```
class Camera
{
public:
	Camera();

public:
	SDL_Rect rect = { 0, 0, 0, 0 };//The actual camera coordinates in the world.
	SDL_Rect screen_section = { 0, 0, 0, 0 };//The section on the screen it covers.
};
```

2. For each blit of the map we have to do a for to go through all cameras and check if the tile is inside the camera view:

```
void j1Map::Draw()
{
	if(map_loaded == false)
		return; 

	for (int i = 0; i < App->render->num_of_cameras; i++) {
		Camera* cam = App->render->cameras.At(i)->data;

		SDL_RenderSetClipRect(App->render->renderer, &cam->screen_section);

		p2List_item<MapLayer*>* item = data.layers.start;

		for (; item != NULL; item = item->next)
		{
			MapLayer* layer = item->data;

			if (layer->properties.Get("Nodraw") != 0)
				continue;

			for (int y = 0; y < data.height; ++y)
			{
				for (int x = 0; x < data.width; ++x)
				{
					int tile_id = layer->Get(x, y);
					if (tile_id > 0)
					{
						TileSet* tileset = GetTilesetFromTileId(tile_id);

						SDL_Rect r = tileset->GetTileRect(tile_id);
						iPoint pos = MapToWorld(x, y);

						
						if(App->render->IsOnCamera(pos.x,pos.y,tileset->tile_width,tileset->tile_height,cam))
							App->render->Blit(tileset->texture, pos.x, pos.y, cam, &r);
					}
				}
			}
		}
		SDL_RenderSetClipRect(App->render->renderer, nullptr);
	}
}
```

3. The blit funcion now has a camera parameter so we print on each camera separately.

```
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
```
## Exercicies
### TODO 1
In the config file create a new child called camera that stores the quantity of cameras and the margin between them.
### TODO 2
On the Awake function of j1Render.cpp load the two variables from the config file and execute the function to create the cameras. There are some variables in this module to store this values.
### TODO 3
We check if the width of each camera is smaller than half of the screen height.

TODO 3.1: Here we add a row and check if the number of cameras is pair. If it is, the number of columns will depend in the rows (you have to make a little operation), else we add a column and set the resize variable to true.

TODO 3.2: The number of columns will be the number of cameras.
### TODO 4
We need to change the current column and current row when we finish each loop. Remember that if we change the current row the current column has to be 0 again.
### TODO 5
Add the modified auxiliar camera to the cameras list.
### TODO 6
In the IsOnCamera() function create two local rects, one for the texture we are checking (keep in mind the scale) and one for the camera position in screen. After this, check if they have intersect with eachother.
### TODO 7
Now it shoud work, the only thing is the movement of the cameras. In the j1Scene.cpp uncomment this part and every camera will move with their respective keys.
## Improvements
Some problems with this system are:

- The number of cameras is fixed during execution. You could implement a change of the number of cameras in real-time, you have to add a DeleteCameras() funciton and a variable input in the CreateCameras() function to tell it how many cameras to create.
- You can't decide where to place each camera. For example, you can't place the camera 1 in the right bottom corner, it will always follow an order.
- Also it doesn't have the option to do Voronoi Split screen. If you are interested in how to implement a Voronoi Split screen, here you can find some information:

https://mattwoelk.github.io/voronoi_split_screen_notes/

https://www.reddit.com/r/gaming/comments/5hehly/why_arent_developers_doing_split_screen_anymore/

https://www.youtube.com/watch?v=tu-Qe66AvtY (25:36s)
