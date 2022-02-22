//
// Created by andreas on 20.02.22.
//

#ifndef PARTICLE_2D_IN_A_BOX_H
#define PARTICLE_2D_IN_A_BOX_H
#include <cstddef>
#include <cmath>
#include "i_particle_2D_in_a_box.h"
#include <random>

template<class T>
class Particle2DInABox: public IParticle2DInABox<T>
{
public:
	Particle2DInABox()
		:
		id_{Particle2DInABox<T>::particle_counter_++}
	{
		std::random_device random_device;
		std::mt19937 mersenne_twister(random_device());
		std::uniform_real_distribution<> position(0.0, 1.0);
		std::uniform_real_distribution<> velocity(-0.005, 0.005);
		radius_ = 0.2;
		mass_ = 0.5;
		x_position_ = position(mersenne_twister);
		y_position_ = position(mersenne_twister);
		x_velocity_ = velocity(mersenne_twister);
		y_velocity_ = velocity(mersenne_twister);
	}
	T radius() const final
	{
		return radius_;
	}

	T mass() const final
	{
		return mass_;
	}

	void move(T time_delta) final
	{
		x_position_ += x_velocity_ * time_delta;
		y_position_ += y_velocity_ * time_delta;
	}

	T time_to_scatter(std::shared_ptr<IParticle2DInABox<T>> & other_particle) const final
	{

		if (this->id() == other_particle->id())
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
		auto radii_distance = this->radius_ + other_particle->radius();

		auto
			delta = (delta_position_times_delta_velocity * delta_position_times_delta_velocity) - velocity_delta_squared
			* (position_delta_squared - radii_distance * radii_distance);
		if (delta < 0)
			return T{-1};
		return -(delta_position_times_delta_velocity + std::sqrt(delta)) / velocity_delta_squared;

	}
	T time_to_scatter_vertical_wall() const final
	{
		// we are in a box of size 1x1 with left lower origin at (0,0)
		if (x_velocity_ > 0) {
			return (1.0 - x_position_ - radius_) / x_velocity_;
		}
		if (x_velocity_ < 0) {
			return (x_position_ - radius_) / x_velocity_;
		}

		return T{-1};
	}
	T time_to_scatter_horizontal_wall() const final
	{
		// we are in a box of size 1x1 with left lower origin at (0,0)
		if (y_velocity_ > 0) {
			return (1.0 - y_position_ - radius_) / y_velocity_;
		}
		if (y_velocity_ < 0) {
			return (y_position_ - radius_) / y_velocity_;
		}
		return T{-1};
	}
	void scatter(std::shared_ptr<IParticle2DInABox<T>> & other_particle) final
	{
		auto delta_x = delta_x_(other_particle);
		auto delta_y = delta_y_(other_particle);
		auto delta_v_x = delta_v_x_(other_particle);
		auto delta_v_y = delta_v_y_(other_particle);
		auto delta_position_times_delta_velocity = delta_x * delta_v_x + delta_y * delta_v_y;
		auto radii_distance = this->radius_ + other_particle->radius();
		auto momentum = 2 * this->mass_ * other_particle->mass() * delta_position_times_delta_velocity
			/ (this->mass_ + other_particle->mass()) / radii_distance;

		double x_momentum = momentum * delta_x / radii_distance;
		double y_momentum = momentum * delta_y / radii_distance;
		this->x_velocity_ += x_momentum / this->mass_;
		this->y_velocity_ += y_momentum / this->mass_;
		other_particle->set_x_velocity(other_particle->x_velocity() - x_momentum / other_particle->mass());
		other_particle->set_y_velocity(other_particle->y_velocity() - y_momentum / other_particle->mass());
		other_particle->increase_collision_counter();
		this->increase_collision_counter();
	}
	void scatter_vertical_wall() final
	{
		x_velocity_ = -x_velocity_;
		increase_collision_counter();
	}
	void scatter_horizontal_wall() final
	{
		y_velocity_ = -y_velocity_;
		increase_collision_counter();
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
	void set_x_position(const T &x_position) final
	{
		x_position_ = x_position;
	}
	void set_y_position(const T &y_position) final
	{
		y_position_ = y_position;
	}
	void set_x_velocity(const T &x_velocity) final
	{
		x_velocity_ = x_velocity;
	}
	void set_y_velocity(const T &y_velocity) final
	{
		y_velocity_ = y_velocity;
	}
	size_t number_of_collisions() const final
	{
		return number_of_collisions_;
	}
	void increase_collision_counter() final
	{
		number_of_collisions_++;
	}
	~Particle2DInABox() override = default;
private:
	T delta_x_(std::shared_ptr<IParticle2DInABox<T>> &other_particle) const
	{
		return other_particle->x_position() - this->x_position_;
	}
	T delta_y_(std::shared_ptr<IParticle2DInABox<T>> &other_particle) const
	{
		return other_particle->y_position() - this->y_position_;
	}

	T delta_v_x_(std::shared_ptr<IParticle2DInABox<T>> &other_particle) const
	{
		return other_particle->x_velocity() - this->x_velocity_;
	}
	T delta_v_y_(std::shared_ptr<IParticle2DInABox<T>> &other_particle) const
	{
		return other_particle->y_velocity() - this->y_velocity_;
	}

	size_t id_{};
	static size_t particle_counter_;
	T x_position_{};
	T y_position_{};
	T x_velocity_{};
	T y_velocity_{};
	T radius_{};
	T mass_{};
	size_t number_of_collisions_{};

};

// Initialize particle counter.
template<typename T>
size_t Particle2DInABox<T>::particle_counter_ = 0;

#endif //PARTICLE_2D_IN_A_BOX_H
