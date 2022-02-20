//
// Created by andreas on 20.02.22.
//

#ifndef PARTICLE_2D_IN_A_BOX_H
#define PARTICLE_2D_IN_A_BOX_H
#include <cstddef>
#include <cmath>
#include "i_particle_2D_in_a_box.h"

template<class T>
class Particle2DInABox: public IParticle2DInABox<T>
{
public:
	Particle2DInABox()
		:
		id_{particle_counter_++}
	{

	}
	T radius() const final
	{
		return nullptr;
	}

	void move(T time_delta) final
	{

	}

	T time_to_hit(IParticle2DInABox<T> &other_particle) final
	{
		if (this->id() == other_particle.id())
			return T{-1};
		auto delta_x = this->x_position_ - other_particle.x_position();
		auto delta_y = this->y_position_ - other_particle.y_position();

		auto delta_v_x = this->x_velocity_ - other_particle.x_velocity();
		auto delta_v_y = this->y_velocity_ - other_particle.y_velocity();

		auto delta_position_times_delta_velocity = delta_x * delta_v_x + delta_y * delta_v_y;
		if (delta_position_times_delta_velocity > T{})
			return T{-1};

		auto velocity_delta_squared = delta_v_x * delta_v_x + delta_v_y * delta_v_y;
		auto position_delta_squared = delta_x * delta_x + delta_y * delta_y;
		auto radi_distance = this->radius_ + other_particle.radius();

		auto delta = (delta_position_times_delta_velocity * delta_position_times_delta_velocity) - velocity_delta_squared
			*(position_delta_squared - radi_distance *radi_distance);
		if(delta < 0)
			return T{-1};
		return -(delta_position_times_delta_velocity + std::sqrt(delta))/velocity_delta_squared;


	}
	T time_to_hit_vertical_wall() final
	{
		return nullptr;
	}
	T time_to_hit_horizontal_wall() final
	{
		return nullptr;
	}
	void scatter(IParticle2DInABox<T> &other_particle) final
	{

	}
	void scatter_vertical_wall() final
	{

	}
	void scatter_horizontal_wall() final
	{

	}
	T x_position() const final
	{
		return x_position_;
	}
	T y_position() const final
	{
		return y_position_;
	}
	T x_velocity() const final
	{
		return x_velocity_;
	}
	T y_velocity() const final
	{
		return y_velocity_;
	}
	size_t id() const
	{
		return nullptr;
	}
private:
	size_t id_{};
	static size_t particle_counter_;
	T x_position_{};
	T y_position_{};
	T x_velocity_{};
	T y_velocity_{};
	T radius_{};
	
};


#endif //PARTICLE_2D_IN_A_BOX_H
