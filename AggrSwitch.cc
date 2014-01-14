#include <iostream>
#include <cassert>
#include "AggrSwitch.h"
#include "EdgeSwitch.h"
#include "CoreSwitch.h"
#include "packet.h"
#include "debug.h"
#include "Cache.h"
#include "Switch.h"


using namespace std; 
using namespace fattree;

fattree::AggrSwitch::~AggrSwitch(){
    if(cache)
        delete cache;
}

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
    for(size_t s = 0; s < ports/2; s ++){
        string key = "10."; 
        key += itoa(pod);
        key += ".";
        key += itoa(s); 
        key += ".0";
        table1[key] = s;
    }

    //generate second level table for the ips in different pods
    for(size_t host = 2; host <= ports/2+1; host++){
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


void fattree::AggrSwitch::send_packet(const Packet& pkt){
    //handle cache
    string dest = pkt.dest;
    vector<int> ips = split_ip(dest);
    string prefix = connect_ip("10",itoa(ips[1]),itoa(ips[2]),"0");
    bool up ; 
    if(table1.find(prefix) == table1.end())
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

    //route packet
    IpPortTable::iterator pos = table1.find(prefix);
    if(pos != table1.end()){
        size_t i = pos->second;
        assert(i < es.size());
        Debug::info("Aggr switch " +  get_ip() + " send a packet to " + es[i]->get_ip());
        es[i]->send_packet(pkt);
    }else {
        string suffix = connect_ip("0","0","0",itoa(ips[3]));
        pos = table2.find(suffix);
        assert(pos != table2.end());
        int i = pos->second; 
        Debug::info("Aggr switch " + get_ip() + " send a packet to " + cs[i]->get_ip());
        cs[i]->send_packet(pkt);
        
    }
}

int fattree::AggrSwitch::get_cache_hit(){
    if(cache)
        return cache->hit_cnt();
    return -1;
}

int fattree::AggrSwitch::get_cache_miss(){
    if(cache)
        return cache->miss_cnt();
    return -1;
}

pair<int,int> fattree::AggrSwitch::get_cache_hit_pair(){
    return pair<int,int>(up_hit,down_hit);
}

pair<int,int> fattree::AggrSwitch::get_cache_miss_pair(){
    return pair<int,int>(up_miss,down_miss);
}

Switch* fattree::AggrSwitch::next_hop(Packet * pkt){
    string dest = pkt->dest;
    vector<int> ips = split_ip(dest);
    string prefix = connect_ip("10",itoa(ips[1]),itoa(ips[2]),"0");
    IpPortTable::iterator pos = table1.find(prefix);
    if(pos != table1.end()){
        size_t i = pos->second;
        assert(i < es.size());
        Debug::info("Aggr switch " +  get_ip() + " send a packet to " + es[i]->get_ip());
        return es[i];
    }else {
        string suffix = connect_ip("0","0","0",itoa(ips[3]));
        pos = table2.find(suffix);
        assert(pos != table2.end());
        int i = pos->second; 
        Debug::info("Aggr switch " + get_ip() + " send a packet to " + cs[i]->get_ip());
        return cs[i];
    }
}
