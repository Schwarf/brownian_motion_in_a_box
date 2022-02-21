//
// Created by andreas on 21.02.22.
//

#ifndef COLLISION_EVENT_H
#define COLLISION_EVENT_H
#include <memory>
#include "i_collision_event.h"
#include "i_particle_2D_in_a_box.h"

template<class T>
class CollisionEvent: public ICollisionEvent<T>
{
public:
	CollisionEvent(T time_of_event, IParticle2DInABox<T> &particle_one, IParticle2DInABox<T> &particle_two)
		:
		time_of_event_(time_of_event),
		particle_one_(std::make_shared<IParticle2DInABox<T>>(particle_one)),
		particle_two_(std::make_shared<IParticle2DInABox<T>>(particle_two))
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
	bool does_happen_before(const ICollisionEvent<T> &other_event) const final
	{
		return time_of_event_ < other_event.time();
	}
	T time() const final	
	{
		return time_of_event_;
	}

private:
	std::shared_ptr<IParticle2DInABox<T>> particle_one_;
	std::shared_ptr<IParticle2DInABox<T>> particle_two_;
	T time_of_event_;
	size_t collision_count_particle_one_{};
	size_t collision_count_particle_two_{};
};

#endif //COLLISION_EVENT_H
