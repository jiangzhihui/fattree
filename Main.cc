/*                                                                              
 ============================================================================
 Name        : 
 Author      : Zhihui,Jiang             
 Email       : coboy123456@gmail.com    
 Version     : 0.0 
 Copyright   : Your copyright notice    
 Description :  
 ============================================================================
 */

#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<map> 
#include<set>
#include<deque>
#include<list>
#include<algorithm>
#include<cmath>
#include<cstdlib>
#include "fattree.h"
#include "packet.h"

using namespace std; 
using fattree::Engine;
using fattree::Packet;

int main()
{
    srand(time(NULL));
    Engine e(4);    
    const int packets = 100000;
    for(int i = 0; i < packets; i ++){
        Packet p = e.generate_rand_packet();
        e.send_packet(p);
        cout << endl;
    }

    cout << "Aggr switch hit and miss " << endl;
    vector<int> hits = e.get_aggr_hit_cnt();
    vector<int> miss = e.get_aggr_miss_cnt(); 
    for(size_t i = 0; i < hits.size(); i++){
        if(hits[i] >= 0){
            cout << "switch " << i << " is cached and the hit " << hits[i] << " and miss " << miss[i] << endl;
            cout << "hit rate " << hits[i]*1.0/(hits[i]+miss[i])*100 << "%" << endl;    
        }
    }

    cout << endl << endl;
    cout << "edge switch hit and miss " << endl;
    hits = e.get_edge_hit_cnt();
    miss = e.get_edge_miss_cnt(); 
    for(size_t i = 0; i < hits.size(); i++){
        if(hits[i] >= 0){
            cout << "switch " << i << " is cached and the hit " << hits[i] << " and miss " << miss[i] << endl;
            cout << "hit rate " << hits[i]*1.0/(hits[i]+miss[i])*100 << "%" << endl;    
        }
    }

    cout << endl << endl;
    cout << "core switch hit and miss " << endl; 
    hits = e.get_core_hit_cnt();
    miss = e.get_core_miss_cnt();
    for(size_t i = 0; i < hits.size(); i++){
        if(hits[i] >= 0){
            cout << "switch " << i << " is cached and the hit " << hits[i] << " and miss " << miss[i] << endl;
            cout << "hit rate " << hits[i]*1.0/(hits[i]+miss[i])*100 << "%" << endl;    
        }
    }
}


