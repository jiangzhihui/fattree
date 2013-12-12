#include <iostream>
#include "host.h"
#include "EdgeSwitch.h" 

using namespace std; 

void fattree::EdgeSwitch::set_switch(size_t port, AggrSwitch*s){
    switches[port-ports/2] = s;
}

void fattree::EdgeSwitch::set_host(size_t port, Host * h){
    hosts[port] = h;
}

void fattree::EdgeSwitch::generate_route_table(){
    for(int i = 0; i < ports/2; i++){
        string key = hosts[i]->get_ip(); 
        table[key] = i;    
    }
}

void fattree::EdgeSwitch::print_route_table(){
    IpPortTable::iterator pos = table.begin();
    while(pos != table.end()){
        cout << pos->first << "->" << pos->second << endl;    
        pos++;
    }
}
