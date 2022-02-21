//
// Created by andreas on 21.02.22.
//

#ifndef I_COLLISION_EVENT_H
#define I_COLLISION_EVENT_H
template<class T>
class ICollisionEvent
{
public:
	virtual bool is_still_valid() const = 0;
	virtual bool does_happen_before(const ICollisionEvent<T> &other_event) const = 0;
	virtual T time() const = 0;
};

#endif //I_COLLISION_EVENT_H
