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
	SystemSimulation(std::vector<std::shared_ptr<IParticle2DInABox<T>>> &list_of_particles, T simulation_time_limit)
		:
		simulation_time_limit_(simulation_time_limit)
	{
		list_of_particles_ = list_of_particles;
	}
	void simulate_up_to_time(T time) final
	{
		for (size_t current_particle_index = 0; current_particle_index < list_of_particles_.size();
			 ++current_particle_index) {
			predict_scatter_times_for_(list_of_particles_[current_particle_index], current_particle_index);
		}
	}
	std::vector<std::shared_ptr<IParticle2DInABox<T>>> particles()
	{
		return list_of_particles_;
	}

	BinaryHeap<ScatterEvent<T>, number_of_particles * (number_of_particles - 1) / 2> queue()
	{
		return priority_queue_;
	}
private:
	void predict_scatter_times_for_(std::shared_ptr<IParticle2DInABox<T>> &current_particle,
									size_t current_particle_index)
	{
		// check for current_particle-current_particle-scattering
		for (size_t particle_index = current_particle_index + 1; particle_index < list_of_particles_.size();
			 particle_index++) {
			auto scatter_time = current_particle->time_to_scatter(list_of_particles_[particle_index]);
			if (scatter_time < 0.0) {
				continue;
			}
			if ((scatter_time + simulation_time_) < simulation_time_limit_) {
				auto scatter_event = ScatterEvent<T>(scatter_time + simulation_time_,
													 list_of_particles_[particle_index],
													 current_particle);
				priority_queue_.insert(scatter_event);
			}
		}
		auto vertical_wall_scatter_time = current_particle->time_to_scatter_vertical_wall();
		auto horizontal_wall_scatter_time = current_particle->time_to_scatter_horizontal_wall();
		if (vertical_wall_scatter_time > 0.0 && (vertical_wall_scatter_time + simulation_time_) < simulation_time_limit_) {
			auto scatter_event =
				ScatterEvent<T>(vertical_wall_scatter_time + simulation_time_, current_particle, current_particle);
			priority_queue_.insert(scatter_event);
		}
		if (horizontal_wall_scatter_time > 0.0 && (horizontal_wall_scatter_time + simulation_time_) < simulation_time_limit_) {
			auto scatter_event =
				ScatterEvent<T>(horizontal_wall_scatter_time + simulation_time_, current_particle, current_particle);
			priority_queue_.insert(scatter_event);
		}

	}
	BinaryHeap<ScatterEvent<T>, number_of_particles * (number_of_particles - 1) / 2> priority_queue_;
	std::vector<std::shared_ptr<IParticle2DInABox<T>>> list_of_particles_;
	T simulation_time_{};
	T simulation_time_limit_{};
};
#endif //SYSTEM_SIMULATION_H
