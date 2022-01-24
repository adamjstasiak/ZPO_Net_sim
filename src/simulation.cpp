//
// Created by stasi on 23.01.2022.
//

# include "simulation.hpp"
void simulate(Factory& f,TimeOffset d,std::function<void (Factory&,Time)>rf){
    if(f.is_consistent() != true){
        throw std::logic_error("Not consistent");
    }
    else{
        rf(f,d);
    }
    for(int t = 1; t < d; t++ ){
        f.do_deliveries(t);
        f.do_package_passing();
        f.do_work(t);
    }
}