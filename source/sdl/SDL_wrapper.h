//
// Created by andreas on 27.02.22.
//

#ifndef SDL_WRAPPER_H
#define SDL_WRAPPER_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <memory>

class SDL_Wrapper
{
public:
	SDL_Wrapper(int window_width, int window_height);


private:
	std::shared_ptr<SDL_Window> SDL_window_;
	std::shared_ptr<SDL_Surface> SDL_surface_;
	std::shared_ptr<void> GL_context_;

};


#endif //SDL_WRAPPER_H
