#include <iostream>
#include <cassert>
#include <cstdlib>
#include "host.h"
#include "EdgeSwitch.h" 
#include "AggrSwitch.h"
#include "packet.h"
#include "Cache.h"
#include "debug.h"


using namespace std; 

fattree::EdgeSwitch::~EdgeSwitch(){
    if(cache)
        delete cache;
}

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

    bool up;            //link direction type up or down 
    if(table.find(dest) == table.end())
        up = true;
    else 
        up = false;

    unsigned int data = pkt.data[0];
    if(cache){
        Packet p; 
        if(!cache->get(data,p)){
            cache->put(data,p);
            if(up)
                up_miss ++;
            else 
                down_miss ++; 
        }else {
            if(up)
                up_hit ++; 
            else 
                down_hit ++;
        }
    }

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

int fattree::EdgeSwitch::get_cache_hit(){
    if(cache)
        return cache->hit_cnt();
    return -1;
}

int fattree::EdgeSwitch::get_cache_miss(){
    if(cache)
        return cache->miss_cnt();
    return -1;
}

//return the up link and down link hit count as a pair
pair<int,int> fattree::EdgeSwitch::get_cache_hit_pair(){
    return pair<int,int>(up_hit,down_hit);
}

//return the up link and down link miss count as a pair
pair<int,int> fattree::EdgeSwitch::get_cache_miss_pair(){
    return pair<int,int>(up_miss,down_miss);
}
