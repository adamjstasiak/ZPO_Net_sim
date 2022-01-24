//
// Created by stasi on 23.01.2022.
//

#ifndef ZPO_NET_SIM_REPORTS_HPP
#define ZPO_NET_SIM_REPORTS_HPP
#include "factory.hpp"
#include "nodes.hpp"

void generate_structure_report(const Factory& factory,std::ostream& os);
void generate_structure_turn_report(const Factory& factory,std::ostream os, Time t);

class SpecificTurnsReportNotifier{
public:
    SpecificTurnsReportNotifier(std::set<Time> turns) : turns(turns){}
    bool should_generate_report(Time t){return turns.count(t)>0;}

private:
    std::set<Time> turns;

};
class IntervalReportNotifier{
public:
    IntervalReportNotifier(TimeOffset to) : to(to){}
    bool should_generate_report(Time t){ return (t-1) % to == 0;}

private:
    TimeOffset to;
};

#endif //ZPO_NET_SIM_REPORTS_HPP
