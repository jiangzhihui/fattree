#ifndef _FATTREE_CACHE_H
#define _FATTREE_CACHE_H

#include <map>
#include <list>
#include "packet.h"

namespace fattree{

typedef int Key;
typedef std::pair<Key,Packet> KVPair;

class Cache{

public:
    
    Cache(size_t max_size = 0):_max_size(max_size),_size(0){}
    /*
    get a value from the cache with the key 
    if the key exists return true else return false
    */
    bool get(Key key, Packet & value);

    /*
    put a cache entry into the cache with (key,value) pair
    */
    void put(Key key, const Packet & value);

    /*
    return current cache size
    */
    size_t size(){
        return _size;
    }

private:
    size_t _max_size; 
    size_t _size;
    std::map<Key,Packet> mp; 
    std::list<KVPair> cache;
    
};

}//fattree

#endif 
