#include "AggrSwitch.h"


void fattree::AggrSwitch::set_switch(size_t port, CoreSwitch*s){
    cs[port-ports/2] = s;
}

void fattree::AggrSwitch::set_switch(size_t port, EdgeSwitch*s){
    es[port] = s;
}

