#include <iostream>
#include <SDL2/SDL.h>
#include "particle_2D_in_a_box.h"
#include "collision_event.h"
#include "system_simulation.h"
int main()
{
	Particle2DInABox<double> particle;
	Particle2DInABox<double> particle1;
	std::shared_ptr<Particle2DInABox<double>[]> list_of_particles(new Particle2DInABox<double>[2]);
	SystemSimulation<double, 100> simu(list_of_particles);
	std::cout << "Hello, World!" << particle.id() << std::endl;
	std::cout << "Hello, World!" << particle1.id() << std::endl;

	particle.time_to_hit(particle1);
	return 0;
}
