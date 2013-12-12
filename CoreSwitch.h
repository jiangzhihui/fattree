#ifndef _FATTREE_CORESWITCH_H
#define _FATTREE_CORESWITCH_H

#include <string> 
#include <vector>
#include "utility.h"

namespace fattree{

class AggrSwitch;

class CoreSwitch{
public:
    CoreSwitch(std::string ip="",size_t ports = 4):ports(ports),switches(ports),ip(ip){
//        generate_route_table();     
    }

    void set_switch(size_t port_id, AggrSwitch* s);
    void send(size_t port);
    void recv(size_t port);
    std::string get_ip() const {
        return ip;
    }
    void generate_route_table();
    void print_route_table();

private:

    //get the i,j position of a core switch from its ip address 
    std::pair<int,int> get_position();  

private:
    size_t ports; 
    std::vector<AggrSwitch*> switches; 
    std::string ip;
    IpPortTable route_table;

};//CoreSwitch

}//fattree
#endif 
