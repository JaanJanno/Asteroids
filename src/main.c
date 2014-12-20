/*
	Jaan Janno, 20. detsember, 2014
	Programmeerimine C keeles - lõpuülesanne.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include "main.h"

#define starLimit 100
#define width 800
#define height 600
#define PI 3.14159265358979323846
#define laevaUrl "res/laev.png"

/*
	Tekitab pinna, mille peale hiljem mängu tegevus joonistada.
	Tagastab 0 kui ei õnnestunud, muidu 1.
*/

char initScreen(SDL_Surface **screen) {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("Tekkis viga: %s\n", SDL_GetError());
		return 0;
	}
	if ((*screen = SDL_SetVideoMode(width, height, 0, SDL_HWPALETTE)) == NULL) {
		printf("Tekkis viga: %s\n", SDL_GetError());
		return 0;
	}
	SDL_WM_SetCaption("Asteroids", NULL);
	return 1;
}

/*
	Tekitab hulga tähti, mida hiljem ekraanile joonistada.
*/

void initStars(Star *stars, SDL_Surface *screen) {
	int i, r;
	for (i = 0 ; i < starLimit ; i ++) {
		r = rand() % 4;
		stars[i].dim.x = rand() % width;
		stars[i].dim.y = rand() % height;
		stars[i].dim.w = 2 + r;
		stars[i].dim.h = 2 + r;
		stars[i].col = SDL_MapRGB(screen->format, 255,255,255 - (rand() % 150));
		stars[i].dist = (float)(rand() % 100) / 100;
	}
}

/*
	Tagastab taandatud kraadi, mille poole laev on suunatud täisarvuna.
*/

int getImgRot(float rot) {
	int iRot = (int)rot % 359;
	return iRot >= 0 ? iRot : iRot + 360;
}

/*
	Joonistab mängija ekraanile.
*/

void drawPlayer(SDL_Surface *screen, Player player, SDL_Surface **shipImgs) {
	int x = getImgRot(player.rpos);
	SDL_Rect playerLocation;
	playerLocation.x = width / 2 - shipImgs[x] -> w / 2;
	playerLocation.y = height / 2 - shipImgs[x] -> h / 2;
	playerLocation.w = shipImgs[x] -> w;
	playerLocation.h = shipImgs[x] -> h;
	SDL_BlitSurface(shipImgs[x], 0, screen, &playerLocation);
}

/*	
	Kiirendab mängija laeva.
*/

void accelerate(Player *player) {
	float rad = (player -> rpos) * PI / 180.0;
	player -> xacc =  0.01 * cos(rad);
	player -> yacc = -0.01 * sin(rad);
}

/*
	Uuendab mängija laeva asukohta.
*/

void updatePlayer(Player *player) {
	if (player -> acc) {
		accelerate(player);
	} else {
		player -> xacc = 0;
		player -> yacc = 0;
	}
	player -> xpos += player -> xvel;
	player -> ypos += player -> yvel;
	player -> xvel += player -> xacc;
	player -> yvel += player -> yacc;
	player -> rpos += player -> rspd;
}

int main(int argc, char *argv[]) {
	SDL_Surface *screen;
	SDL_Event event;
	Star stars[starLimit];

	SDL_Rect drawRect;
	SDL_Surface *shipImg = IMG_Load(laevaUrl);
	SDL_Surface *shipImgs[359];
	
	Player player = {100,100,0,0,0,0,0,0,0};

	uint x;
	srand(time(NULL));

	
	if(initScreen(&screen) == 0) {
		return 0;
	}
	initStars(stars, screen);

	if(!shipImg) {
    	printf("IMG_Load failed: %s\n", IMG_GetError());
    	return 0;
	}

	for (x = 0; x < 360; x++)
	{
		shipImgs[x] = rotozoomSurface(shipImg, x, 1, 1);
	}
	
	while (1) {
		SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
	
		/*
			Käib läbi kõik sisendsündmused.
		*/

		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{			
				case SDL_QUIT:
					exit(0);
				break;

				case SDL_KEYDOWN:
					switch (event.key.keysym.sym)
					{
						case SDLK_ESCAPE:
							exit(0); 
						break;
						
						case SDLK_UP:
							player.acc = 1;
						break;
						
						case SDLK_LEFT: 
							player.rspd += 2; 
						break;

						case SDLK_RIGHT: 
							player.rspd -= 2; 
						break;
						default: break;
					} break;
				case SDL_KEYUP:
					switch (event.key.keysym.sym)
					{
						case SDLK_ESCAPE:
							exit(0); 
						break;
						
						case SDLK_UP:
							player.acc = 0;
						break;

						case SDLK_LEFT: 
							player.rspd -= 2; 
						break;

						case SDLK_RIGHT: 
							player.rspd += 2; 
						break;
						default: break;
					} break;
			}
		}

		/*
			Mängu olukorra uuendused.
		*/

		updatePlayer(&player);

		for (x = 0 ; x < starLimit ; x ++) {
			if (stars[x].dim.x - player.xpos * stars[x].dist < 0) {
				stars[x].dim.x += width;
			}
			if (stars[x].dim.y - player.ypos * stars[x].dist < 0) {
				stars[x].dim.y += height;
			}
			if (stars[x].dim.x - player.xpos * stars[x].dist > width) {
				stars[x].dim.x -= width;
			}
			if (stars[x].dim.y - player.ypos * stars[x].dist > height) {
				stars[x].dim.y -= height;
			}
		}

		/*
			Mängu olukorra joonistamine
		*/

		for (x = 0 ; x < starLimit ; x ++) {
			drawRect = stars[x].dim;
			drawRect.x -= player.xpos * stars[x].dist;
			drawRect.y -= player.ypos * stars[x].dist;
			SDL_FillRect(screen, &drawRect, stars[x].col);
		}

		drawPlayer(screen, player, shipImgs);
		
		/*
			100 FPS limiit.
		*/

		SDL_Delay(10); 
		SDL_Flip(screen);
	}
	
	SDL_Quit();
	return 0;
}
