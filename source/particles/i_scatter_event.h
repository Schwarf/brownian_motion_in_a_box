//
// Created by andreas on 21.02.22.
//

#ifndef I_SCATTER_EVENT_H
#define I_SCATTER_EVENT_H
template<class T>
class IScatterEvent
{
public:
	virtual bool is_still_valid() const = 0;
	virtual bool does_happen_before(const IScatterEvent<T> &other_event) const = 0;
	virtual T time() const = 0;
};

#endif //I_SCATTER_EVENT_H
