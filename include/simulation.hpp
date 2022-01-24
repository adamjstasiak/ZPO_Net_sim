//
// Created by stasi on 23.01.2022.
//

#ifndef ZPO_NET_SIM_SIMULATION_HPP
#define ZPO_NET_SIM_SIMULATION_HPP

#include "factory.hpp"

void simulate(Factory& f,TimeOffset d,std::function<void (Factory&,Time)>rf);

#endif //ZPO_NET_SIM_SIMULATION_HPP
