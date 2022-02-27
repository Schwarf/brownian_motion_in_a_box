//
// Created by andreas on 27.02.22.
//

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <string>


int main()
{
	SDL_Init(SDL_INIT_VIDEO);
	auto title = "My first window";
	SDL_Window * window = SDL_CreateWindow(title, 300,30, 500, 600, SDL_WINDOW_SHOWN);
	SDL_Surface * screen = SDL_GetWindowSurface(window);
	SDL_Delay(2000);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}