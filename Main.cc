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
using namespace fattree;

Config read_config(string file_name){
    ifstream in(file_name.c_str());
    Config re; 

    if(in.good()){
        in >> re.max_edge_cache; 
        in >> re.max_aggr_cache; 
        in >> re.max_core_cache;
    }

    return re;
}

void write_result(vector<int>& hits , vector<int> & miss,ofstream & out){
    for(int i = 0;i < hits.size(); i ++){
        if(hits[i] >= 0){
            out << hits[i] << ":" << miss[i] <<":" << hits[i]*1.0/(hits[i]+miss[i])*100 << "%" << endl;
        }
    }
}

int main()
{
    srand(time(NULL));
    string config_files [] = {"config1","config2","config3","config4"};
    ofstream out("result1",ios::out|ios::app);
    for(int ports = 4; ports <= 12; ports += 4){
        for(int i = 0; i < 3; i ++){
            Config cfg = read_config(config_files[i]);
            Engine e(ports,cfg);    
            for(int packets = 1000; packets <= 100000; packets *= 10){
                for(int i = 0; i < packets; i ++){
                    Packet p = e.generate_rand_packet();
                    e.send_packet(p);
                    cout << i << endl;
    //                cout << endl;
                }

                out << "config options: ports=" << ports << " packets=" << packets << " edge_cache_size=" << cfg.max_edge_cache << " aggr_cache_size=" << cfg.max_aggr_cache << " core_cache_size=" << cfg.max_core_cache<< endl;
                out << "Edge statics: " << endl;
                vector<int> hits = e.get_edge_hit_cnt();
                vector<int> miss = e.get_edge_miss_cnt(); 
                write_result(hits,miss,out);

                /*
                cout << "edge switch hit and miss " << endl;
                for(size_t i = 0; i < hits.size(); i++){
                    if(hits[i] >= 0){
                        cout << "switch " << i << " is cached and the hit " << hits[i] << " and miss " << miss[i] << endl;
                        cout << "hit rate " << hits[i]*1.0/(hits[i]+miss[i])*100 << "%" << endl;    
                    }
                }
                */
                out << "Aggr statics:" << endl;
                hits = e.get_aggr_hit_cnt();
                miss = e.get_aggr_miss_cnt(); 
                write_result(hits,miss,out);
                /*
                cout << "Aggr switch hit and miss " << endl;
                for(size_t i = 0; i < hits.size(); i++){
                    if(hits[i] >= 0){
                        cout << "switch " << i << " is cached and the hit " << hits[i] << " and miss " << miss[i] << endl;
                        cout << "hit rate " << hits[i]*1.0/(hits[i]+miss[i])*100 << "%" << endl;    
                    }
                }
                */
                out << "Core statics:" << endl;
                hits = e.get_core_hit_cnt();
                miss = e.get_core_miss_cnt();
                write_result(hits,miss,out);
                /*
                cout << endl << endl;
                cout << "core switch hit and miss " << endl; 
                for(size_t i = 0; i < hits.size(); i++){
                    if(hits[i] >= 0){
                        cout << "switch " << i << " is cached and the hit " << hits[i] << " and miss " << miss[i] << endl;
                        cout << "hit rate " << hits[i]*1.0/(hits[i]+miss[i])*100 << "%" << endl;    
                    }
                }
                */
                out << endl;
            }
        }
    }
    out.close();
}


