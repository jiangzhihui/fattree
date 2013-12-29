#ifndef _FATTREE_AGGRSWITCH_H
#define _FATTREE_AGRRSWITCH_H

#include <vector>
#include <string>
#include "utility.h"

namespace fattree{


class EdgeSwitch;
class CoreSwitch;
class Packet;
class Cache;

class AggrSwitch{
public:
    AggrSwitch(std::string ip="",size_t ports = 4)
        :ports(ports),es(ports/2),cs(ports/2),ip(ip),cache(NULL)
    {
 //       generate_route_table();
    }    

    void set_switch(size_t port_id, CoreSwitch* s);
    void set_switch(size_t port_id, EdgeSwitch* s);
    void send_packet(const Packet &);
    void recv(size_t port);
    std::string get_ip() const {
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

private:


private:
    size_t ports; 
    std::vector<EdgeSwitch*> es; 
    std::vector<CoreSwitch*> cs;
    std::string ip;
    IpPortTable table1,table2; 
    Cache* cache ; 

};//AggrSwtich

}//fattree

#endif 
