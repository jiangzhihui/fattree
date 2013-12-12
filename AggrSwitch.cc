#include <iostream>
#include "AggrSwitch.h"
#include "EdgeSwitch.h"
#include "CoreSwitch.h"


using namespace std; 

void fattree::AggrSwitch::set_switch(size_t port, CoreSwitch*s){
    cs[port-ports/2] = s;
}

void fattree::AggrSwitch::set_switch(size_t port, EdgeSwitch*s){
    es[port] = s;
}

void fattree::AggrSwitch::generate_route_table(){
    //generate first level table for the ips in the same pod     
    vector<int> dotted_ip = split_ip(ip); 
    int pod = dotted_ip[1];
    int swi = dotted_ip[2];
    for(int s = 0; s < ports/2; s ++){
        string key = "10."; 
        key += itoa(pod);
        key += ".";
        key += itoa(s); 
        key += ".0";
        table1[key] = s;
    }

    //generate second level table for the ips in different pods
    for(int host = 2; host <= ports/2+1; host++){
        int port = (host-2+swi)%(ports/2) ;
        string key = "0.0.0."; 
        key += itoa(host); 
        table2[key] = port;
    }
}

void fattree::AggrSwitch::print_route_table(){
    cout << "My ip address is " << get_ip() << endl;
    IpPortTable::const_iterator pos = table1.begin(); 
    while(pos != table1.end()){
        cout << pos->first << "->" << pos->second <<"->" <<  es[pos->second]->get_ip() << endl;
        pos ++;
    }
    pos = table2.begin();
    while(pos != table2.end()){
        cout << pos->first << "->" << pos->second + ports/2 <<"->" <<  cs[pos->second]->get_ip() << endl;
        pos ++;
    }
    cout << endl;
}
