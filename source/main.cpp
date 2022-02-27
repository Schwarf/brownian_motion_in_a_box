#include <iostream>
#include "particle_2D_in_a_box.h"
#include "scatter_event.h"
#include "system_simulation.h"
int main()
{
	constexpr size_t number_of_particles = 100;
//	Particle2DInABox<double> particle;
//	Particle2DInABox<double> particle1;
	std::vector<std::shared_ptr<IParticle2DInABox<double>>> list_of_particles;
	for(size_t i =0; i < number_of_particles; ++i)
	{
		list_of_particles.push_back(std::make_shared<Particle2DInABox<double>>());
	}
	SystemSimulation<double, number_of_particles> simu(list_of_particles, 10000);
//	std::cout << "Hello, World!" << particle.id() << std::endl;
//	std::cout << "Hello, World!" << particle1.id() << std::endl;
	std::cout << "Hello, World!" << simu.particles()[0]->id() << std::endl;
	std::cout << "Hello, World!" << simu.particles()[1]->id() << std::endl;
//	std::cout << particle.time_to_scatter(particle1) << std:: endl;
	simu.simulate_up_to_time(1000);

	auto x = simu.queue();
	return 0;
}
