#ifndef _FATTREE_PACKET_H
#define _FATTREE_PACKET_H

#include <cstring>
#include <string>

namespace fattree{
 
const int MAX_LENGTH=64;

struct  Packet{   
    Packet(){
        std::memset(data,0,sizeof(data));   
    }
    std::string src; 
    std::string dest;
    unsigned char data[MAX_LENGTH];
};

}//fattree

#endif 
