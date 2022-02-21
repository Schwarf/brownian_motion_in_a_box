//
// Created by andreas on 21.02.22.
//

#ifndef SYSTEM_SIMULATION_H
#define SYSTEM_SIMULATION_H
#include "i_system_simulation.h"
#include "binary_heap.h"
#include "scatter_event.h"
#include "particle_2D_in_a_box.h"
#include <vector>

template<class T, size_t number_of_particles>
class SystemSimulation: public ISystemSimulation<T>
{
public:
	SystemSimulation(std::vector<IParticle2DInABox<T> *> list_of_particles, T simulation_time_limit)
		:
		simulation_time_limit_(simulation_time_limit)
	{
		list_of_particles_ = list_of_particles;
	}
	void simulate_up_to_time(T time) final
	{
		for (const auto &p_particle: list_of_particles_) {
			predict_scatter_times_for_(p_particle);
		}
	}

	std::vector<IParticle2DInABox<T> *> particles()
	{
		return list_of_particles_;
	}

private:
	void predict_scatter_times_for_(IParticle2DInABox<T> *current_particle)
	{
		// check for current_particle-current_particle-scattering
		for (const auto &particle: list_of_particles_) {
			auto scatter_time = current_particle->time_to_scatter(*particle);
			if (scatter_time < 0)
				continue;
			if ((scatter_time + simulation_time_) < simulation_time_limit_) {
				auto scatter_event = ScatterEvent<T>(scatter_time + simulation_time_, particle, current_particle);
				priority_queue_.insert(scatter_event);
			}
		}
		auto vertical_wall_scatter_time = current_particle->time_to_scatter_vertical_wall();
		auto horizontal_wall_scatter_time = current_particle->time_to_scatter_horizontal_wall();
		if ((vertical_wall_scatter_time + simulation_time_) < simulation_time_limit_) {
			// TODO FIX THIS. NULLPTR IS NOT VALID HERE
			//auto scatter_event = ScatterEvent<T>(current_particle, nullptr);
			//priority_queue_.insert(scatter_event);
		}
		if ((horizontal_wall_scatter_time + simulation_time_) < simulation_time_limit_) {
			//auto scatter_event = ScatterEvent<T>(current_particle, nullptr);
			//priority_queue_.insert(scatter_event);
		}

	}
	BinaryHeap<ScatterEvent<T>, number_of_particles> priority_queue_;
	std::vector<IParticle2DInABox<T> *> list_of_particles_;
	T simulation_time_{};
	T simulation_time_limit_{};
};
#endif //SYSTEM_SIMULATION_H
