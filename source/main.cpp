#include <iostream>
#include <SDL2/SDL.h>
#include "particle_2D_in_a_box.h"
int main()
{
	Particle2DInABox<double> particle;
	Particle2DInABox<double> particle1;

	std::cout << "Hello, World!" << particle.id() << std::endl;
	std::cout << "Hello, World!" << particle1.id() << std::endl;
	particle.time_to_hit(particle1);
	return 0;
}
