#include "EdgeSwitch.h" 

void fattree::EdgeSwitch::set_switch(size_t port, AggrSwitch*s){
    switches[port-ports/2] = s;
}

void fattree::EdgeSwitch::set_host(size_t port, Host * h){
    hosts[port] = h;
}
