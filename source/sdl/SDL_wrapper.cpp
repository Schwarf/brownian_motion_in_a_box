//
// Created by andreas on 27.02.22.
//

#include "SDL_wrapper.h"

SDL_Wrapper::SDL_Wrapper(int window_width, int window_height)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		throw std::bad_alloc();
	}
	SDL_window_ = std::shared_ptr<SDL_Window>(SDL_CreateWindow("Title",
															   SDL_WINDOWPOS_UNDEFINED,
															   SDL_WINDOWPOS_UNDEFINED,
															   window_width,
															   window_height,
															   SDL_WINDOW_SHOWN), SDL_DestroyWindow);
	SDL_surface_ = std::shared_ptr<SDL_Surface>(SDL_GetWindowSurface(SDL_window_.get()), SDL_FreeSurface);
	GL_context_ = std::shared_ptr<void>(SDL_GL_CreateContext(SDL_window_.get()), SDL_GL_DeleteContext);
	SDL_renderer_ = std::shared_ptr<SDL_Renderer>(SDL_CreateRenderer(SDL_window_.get(), -1, SDL_RENDERER_ACCELERATED),
												  SDL_DestroyRenderer);

	auto bitmap = SDL_LoadBMP("dots.bmp");
	auto bitmap_texture = SDL_CreateTextureFromSurface(SDL_renderer_.get(), bitmap);
	SDL_FreeSurface(bitmap);
	auto run = true;
	while(run)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_QUIT:
					run = false;
					break;
			}
		}
		SDL_RenderClear(SDL_renderer_.get());
		SDL_RenderCopy(SDL_renderer_.get(), bitmap_texture, NULL, NULL);
		SDL_RenderPresent(SDL_renderer_.get());
	}

}
