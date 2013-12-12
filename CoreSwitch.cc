#include <iostream>
#include "CoreSwitch.h"
#include "AggrSwitch.h"
#include "utility.h" 

using namespace std; 

void fattree::CoreSwitch::set_switch(size_t port_id,AggrSwitch*s){
    switches[port_id] = s;
    //cout << "the port of core " << get_ip() << " " << port_id << endl;
}

/*
generate the routing table of core switch 
*/
void fattree::CoreSwitch::generate_route_table(){
    //pair<int,int> pos = get_position();    
    for(size_t pod = 0; pod < ports; pod ++){
        string key = "10."; 
        key += itoa(pod);    
        key += ".0.0";
        route_table[key] = pod;
    }
}

pair<int,int> fattree::CoreSwitch::get_position(){
    pair<int,int> re;
    std::vector<int> dotted_ip = split_ip(ip);
    re.first = dotted_ip[2]; 
    re.second = dotted_ip[3];
    return re;
}

void fattree::CoreSwitch::print_route_table(){
    cout << "My ip is " << get_ip() << endl;
    IpPortTable::iterator pos = route_table.begin();
    while(pos != route_table.end()){
        cout << pos->first << "->" << pos->second  << "->" << switches[pos->second]->get_ip()<< endl; 
        pos ++;
    }
}
