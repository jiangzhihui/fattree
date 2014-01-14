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
#include<iomanip>
#include<fstream>
#include<string>
#include<vector>
#include<map> 
#include<set>
#include<deque>
#include<iterator>
#include<list>
#include<algorithm>
#include<numeric>
#include<cmath>
#include<cstdlib>
#include "fattree.h"
#include "packet.h"
#include "CachePlaceComp.h"

using namespace std; 
using namespace fattree;

/*
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
*/

void print_bar(int n,char c,ostream&out){
    while(n-- > 0)
        out << c ; 
    out << endl;
}

void write_result(vector<string> & ips , vector<int>& hits , vector<int> & miss,ofstream & out,vector<pair<int,int> > & hit_pair, vector<pair<int,int> > & miss_pair){
    int width = 10; 
    int w = width * 8 + 8; 
    print_bar(w,'-',out);
    out << setw(width) << right << "ip" << "|" << setw(width) << "hits" << "|" << setw(width) << "miss" << "|" << setw(width) << "hit ratio";
    out << "|" << setw(width) << "up hits" << "|" << setw(width) << "downhits" << "|" ;
    out << setw(width) << "up miss" << "|" << setw(width) << "downmiss" << "|" << endl;
    print_bar(w,'-',out);
    for(size_t i = 0;i < hits.size(); i ++){
        if(hits[i] >= 0){
            out << setw(width) <<  ips[i] << "|"; 
            out << setw(width) <<  hits[i] << "|" << setw(width) << miss[i] <<"|" << setw(width) << hits[i]*1.0/(hits[i]+miss[i])*100 << "%|" ;
            out << setw(width) << hit_pair[i].first << "|" << setw(width) << hit_pair[i].second << "|"; 
            out << setw(width) << miss_pair[i].first << "|" << setw(width) << miss_pair[i].second << "|"; 
            out << endl;
        }
    }
        print_bar(w,'-',out);
}

void write_core_result(vector<string> & ips , vector<int>& hits , vector<int> & miss,ofstream & out){
    int width = 8; 
    int w = width * 4 + 4; 
    print_bar(w,'-',out);
    out << setw(width) << right << "ip" << "|" << setw(width) << "hits" << "|" << setw(width) << "miss" << "|" << setw(width) << "hit ratio" << endl;
    print_bar(w,'-',out);
    for(size_t i = 0;i < hits.size(); i ++){
        if(hits[i] >= 0){
            out << setw(8) <<  ips[i] << "|"; 
            out << setw(width) <<  hits[i] << "|" << setw(width) << miss[i] <<"|" << setw(width) << hits[i]*1.0/(hits[i]+miss[i])*100 << "%" << endl;
        }
    }
        print_bar(w,'-',out);
}

void test_edge(Engine&e){
    vector<pair<int,int> > hit1 = e.get_edge_hit_cnt_pair();
    vector<int>            hit2 = e.get_edge_hit_cnt(); 
    for(size_t i = 0; i < hit1.size(); i++){
        cout << "up " << hit1[i].first << " down " << hit1[i].second << " total " << hit2[i] << endl;
    }
}

void test_each_hop(){
    string config_files [] = {"config1","config2","config3","config4"};
    ofstream out("result",ios::out|ios::app);
    for(int ports = 4; ports <= 8; ports += 4){
        for(int i = 0; i < 3; i ++){
            Config cfg = read_config(config_files[i]);
            for(int packets = 10000; packets <= 100000; packets *= 10){
                Engine e(ports,cfg);    
                vector<string> edgeip = e.get_edge_ips();
                vector<string> aggrip = e.get_aggr_ips(); 
                vector<string> coreip = e.get_core_ips();
                for(int i = 0; i < packets; i ++){
                    Packet p = e.generate_rand_packet();
                    e.send_packet(p);
                }

                out << "config options: ports=" << ports << " packets=" << packets << " edge_cache_size=" << cfg.max_edge_cache << " aggr_cache_size=" << cfg.max_aggr_cache << " core_cache_size=" << cfg.max_core_cache<< endl;
                out << "Edge statistics: " << endl;
                vector<int> hits = e.get_edge_hit_cnt();
                vector<int> miss = e.get_edge_miss_cnt(); 
                vector<pair<int,int> > hits_pair = e.get_edge_hit_cnt_pair();
                vector<pair<int,int> > miss_pair = e.get_edge_miss_cnt_pair();
                write_result(edgeip,hits,miss,out,hits_pair,miss_pair);
                int sum = 0; 
                sum = accumulate(hits.begin(),hits.end(),0);
                sum = accumulate(miss.begin(),miss.end(),0);
                cout <<"edge " <<  sum  << " " << packets<< endl; 
                
                out << endl;
                out << "Aggr statistics:" << endl;
                hits = e.get_aggr_hit_cnt();
                miss = e.get_aggr_miss_cnt(); 
                hits_pair = e.get_aggr_hit_cnt_pair();
                miss_pair = e.get_aggr_miss_cnt_pair();
                write_result(aggrip,hits,miss,out,hits_pair,miss_pair);
                sum = 0; 
                sum = accumulate(hits.begin(),hits.end(),sum);
                sum = accumulate(miss.begin(),miss.end(),sum);
                //cout <<"Aggr " <<  sum  << " " << packets<< endl; 
                
                out << endl;
                out << "Core statistics:" << endl;
                hits = e.get_core_hit_cnt();
                miss = e.get_core_miss_cnt();
                write_core_result(coreip,hits,miss,out);
                sum = 0; 
                sum = accumulate(hits.begin(),hits.end(),sum);
                sum = accumulate(miss.begin(),miss.end(),sum);
                //cout <<"Core " <<  sum  << " " << packets<< endl; 
                out << endl;

                vector<char> sharps(100,'#');
                copy(sharps.begin(),sharps.end(),ostream_iterator<char>(out,"")); 
                out << endl;
            }
        }
    }
    out.close();

}

int main()
{
    srand(time(NULL));
    CachePlaceComp cpc;
    cpc.last_hop();
}


