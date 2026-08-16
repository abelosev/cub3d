*This project has been created as part of the 42 curriculum by vfekete, zaddi*

# cub3d

## Description
The cub3d project is one of the two last graphics design project of the old C 42 school's network Common Core. \
The goal is to recreate a small subset of the famous **Wolfenstein 3D**'s original graphics engine. \
At the time, this ingenious raycasting engine was a huge leap forward in the computer graphics domain, inspiring later classic games such as Doom, which uses a more refined raycasting method allowing for more complicated objects to be rendered. 

### The main idea is straightforward : 
- The program represents a player with a position and a direction
- The player evolves in a two-dimensional grid and is enclosed by walls
- The program should render everything in the filed of view of the player, and the player should be able to move or rotate it's position

### The raycasting, simplified :
- Representing the player and it's orientation using vectors, we can use vector algebra to describe "rays" being emitted from the player, following it's orientation +/- the field of view (we use a plane vector to be added to the original direction)
- For each of these rays, we look for it's first intersection with a wall. (This uses an algorithm called the Digital differential analyser, see **Resources** section)
- Using the data computed by the DDA algorithm, we can transform the data from world/map space to screen space. (The simple Wolfenstein world geometry allows this method to work.)

## Instructions

**Operating system** : Linux or macOS \
**Language** : C \
**Dependendencies** : xorg libxext-dev zlib1g-dev libbsd-dev \
**Build** : 
```
sudo apt-get update && sudo apt-get install xorg libxext-dev zlib1g-dev libbsd-dev
git clone [wherever_you_got_this_code_from] cub3d
cd cub3d
make
```

The cub3d program takes a .cub map file as argument. It should abide the following rules :

-  First, it should contain the path to all textures for each wall's orientation, and the colors for the floor and ceiling:

    - NO ./path_to_the_north_texture
    - SO ./path_to_the_south_texture
    - WE ./path_to_the_west_texture
    - EA ./path_to_the_east_texture
    - F R[0-255],G[0-255],B[0-255]
    - C R[0-255],G[0-255],B[0-255]
- After this data comes the map data which includes :
    - 0 : this map tile is empty, the player can walk on it
    - 1 : this map tile is a wall, the player cannot walk on it
    - N, S, E or W : the player spawns on this tile facing North(**N**), South(**S**), East(**E**) or West(**W**)
    - Whitespaces are the only exception, we allow them for the maps to have different shapes than a rectangle. All spaces must be enclosed by walls or other whitespaces,otherwise they will trigger a parsing error.
    - Any other character will trigger a parsing error

Any other character in the map description will generate a parsing error.

**Run** :
```
./cub3d [your_map_file.cub]
```

**Movements** : \
Classic WASD movements don't act like you've never player a video game before.\
Rotate the camera with left and right arrow.


**Note** : \
This project includes a few of the bonuses mentioned in the subject :
- Wall collisions
- Player rotation with mouse
- A minimap system

To build the bonuses :
```
make bonus
./cub3d_bonus [your_map_file.cub]
```

## Resources
[1/ Goated raycasting article (Lode's blog)](https://lodev.org/cgtutor/raycasting.html) \
[2/ cub3d tutorial for textures](https://ibon-ira-cub3d.mintlify.app/concepts/textures) \
[3/ DDA interactive tutorial](https://aaaa.sh/creatures/dda-algorithm-interactive/) \
[4/ Wikipedia : Raycasting](https://en.wikipedia.org/wiki/Ray_casting)

### AI Usage
We used AI in this project, mostly to discuss and polish our understanding of the underlying mathematics concepts used for this project and validate our parsing.
It was also used to clarify some obscure code lines coming from resources 1 and 2.