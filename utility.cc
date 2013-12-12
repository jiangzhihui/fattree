#include <sstream> 
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include "utility.h"

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

}//fattree
