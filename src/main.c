#include <stdio.h>
#include <stdlib.h>
#include "main.h"

char initScreen(SDL_Surface **screen) {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("Tekkis viga: %s\n", SDL_GetError());
		return 0;
	}
	if ((*screen = SDL_SetVideoMode(800, 600, 0, SDL_HWPALETTE)) == NULL) {
		printf("Tekkis viga: %s\n", SDL_GetError());
		return 0;
	}
	SDL_WM_SetCaption("Asteroids", NULL);
	return 1;
}

int main(int argc, char *argv[]) {
	SDL_Surface *screen;
	SDL_Event event;
	char i = 0;
	
	initScreen(&screen);	
	
	while (1) {
		SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, (i % 255), 0, 0));
	
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
							exit(0); break;
						
						case SDLK_UP:
							i = 0; break;
					
						case SDLK_DOWN:
							i = 1; break;
						
						case SDLK_LEFT: break;
						
						case SDLK_RIGHT: break;
						
						case SDLK_SPACE:
							switch (i) {
								case 1: i = 0; break;
								case 0: i = 1; break;
							}
						break;
					
						default:
						break;
					}
				break;
			}
		}
		i ++;
		
		SDL_Delay(10);
		SDL_Flip(screen);
	}
	
	SDL_Quit();
	return 0;
}
