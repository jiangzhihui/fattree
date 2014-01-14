#ifndef _FATTREE_HOST_H
#define _FATTREE_HOST_H

#include <string>


namespace fattree{

class EdgeSwitch;
class Packet;
class Switch;

class Host{
public:
    Host(std::string ip="", EdgeSwitch *s = 0):ip(ip),swit(s){}
    void set_switch(EdgeSwitch*s){
        swit = s;
    }
    void send_packet(const Packet &);
    void recv_packet(const Packet &);
    std::string get_ip() const {
        return ip;
    }
    Switch* next_hop(Packet&); 
private:
    std::string ip;
    EdgeSwitch* swit;               //switch the host connects to 
};

}//fattree
#endif 
