#include <iostream>
#include <vector>
#include "CachePlaceComp.h"
#include "Switch.h"
#include "fattree.h"
#include "host.h"

using namespace std; 
using namespace fattree;


const int MAXPKTS = 100000; 

void CachePlaceComp::last_hop(){
    Config cfg = read_config("config1");  
    int ports = 4; 
    Engine e(ports,cfg);
    /*
    for(int i = 0; i < MAXPKTS; i++){
        Packet p = e.generate_rand_packet();
        vector<Switch*> swis = get_switches(p,e);
        cout << p.src << " -> " ; 
        for(size_t j = 0; j < swis.size(); j++){
            cout << swis[j]->get_ip() << " -> " ; 
        }
        cout << p.dest << endl;
    }
    */

    int saved = 0; 
    int total = 0;
    for(int i = 0; i < MAXPKTS; i++){
        Packet p = e.generate_rand_packet();
        vector<Switch*> swis = get_switches(p,e);     
        int len = swis.size();
        int j; 
        for(j = len-1; j >= 0; j--){
            Cache * cache = swis[j]->get_cache();    
            if(cache && cache->get(p.data[0],p))
                break;
        }

        if(j >= 0){
            saved += j; 
        }
        total += len-1;
        for(int j = 0; j < len; j++){
            Cache * c = swis[j]->get_cache();
            c->put(p.data[0],p);
        }
    }
    cout << "saved " << saved << "  total " << total << " " << saved*100.0/total <<"%"<< endl;
}

vector<Switch*> CachePlaceComp::get_switches(Packet & p, Engine & e){
    vector<Switch*> re; 
    Host host = e.get_host_by_ip(p.src);  
    Switch * swi = host.next_hop(p);
    while(swi){
        re.push_back(swi);
        swi = swi->next_hop(&p);
    }
    return re;
}
