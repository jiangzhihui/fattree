#include <iostream>
#include <sstream>
#include <cassert>
#include <climits>
#include "fattree.h"
#include "zipf.h"

namespace fattree{

using namespace std; 

/*
void generate(int k){
    for(int pod = 0 ; pod < k; pod ++){
        for(int swit = k/2; swit < k ; swit++){
            cout << "switch ip address 10." << pod <<"." << swit << "." << 1 << endl;
            for(int subnet = 0 ; subnet < k/2 ; subnet ++){
                cout << "10." << pod << "." << swit <<".1   "; 
                cout << "10." << pod << "." << subnet <<".0/24  "; 
                cout << subnet << endl;
            }
            //cout << "10." << pod << "." << swit <<".1   "; 
            //cout << "0.0.0.0/0  0" << endl;
            for(int host = 2; host <= k/2+1 ;host ++){
                cout << "10." << pod <<"." << swit <<".1   " ; 
                cout << "0.0.0." << host << "/8 " ; 
                cout << (host-2+swit)%(k/2)+k/2 << endl; 
            }

            cout << "\n\n\n" << endl;
        }
    }
}
*/

void fattree::Engine::init_cores(){
    int id = 0; 
    for(int i = 1; i <= k/2; i++)
        for(int j = 1; j <= k/2; j++){
            string ip = connect_ip("10",itoa(k),itoa(i),itoa(j));
            /*
            stringstream ss; 
            ss << "10." ; 
            ss << k ; 
            ss << "."; 
            ss << i;     
            ss << ".";
            ss << j;
            ss >> ip ; 
            */
            cores[id++] = CoreSwitch(ip,k);
            cores[id-1].generate_route_table();
        }
}

void fattree::Engine::init_aggrs(){
    int id = 0; 
    for(int pod = 0; pod < k ; pod ++){
        for(int swi = k/2; swi < k; swi ++){
            string ip = connect_ip("10",itoa(pod),itoa(swi),"1");
            /*
            stringstream ss; 
            ss << "10." ; 
            ss << pod; 
            ss << ".";
            ss << swi; 
            ss << ".1";
            ss >> ip ; 
            */
            aggrs[id++] = AggrSwitch(ip,k);
            aggrs[id-1].generate_route_table();
        }
    }
}

void fattree::Engine::init_edges(){
    int id = 0; 
    for(int pod = 0; pod < k; pod ++){
        for(int swi = 0; swi < k/2; swi++){
            string ip = connect_ip("10",itoa(pod),itoa(swi),"1");
            /*
            stringstream ss; 
            ss << "10.";
            ss << pod; 
            ss << ".";
            ss << swi; 
            ss << ".1";
            ss >> ip ; 
            */
            edges[id++] = EdgeSwitch(ip,k);
            edges[id-1].generate_route_table();
        }
    }
}

void fattree::Engine::init_hosts(){
    int id = 0; 
    for(int pod = 0; pod < k; pod ++){
        for(int swi = 0 ; swi < k/2; swi ++){
            for(int h = 2; h <= k/2 + 1; h++){
                string ip = connect_ip("10",itoa(pod),itoa(swi),itoa(h));
                /*
                stringstream ss; 
                ss <<  "10." ; 
                ss << pod; 
                ss << ".";
                ss << swi; 
                ss << ".";
                ss << h; 
                ss >> ip ; 
                */
                hosts[id++] = Host(ip);
            }
        }
    }
}

void fattree::Engine::connect_core_aggr(){
    for(int i = 0; i < k/2; i++){
        for(int j = 0; j < k/2; j++){
            int id = i*k/2+j;
            CoreSwitch & cs = cores[id];

            //connect each port to the aggr switches
            for(int pod = 0; pod < k; pod++){
                int aggr_id = pod*k/2 + i;
                AggrSwitch & as = aggrs[aggr_id]; 
                cs.set_switch(pod,&as); 
                //cout << cs.get_ip() << " --> "  << as.get_ip() << endl;
            }
        }
    }
    //cout << endl << endl;
}

/*
connect each AggrSwitch to k/2 core switch from its port k/2 ~ k-1
*/
void fattree::Engine::connect_aggr_core(){
    for(int pod = 0; pod < k; pod ++){
        for(int i = 0; i < k/2; i++){
            int id = pod*k/2 + i;
            AggrSwitch& as = aggrs[id];
            
            //connect each port to a Core Switch 
            for(int p = 0; p < k/2; p++){
                int cs_id = i*k/2 + p; 
                CoreSwitch & cs = cores[cs_id];
                as.set_switch(k/2+p,&cs); 
                //cout << as.get_ip() << " --> " << cs.get_ip() << endl;
            }
        }
    }

    //cout << endl << endl;
}

/*
connect each Aggr Switch to edge switches from its port 0~(k/2-1)
*/
void fattree::Engine::connect_aggr_edge(){
    for(int pod = 0; pod < k; pod ++){
        for(int i = 0; i < k/2; i++){
            int id = pod*k/2 + i; 
            AggrSwitch& as = aggrs[id];

            //connect each port [0,k/2) to the lower level edge switches 
            for(int port = 0; port < k/2; port ++){
                int id = pod*k/2 + port; 
                EdgeSwitch& es = edges[id]; 
                as.set_switch(port,&es);
                //cout << as.get_ip() << " --> " << es.get_ip() << endl;
            }
        }
    }
    //cout << endl << endl;
}

/*
connect edge switch to upper level aggr switches 
*/
void fattree::Engine::connect_edge_aggr(){
    for(int pod = 0; pod < k; pod ++){
        for(int i=0; i < k/2; i++){
            //the index of the edge switch 
            int id = pod*k/2 + i; 
            EdgeSwitch&es = edges[id];

            for(int port = k/2; port < k; port ++){
                int aggr_id = pod*k/2 + port-k/2;
                AggrSwitch& as = aggrs[aggr_id];
                es.set_switch(port,&as);
            }
        }
    }
}

/*
connect edge switch to its lower level hosts 
*/
void fattree::Engine::connect_edge_host(){
    for(int pod = 0; pod < k; pod ++){
        for(int i = 0; i < k/2; i++){
            int id = pod*k/2 + i; 
            EdgeSwitch& es = edges[id];
            
            for(int port = 0; port < k/2; port ++){
                int host_id = pod*(k/2)*(k/2) + i*k/2 + port; 
                Host& h = hosts[host_id]; 
                es.set_host(port,&h);      
            }
        }
    }
}

/*
connect each host to its upper level edge switches 
*/
void fattree::Engine::connect_host_edge(){
    for(int pod = 0; pod < k; pod ++){
        for(int e = 0; e < k/2; e++){
            for(int h = 0; h < k/2; h++){
                Host& host = hosts[pod*(k/2)*(k/2)+e*k/2+h];
                EdgeSwitch& es = edges[pod*k/2+e];
                host.set_switch(&es);    
            }
        }
    }
    //cout << endl << endl;
}

/*
connect all the devices in a datacenter 
*/
void fattree::Engine::connect_devices(){
    connect_core_aggr();
    connect_aggr_core();
    connect_aggr_edge();
    connect_edge_aggr();
    connect_edge_host();
    connect_host_edge();
}

/*
init switches and hosts
*/
void fattree::Engine::init_devices(){
    init_cores();
    init_aggrs();
    init_edges();
    init_hosts();
    set_caches();
}

void fattree::Engine::set_caches(){
    set_edge_cache();
    set_aggr_cache();
    set_core_cache();
}

//!!!!!!  the following three methods to be reconstructed 
/*
select random core switches to set a cache
*/
void fattree::Engine::set_core_cache(){
    int caches = cores.size() / 2; 
    int cnt = 0; 
    vector<bool> cached(cores.size(),0);
    while(cnt < caches){
        int i = get_rand(0,cores.size());
        if(!cached[i]){
            cnt ++;
            cached[i] = 1; 
        }
    }

    for(size_t i = 0; i < cores.size(); i++){
        if(cached[i])
            cores[i].set_cache(new Cache(cfg.max_core_cache));
    }

}

/*
select random aggr switches to set a cache
*/
void fattree::Engine::set_aggr_cache(){
    int caches = aggrs.size() / 2; 
    int cnt = 0; 
    vector<bool> cached(aggrs.size(),0);
    while(cnt < caches){
        int i = get_rand(0,aggrs.size());
        if(!cached[i]){
            cnt ++;
            cached[i] = 1; 
        }
    }

    for(size_t i = 0; i < aggrs.size(); i++){
        if(cached[i])
            aggrs[i].set_cache(new Cache(cfg.max_aggr_cache));
    }
}

/*
select random edge switches to set a cache
*/
void fattree::Engine::set_edge_cache(){
    int caches = edges.size()/2;   
    int cnt = 0; 
    vector<bool> cached(edges.size(),0);  
    while(cnt < caches){
        int i = get_rand(0,edges.size());
        if(!cached[i]){
            cnt ++;
            cached[i] = 1;    
        }
    }

    for(size_t i = 0; i < edges.size(); i++){
        if(cached[i]){
            edges[i].set_cache(new Cache(cfg.max_edge_cache));
        }
    }
}

vector<int> fattree::Engine::get_edge_hit_cnt(){

    vector<int> cnt(edges.size(),-1);
    for(size_t i = 0; i < edges.size(); i++){
        cnt[i] = edges[i].get_cache_hit();
    }

    return cnt;
}

vector<int> fattree::Engine::get_edge_miss_cnt(){
    vector<int> cnt(edges.size(),-1);
    for(size_t i = 0; i < edges.size(); i++){
        cnt[i] = edges[i].get_cache_miss();
    }
    return cnt;
}

vector<int> fattree::Engine::get_aggr_hit_cnt(){
    vector<int> cnt(aggrs.size(),-1);
    for(size_t i = 0; i < aggrs.size(); i++){
        cnt[i] = aggrs[i].get_cache_hit();
    }

    return cnt;
}

vector<int> fattree::Engine::get_aggr_miss_cnt(){
    vector<int> cnt(aggrs.size(),-1);
    for(size_t i = 0; i < aggrs.size(); i++){
        cnt[i] = aggrs[i].get_cache_miss();
    }
    return cnt;
}

vector<int> fattree::Engine::get_core_hit_cnt(){
    vector<int> cnt(cores.size(),-1);
    for(size_t i = 0; i < cores.size(); i++){
        cnt[i] = cores[i].get_cache_hit();
    }
    return cnt;
}

vector<int> fattree::Engine::get_core_miss_cnt(){
    vector<int> cnt(cores.size(),-1);
    for(size_t i = 0; i < cores.size(); i++){
        cnt[i] = cores[i].get_cache_miss();
    }
    return cnt;
}

void fattree::Engine::print_cores(){
    cout << "The ip of all the core switches:" << endl;
    for(size_t i = 0; i < cores.size() ; i++){
        cout << cores[i].get_ip() << endl; 
        /*
        cout << "the aggr switches it connects to:"  << endl; 
        for(int p = 0; p < k; p++){
            AggrSwitch * asp = cores[i].switches[p];
            if(asp == NULL)
                cout << p << " NULL" << endl;
            else 
                cout << p << "->" << cores[i].switches[p]->get_ip() << endl;
        }
        */
    }
}

void fattree::Engine::print_edges(){
    cout <<"The ip of all the edge switches:" << endl;
    for(size_t i =0 ; i < edges.size(); i ++){
        cout << edges[i].get_ip() << endl;
        /*
        cout <<"the core switches it connects to: " << endl;
        for(int j = 0; j < k/2; j++)
            cout << k/2+j << "->" << edges[i].switches[j]->get_ip() << endl;
        cout << "the hosts it connects to: " << endl; 
        for(int j = 0; j < k/2; j++)
            cout << j << "->" << edges[i].hosts[j]->get_ip() << endl; 
        */
    }
}

void fattree::Engine::print_aggrs(){
    cout <<"The ip of all the aggr switches:" << endl;
    for(size_t i = 0; i < aggrs.size(); i++){
        cout << aggrs[i].get_ip() << endl;
        /*
        cout << "the core switches it connects to:" << endl;
        for(int j = 0; j < k/2; j++)
            cout << k/2+j << "->" << aggrs[i].cs[j]->get_ip() << endl;  
        cout <<"the edge switches it connects to:" << endl;
        for(int j = 0; j < k/2; j++)
            cout << j << "->" << aggrs[i].es[j]->get_ip() << endl;  
        */
    }
}

void fattree::Engine::print_hosts(){
    cout <<"The ip of all the hosts:" << endl; 
    for(size_t i = 0; i < aggrs.size(); i++){
        cout << hosts[i].get_ip() << endl;
        //cout << "the switch it connects to " << hosts[i].swit->get_ip() << endl;
    }
}


void fattree::Engine::print_core_table(){
    for(int i = 0; i < k*k/4; i++)
        cores[i].print_route_table();      
}

void fattree::Engine::print_aggr_table(){
    for(int i = 0; i < k*k/2; i++)
        aggrs[i].print_route_table();
}

void fattree::Engine::print_edge_table(){
    for(int i = 0; i < k*k/2; i++)
        edges[i].print_route_table();
}

Packet fattree::Engine::generate_rand_packet(){
    Packet pkt; 
    string src,dest; 
    src = rand_ip(k); 
    while((dest=rand_ip(k)) == src){}                             
    pkt.src = src;
    pkt.dest = dest;
    /*
    //packet data random distribution 
    for(int i = 0; i < MAX_LENGTH; i++)
        pkt.data[i] = get_rand(0,USHRT_MAX);    
    */

    //packet data zipf distribution 
    Zipf zipf(0.5,USHRT_MAX);
    for(int i = 0; i < MAX_LENGTH; i ++){
        pkt.data[i] = zipf.next();
    }

    string debug_info = "Generated a packet with source " + src + " and dest " + dest; 
    Debug::info(debug_info);

    return pkt;
}

void fattree::Engine::send_packet(Packet & pkt){
    Debug::info("Engine starts sending a packet");
    vector<int> ips = split_ip(pkt.src);
    int pod = ips[1];
    int swi = ips[2];
    int h = ips[3];
    size_t id = pod * k/2*k/2 + swi*k/2 + (h-2) ;     
    //cout << pod <<  " " << swi << " " << h << " " << id << endl;
    assert(id < hosts.size());
    hosts[id].send_packet(pkt);
}

}//fattree
