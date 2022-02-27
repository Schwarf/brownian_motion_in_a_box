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
		for (auto & particle : list_of_particles_) {
			predict_scatter_times_for_(particle);
		}

		priority_queue_.insert( ScatterEvent<T>(0.0));

		while(!priority_queue_.is_empty())
		{
			auto event = priority_queue_.pop_minimum();
			if(!event.is_still_valid())
				continue;
			auto particle_one = event.particle_one();


			auto time_of_event = event.time();
			for(auto & particle : list_of_particles_)
			{
				particle->move(time_of_event - simulation_time_);
			}
			simulation_time_ = time_of_event;


			if(event.is_helper_event())
				continue;

			if(!event.is_hitting_horizontal_wall() && !event.is_hitting_vertical_wall()) {
				auto particle_two = event.particle_two();
				particle_one->scatter(particle_two);
				predict_scatter_times_for_(particle_two);
			}
			if(event.is_hitting_vertical_wall())
				particle_one->scatter_vertical_wall();
			if(event.is_hitting_horizontal_wall())
				particle_one->scatter_horizontal_wall();

			predict_scatter_times_for_(particle_one);
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
	void predict_scatter_times_for_(std::shared_ptr<IParticle2DInABox<T>>  current_particle)
	{
	if(! current_particle)
			return;
		// check for current_particle-current_particle-scattering
		for (size_t particle_index = current_particle->id() + 1; particle_index < list_of_particles_.size();
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
				ScatterEvent<T>(vertical_wall_scatter_time + simulation_time_, current_particle);
				scatter_event.set_is_hitting_vertical_wall(true);
			priority_queue_.insert(scatter_event);
		}
		if (horizontal_wall_scatter_time > 0.0 && (horizontal_wall_scatter_time + simulation_time_) < simulation_time_limit_) {
			auto scatter_event =
				ScatterEvent<T>(horizontal_wall_scatter_time + simulation_time_, current_particle);
				scatter_event.set_is_hitting_horizontal_wall(true);
			priority_queue_.insert(scatter_event);
		}

	}
	BinaryHeap<ScatterEvent<T>, number_of_particles * (number_of_particles - 1) / 2> priority_queue_;
	std::vector<std::shared_ptr<IParticle2DInABox<T>>> list_of_particles_;
	T simulation_time_{};
	T simulation_time_limit_{};
};
#endif //SYSTEM_SIMULATION_H
