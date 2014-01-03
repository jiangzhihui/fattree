#ifndef _FATTREE_FATTREE_H
#define _FATTREE_FATTREE_H

#include <vector>
#include <string>
#include "host.h"
#include "EdgeSwitch.h" 
#include "AggrSwitch.h" 
#include "CoreSwitch.h"
#include "packet.h"
#include "Cache.h"
#include "debug.h"

namespace fattree{

struct Config{
    size_t max_edge_cache;
    size_t max_aggr_cache; 
    size_t max_core_cache;
};

class Engine{
public:
    Engine(int k,Config cfg):k(k),hosts(k*k*k/4),cores(k*k/4),edges(k*k/2),aggrs(k*k/2),cfg(cfg){
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
    void print_aggr_table();
    void print_edge_table();

    /*
    generate a packet with random source host and destination host with random data
    */
    Packet generate_rand_packet(); 
    void send_packet(Packet&);

    std::vector<int> get_edge_hit_cnt();
    std::vector<int> get_edge_miss_cnt(); 
    std::vector<int> get_aggr_hit_cnt();
    std::vector<int> get_aggr_miss_cnt();
    std::vector<int> get_core_hit_cnt();
    std::vector<int> get_core_miss_cnt();

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
    void set_edge_cache();    
    void set_aggr_cache();
    void set_core_cache();
    void set_caches();

private:
    //k is the port number of a switch 
    int k ; 
    std::vector<Host> hosts;
    std::vector<CoreSwitch> cores; 
    std::vector<EdgeSwitch> edges;
    std::vector<AggrSwitch> aggrs;
    static const unsigned int MAX_EDGE_CACHE = 10000;
    static const unsigned int MAX_AGGR_CACHE = 1000; 
    static const unsigned int MAX_CORE_CACHE = 1000;
    Config cfg;
};//engine 

}//fattree

#endif
