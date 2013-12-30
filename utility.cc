#include <sstream> 
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include "utility.h"
#include "packet.h"

using namespace std; 

namespace fattree{

vector<int> split_ip(string ip){
    //cout << ip << endl;
    vector<int> re; 
    stringstream ss(ip);
    string temp; 
    char delim = '.';
    while(getline(ss,temp,delim)){
        int i = atoi(temp.c_str());
        //cout << i << endl;
        re.push_back(i);
    }
    return re;  
}

string itoa(int i){
    if(i == 0)
        return "0";
    string re = ""; 
    while(i > 0){
        re.push_back(i%10 + '0');
        i = i / 10; 
    }
    reverse(re.begin(),re.end());
    return re;
}

string connect_ip(const string s1 , const string s2, const string s3 , const string s4){
    string re = s1 + "." + s2 + "." + s3 + "." + s4;
    return re;
}

int get_rand(int low , int high){
    int delta = high - low; 
    int r = rand() % delta;
    return low + r;
}

string rand_ip(int ports){
    int pod = get_rand(0,ports);        
    int swi = get_rand(0,ports/2);
    int h   = get_rand(2,ports/2+2);

    return connect_ip("10",itoa(pod),itoa(swi),itoa(h));
}

unsigned int generate_pkt_key(const Packet & pkt){
    return pkt.data[0];    
}

}//fattree
