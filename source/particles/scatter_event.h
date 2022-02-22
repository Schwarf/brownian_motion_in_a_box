//
// Created by andreas on 21.02.22.
//

#ifndef SCATTER_EVENT_H
#define SCATTER_EVENT_H
#include <memory>
#include "i_scatter_event.h"
#include "i_particle_2D_in_a_box.h"

template<class T>
class ScatterEvent: public IScatterEvent<T>
{
public:
	ScatterEvent() = default;

	ScatterEvent(T time_of_event, IParticle2DInABox<T> * particle_one, IParticle2DInABox<T> * particle_two)
		:
		time_of_event_(time_of_event),
		particle_one_(particle_one),
		particle_two_(particle_two)
	{
		collision_count_particle_one_ = particle_one_->number_of_collisions();
		collision_count_particle_two_ = particle_two_->number_of_collisions();
	}
	bool is_still_valid() const final
	{
		if (collision_count_particle_one_ != particle_one_->number_of_collisions())
			return false;
		if (collision_count_particle_two_ != particle_two_->number_of_collisions())
			return false;
		return true;
	}
	bool does_happen_before(const IScatterEvent<T> &other_event) const final
	{
		return time_of_event_ < other_event.time();
	}
	T time() const final
	{
		return time_of_event_;
	}

private:
	IParticle2DInABox<T> * particle_one_{};
	IParticle2DInABox<T>* particle_two_{};
	T time_of_event_;
	size_t collision_count_particle_one_{};
	size_t collision_count_particle_two_{};
};

#endif //SCATTER_EVENT_H