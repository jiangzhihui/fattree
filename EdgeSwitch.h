#ifndef _FATTREE_EDGESWITCH_H
#define _FATTREE_EDGESWITCH_H

#include <vector>
#include <string> 

namespace fattree{

class Host;
class AggrSwitch;

class EdgeSwitch{
public:
    EdgeSwitch(std::string ip="", size_t ports = 4)
        :ports(ports),hosts(ports/2),switches(ports/2),ip(ip)
    {}

    void set_host(size_t port_id, Host * host);
    void set_switch(size_t port_id, AggrSwitch* s);
    void send(size_t port);
    void recv(size_t port);
    std::string get_ip() const {
        return ip;
    }

private:
    size_t ports; 
    std::vector<Host*> hosts;
    std::vector<AggrSwitch*> switches; 
    std::string ip;

};//EdgeSwitch

}//fattree

#endif 
