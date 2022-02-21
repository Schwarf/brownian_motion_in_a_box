//
// Created by andreas on 20.02.22.
//

#ifndef I_PARTICLE_H
#define I_PARTICLE_H

template<class T>
class IParticle2DInABox
{
public:
	virtual void move(T time_delta) = 0;
	virtual T time_to_hit(const IParticle2DInABox &other_particle) const = 0;
	virtual T time_to_hit_vertical_wall() const = 0;
	virtual T time_to_hit_horizontal_wall() const = 0;
	virtual void scatter(IParticle2DInABox &other_particle) = 0;
	virtual void scatter_vertical_wall() = 0;
	virtual void scatter_horizontal_wall() = 0;
	virtual T x_position() const = 0;
	virtual T y_position() const = 0;
	virtual T x_velocity() const = 0;
	virtual T y_velocity() const = 0;
	virtual T radius() const = 0;
	virtual T mass() const = 0;
	virtual size_t id() const = 0;
	virtual void set_x_position(const T &x_position) = 0;
	virtual void set_y_position(const T &y_position) = 0;
	virtual void set_x_velocity(const T &x_velocity) = 0;
	virtual void set_y_velocity(const T &y_velocity) = 0;
	virtual size_t number_of_collisions() const = 0;
	virtual void increase_collision_counter()  = 0;

};


#endif //I_PARTICLE_H
