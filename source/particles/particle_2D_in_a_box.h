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
		id_{Particle2DInABox<T>::particle_counter_++}
	{

	}
	T radius() const final
	{
		return radius_;
	}

	void move(T time_delta) final
	{

	}

	T time_to_hit(const IParticle2DInABox<T> &other_particle) const final
	{
		if (this->id() == other_particle.id())
			return T{-1};

		auto delta_x = delta_x_(other_particle);
		auto delta_y = delta_y_(other_particle);
		auto delta_v_x = delta_v_x_(other_particle);
		auto delta_v_y = delta_v_y_(other_particle);

		auto delta_position_times_delta_velocity = delta_x * delta_v_x + delta_y * delta_v_y;
		if (delta_position_times_delta_velocity > T{})
			return T{-1};

		auto velocity_delta_squared = delta_v_x * delta_v_x + delta_v_y * delta_v_y;
		auto position_delta_squared = delta_x * delta_x + delta_y * delta_y;
		auto radii_distance = this->radius_ + other_particle.radius();

		auto
			delta = (delta_position_times_delta_velocity * delta_position_times_delta_velocity) - velocity_delta_squared
			* (position_delta_squared - radii_distance * radii_distance);
		if (delta < 0)
			return T{-1};
		return -(delta_position_times_delta_velocity + std::sqrt(delta)) / velocity_delta_squared;

	}
	T time_to_hit_vertical_wall() const final
	{
		return T{};
	}
	T time_to_hit_horizontal_wall() const final
	{
		return T{};
	}
	void scatter(IParticle2DInABox<T> &other_particle) final
	{
		auto delta_x = delta_x_(other_particle);
		auto delta_y = delta_y_(other_particle);

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
		return id_;
	}
private:
	T delta_x_(const IParticle2DInABox<T> &other_particle) const
	{
		return other_particle.x_position() - this->x_position_;
	}
	T delta_y_(const IParticle2DInABox<T> &other_particle) const
	{
		return other_particle.y_position() - this->y_position_;
	}

	T delta_v_x_(const IParticle2DInABox<T> &other_particle) const
	{
		return other_particle.x_velocity() - this->x_velocity_;
	}
	T delta_v_y_(const IParticle2DInABox<T> &other_particle) const
	{
		return other_particle.y_velocity() - this->y_velocity_;
	}

	size_t id_{};
	static size_t particle_counter_;
	T x_position_{};
	T y_position_{};
	T x_velocity_{};
	T y_velocity_{};
	T radius_{};

};

// Initialize particle counter.
template<typename T>
size_t Particle2DInABox<T>::particle_counter_ = 0;

#endif //PARTICLE_2D_IN_A_BOX_H
