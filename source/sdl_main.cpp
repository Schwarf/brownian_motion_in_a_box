//
// Created by andreas on 27.02.22.
//

#include "sdl/SDL_wrapper.h"
#include <string>


int main()
{
	/*
	SDL_Init(SDL_INIT_VIDEO);
	auto title = "My first window";
	SDL_Window * window = SDL_CreateWindow(title, 300,30, 500, 600, SDL_WINDOW_SHOWN);
	SDL_Surface * screen = SDL_GetWindowSurface(window);
	SDL_Delay(2000);
	SDL_DestroyWindow(window);

	 */
	auto wrapper = SDL_Wrapper(600, 600);
	SDL_Delay(1000);
//	SDL_Quit();
	return 0;
}