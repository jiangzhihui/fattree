#ifndef _FATTREE_PACKET_H
#define _FATTREE_PACKET_H

#include <cstring>
#include <string>

namespace fattree{
 
const int MAX_LENGTH=1;

struct  Packet{   
    Packet(){
        std::memset(data,0,sizeof(data));   
    }
    std::string src; 
    std::string dest;
    unsigned int data[MAX_LENGTH];
};

}//fattree

#endif 
