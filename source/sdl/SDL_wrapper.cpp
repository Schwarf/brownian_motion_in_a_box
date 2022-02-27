//
// Created by andreas on 27.02.22.
//

#include "SDL_wrapper.h"

SDL_Wrapper::SDL_Wrapper(int window_width, int window_height)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		throw std::out_of_range("SDL init failed!");
	}
	SDL_window_ = std::shared_ptr<SDL_Window>(SDL_CreateWindow("Title",
															   SDL_WINDOWPOS_UNDEFINED,
															   SDL_WINDOWPOS_UNDEFINED,
															   window_width,
															   window_height,
															   SDL_WINDOW_SHOWN), SDL_DestroyWindow);
	SDL_surface_ = std::shared_ptr<SDL_Surface>(SDL_GetWindowSurface(SDL_window_.get()), SDL_FreeSurface);
	//GL_context_ = std::shared_ptr<void>(SDL_GL_CreateContext(SDL_window_.get()), SDL_GL_DeleteContext);
	SDL_Delay(2000);

}
