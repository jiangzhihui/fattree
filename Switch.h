#ifndef _FATTREE_SWITCH_H
#define _FATTREE_SWITCH_H

#include<string>

namespace fattree{

class Packet;
class Cache;

class Switch{
public:
    virtual Switch* next_hop(Packet*) = 0;
    virtual Cache* get_cache()=0;
    virtual std::string get_ip() const =0;
};

};//fattree 
#endif
