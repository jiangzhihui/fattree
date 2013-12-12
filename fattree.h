#ifndef _FATTREE_FATTREE_H
#define _FATTREE_FATTREE_H

#include <vector>
#include <string>
#include "host.h"
#include "EdgeSwitch.h" 
#include "AggrSwitch.h" 
#include "CoreSwitch.h"

namespace fattree{

class Engine{
public:
    Engine(int k):k(k),hosts(k*k*k/4),cores(k*k/4),edges(k*k/2),aggrs(k*k/2){
        init_devices();    
        connect_devices();
    }
    /*
    Init the data center with fat-tree topology each switch with k ports 
    */
    void print_cores();
    void print_edges();
    void print_aggrs();
    void print_hosts();
    void print_core_table();
private:
    void init_devices();
    void init_cores();             
    void init_aggrs();
    void init_edges();
    void init_hosts();
    void connect_devices();
    void connect_core_aggr();
    void connect_aggr_core();
    void connect_aggr_edge();
    void connect_edge_aggr();
    void connect_edge_host();
    void connect_host_edge();
    

private:
    int k ; 
    std::vector<Host> hosts;
    std::vector<CoreSwitch> cores; 
    std::vector<EdgeSwitch> edges;
    std::vector<AggrSwitch> aggrs;
};//engine 

}//fattree

#endif