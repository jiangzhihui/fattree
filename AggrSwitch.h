#ifndef _FATTREE_AGGRSWITCH_H
#define _FATTREE_AGRRSWITCH_H

#include <vector>
#include <string>
#include "utility.h"

namespace fattree{


class EdgeSwitch;
class CoreSwitch;

class AggrSwitch{
public:
    AggrSwitch(std::string ip="",size_t ports = 4)
        :ports(ports),es(ports/2),cs(ports/2),ip(ip)
    {
 //       generate_route_table();
    }    

    void set_switch(size_t port_id, CoreSwitch* s);
    void set_switch(size_t port_id, EdgeSwitch* s);
    void send(size_t port);
    void recv(size_t port);
    std::string get_ip() const {
        return ip; 
    }

    void print_route_table();
    //generate first level and second level routing table
    void generate_route_table();

private:


private:
    size_t ports; 
    std::vector<EdgeSwitch*> es; 
    std::vector<CoreSwitch*> cs;
    std::string ip;
    IpPortTable table1,table2; 

};//AggrSwtich

}//fattree

#endif 
