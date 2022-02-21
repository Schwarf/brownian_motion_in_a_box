//
// Created by andreas on 21.02.22.
//

#ifndef I_SYSTEM_SIMULATION_H
#define I_SYSTEM_SIMULATION_H

template<class T>
class ISystemSimulation
{
public:
	virtual void simulate_up_to_time(T time) = 0;
};

#endif //I_SYSTEM_SIMULATION_H
