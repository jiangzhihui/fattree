#ifndef _FATTREE_AGGRSWITCH_H
#define _FATTREE_AGRRSWITCH_H

#include <vector>
#include <string>
#include <utility>
#include "utility.h"
#include "Switch.h"

namespace fattree{


class EdgeSwitch;
class CoreSwitch;
class Packet;
class Cache;
class Switch;

class AggrSwitch:public Switch{
public:
    AggrSwitch(std::string ip="",size_t ports = 4)
        :ports(ports),es(ports/2),cs(ports/2),ip(ip),cache(NULL)
    {
        up_hit = down_hit = up_miss = down_miss = 0;
    }    

    ~AggrSwitch();

    void set_switch(size_t port_id, CoreSwitch* s);
    void set_switch(size_t port_id, EdgeSwitch* s);
    void send_packet(const Packet &);
    void recv(size_t port);
    virtual std::string get_ip() const {
        return ip; 
    }

    void print_route_table();
    //generate first level and second level routing table
    void generate_route_table();

    int get_cache_hit();
    int get_cache_miss();
    void set_cache(Cache* c){
        cache = c;
    }
    
    std::pair<int,int> get_cache_hit_pair();
    std::pair<int,int> get_cache_miss_pair();

    virtual Switch* next_hop(Packet*); 
    virtual Cache* get_cache(){
        return cache;
    }
private:


private:
    size_t ports; 
    std::vector<EdgeSwitch*> es; 
    std::vector<CoreSwitch*> cs;
    std::string ip;
    IpPortTable table1,table2; 
    Cache* cache ; 
    int up_hit,down_hit,up_miss,down_miss;

};//AggrSwtich

}//fattree

#endif 
