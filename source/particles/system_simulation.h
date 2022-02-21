//
// Created by andreas on 21.02.22.
//

#ifndef SYSTEM_SIMULATION_H
#define SYSTEM_SIMULATION_H
#include "i_system_simulation.h"
#include "binary_heap.h"
#include "collision_event.h"
#include "particle_2D_in_a_box.h"

template<class T, size_t number_of_particles>
class SystemSimulation: public ISystemSimulation<T>
{
public:
	SystemSimulation(std::shared_ptr<Particle2DInABox<T>[]> list_of_particles)
	{
		list_of_particles_ = list_of_particles;
	}
	void simulate_up_to_time(T time) final
	{

	}

private:
	BinaryHeap<CollisionEvent<T>, number_of_particles> priority_queue_;
	std::shared_ptr<Particle2DInABox<T>[]> list_of_particles_;
};
#endif //SYSTEM_SIMULATION_H
