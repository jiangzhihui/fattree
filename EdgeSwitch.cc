#include <iostream>
#include <cassert>
#include <cstdlib>
#include "host.h"
#include "EdgeSwitch.h" 
#include "AggrSwitch.h"
#include "packet.h"
#include "debug.h"

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
        string key = connect_ip("10",itoa(pod),itoa(swi),itoa(i));
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

/*
First search the destination address in the routing table;
If found, then the dest ip is in the same subnet
If not found, then the send the packet to upper level switches
*/
void fattree::EdgeSwitch::send_packet(const Packet& pkt){
    string dest = pkt.dest; 
    IpPortTable::iterator pos = table.find(dest);
    if(pos != table.end()){
        int port = pos->second;
        fattree::Debug::info("Edge switch " + get_ip() + " send a packet to " + hosts[port]->get_ip());
        hosts[port]->recv_packet(pkt);
    }else{
        int swi = rand()%switches.size();  
        fattree::Debug::info("Edge switch " + get_ip() + " send a packet to " + switches[swi]->get_ip());
        switches[swi]->send_packet(pkt);
    }
}
