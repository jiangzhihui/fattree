#ifndef _FATTREE_EDGESWITCH_H
#define _FATTREE_EDGESWITCH_H

#include <vector>
#include <string> 
#include "utility.h"

namespace fattree{

class Host;
class AggrSwitch;
class Packet;
class Cache;

class EdgeSwitch{
public:
    EdgeSwitch(std::string ip="", size_t ports = 4)
        :ports(ports),hosts(ports/2),switches(ports/2),ip(ip),cache(NULL)
    {}
    
    ~EdgeSwitch();

    void set_host(size_t port_id, Host * host);
    void set_switch(size_t port_id, AggrSwitch* s);
    void send_packet(const Packet & pkt);
    void recv(size_t port);
    std::string get_ip() const {
        return ip;
    }
    
    void generate_route_table();
    void print_route_table();
    int get_cache_hit();
    int get_cache_miss();
    void set_cache(Cache * c){
        cache = c;
    }

private:
    size_t ports; 
    std::vector<Host*> hosts;
    std::vector<AggrSwitch*> switches; 
    std::string ip;

    //table stores the map to hosts
    IpPortTable table;
    Cache * cache;

};//EdgeSwitch

}//fattree

#endif 
