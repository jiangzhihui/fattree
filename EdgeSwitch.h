#ifndef _FATTREE_EDGESWITCH_H
#define _FATTREE_EDGESWITCH_H

#include <vector>
#include <string> 
#include <utility>
#include "utility.h"
#include "Switch.h"

namespace fattree{

class Host;
class AggrSwitch;
class Packet;
class Cache;

class EdgeSwitch: public Switch{
public:
    EdgeSwitch(std::string ip="", size_t ports = 4)
        :ports(ports),hosts(ports/2),switches(ports/2),ip(ip),cache(NULL)
    {
        up_hit = down_hit = up_miss = down_miss = 0;     
    }
    
    ~EdgeSwitch();

    void set_host(size_t port_id, Host * host);
    void set_switch(size_t port_id, AggrSwitch* s);
    void send_packet(const Packet & pkt);
    void recv(size_t port);
    virtual std::string get_ip() const {
        return ip;
    }
    
    void generate_route_table();
    void print_route_table();
    int get_cache_hit();
    int get_cache_miss();
    std::pair<int,int> get_cache_hit_pair( );
    std::pair<int,int> get_cache_miss_pair();
    void set_cache(Cache * c){
        cache = c;
    }

    virtual Switch* next_hop(Packet*);
    virtual Cache* get_cache(){
        return cache;
    }
private:
    size_t ports; 
    std::vector<Host*> hosts;
    std::vector<AggrSwitch*> switches; 
    std::string ip;

    //table stores the map to hosts
    IpPortTable table;
    Cache * cache;
    int up_hit,down_hit,up_miss,down_miss;

};//EdgeSwitch

}//fattree

#endif 
