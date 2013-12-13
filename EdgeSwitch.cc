#include <iostream>
#include <cassert>
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
    vector<int> dotted_ip = split_ip(ip);
    int pod = dotted_ip[1];
    int swi = dotted_ip[2];
    for(size_t i = 2; i <= ports/2+1; i++){
        string key = "10."; 
        key += itoa(pod);
        key += ".";
        key += itoa(swi);
        key += ".";
        key += itoa(i);
        table[key] = i-2;
    }
}

void fattree::EdgeSwitch::print_route_table(){
    IpPortTable::iterator pos = table.begin();
    while(pos != table.end()){
        assert(hosts[pos->second] != NULL);
        cout << pos->first << "->" << pos->second << "->" << hosts[pos->second]->get_ip()<< endl;    
        pos++;
    }
}
