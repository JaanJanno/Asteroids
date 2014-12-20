#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_mixer.h"
#include <SDL/SDL_rotozoom.h>

typedef struct Player
{
	float xpos, ypos;
	float xvel, yvel;
	float xacc, yacc;
	float rpos;
	float rspd;
	int acc;
} Player;

typedef struct Star
{
	SDL_Rect dim;
	int col;
	float dist;
} Star;