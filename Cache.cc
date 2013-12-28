#include "Cache.h"

using namespace fattree; 
using namespace std; 

bool Cache::get(Key key, Packet & value){
    map<Key,Packet>::iterator pos = mp.find(key);
    if(pos != mp.end()){
        value = pos->second;    
        return true;
    }
    return false;
}

void Cache::put(Key key, const Packet & value){
    map<Key,Packet>::iterator pos = mp.find(key);
    if(pos != mp.end())
        return ;
    if(_size == _max_size){
        KVPair & p = cache.back();
        mp.erase(p.first);
        cache.pop_back();
        KVPair newp(key,value); 
        cache.push_front(newp);
        mp.insert(newp);
    }else{
        mp.insert(KVPair(key,value));
        cache.push_front(KVPair(key,value));
        _size++;
    }
}
