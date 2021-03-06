//
// Created by andreas on 21.02.22.
//

#ifndef I_SCATTER_EVENT_H
#define I_SCATTER_EVENT_H
#include <memory>

template<class T>
class IScatterEvent
{
public:
	virtual bool is_still_valid() const = 0;
	virtual bool does_happen_before(std::shared_ptr<IScatterEvent<T>> &other_event) const = 0;
	virtual std::shared_ptr<IParticle2DInABox<T>> particle_one() const = 0;
	virtual std::shared_ptr<IParticle2DInABox<T>> particle_two() const = 0;
	virtual bool is_hitting_horizontal_wall() const = 0;
	virtual bool is_hitting_vertical_wall() const = 0;
	virtual void set_is_hitting_horizontal_wall(bool is_hitting_horizontal_wall) = 0;
	virtual void set_is_hitting_vertical_wall(bool is_hitting_vertical_wall) = 0;
	virtual bool is_helper_event() const = 0;
	virtual T time() const = 0;
};

#endif //I_SCATTER_EVENT_H
