#ifndef _FATTREE_AGGRSWITCH_H
#define _FATTREE_AGRRSWITCH_H

#include <vector>
#include <string>

namespace fattree{


class EdgeSwitch;
class CoreSwitch;

class AggrSwitch{
public:
    AggrSwitch(std::string ip="",size_t ports = 4)
        :ports(ports),es(ports/2),cs(ports/2),ip(ip)
    {}    

    void set_switch(size_t port_id, CoreSwitch* s);
    void set_switch(size_t port_id, EdgeSwitch* s);
    void send(size_t port);
    void recv(size_t port);
    std::string get_ip() const {
        return ip; 
    }

private:
    size_t ports; 
    std::vector<EdgeSwitch*> es; 
    std::vector<CoreSwitch*> cs;
    std::string ip;

};//AggrSwtich

}//fattree

#endif 
