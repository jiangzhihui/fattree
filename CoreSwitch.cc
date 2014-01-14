#include <iostream>
#include <cassert>
#include "CoreSwitch.h"
#include "AggrSwitch.h"
#include "utility.h" 
#include "packet.h"
#include "Cache.h"
#include "debug.h"

using namespace std; 
using namespace fattree;

fattree::CoreSwitch::~CoreSwitch(){
    if(cache)
        delete cache;
}

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

void fattree::CoreSwitch::send_packet(const Packet & pkt){
    if(cache){
        unsigned int key = generate_pkt_key(pkt);
        Packet p;
        if(!cache->get(key,p))
            cache->put(key,p);
    }
    string dest = pkt.dest;
    vector<int> ips = split_ip(dest);
    string mask = connect_ip("10",itoa(ips[1]),"0","0");
    IpPortTable::iterator pos = route_table.find(mask);
    assert(pos != route_table.end());
    Debug::info("Core Switch " + get_ip() + " send a packet to " + switches[pos->second]->get_ip());
    switches[pos->second]->send_packet(pkt);
}

int fattree::CoreSwitch::get_cache_hit(){
    if(cache)
        return cache->hit_cnt();
    return -1;
}

int fattree::CoreSwitch::get_cache_miss(){
    if(cache)
        return cache->miss_cnt();
    return -1;
}

Switch* CoreSwitch::next_hop(Packet* pkt){
    string dest = pkt->dest;
    vector<int> ips = split_ip(dest);
    string mask = connect_ip("10",itoa(ips[1]),"0","0");
    IpPortTable::iterator pos = route_table.find(mask);
    assert(pos != route_table.end());
    Debug::info("Core Switch " + get_ip() + " send a packet to " + switches[pos->second]->get_ip());
    //switches[pos->second]->send_packet(pkt);
    return switches[pos->second];
}
