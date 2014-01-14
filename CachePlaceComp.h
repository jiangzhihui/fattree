#ifndef _LASTHOP_FATTREE_H 
#define _LASTHOP_FATTREE_H 

#include <vector>
#include "Switch.h"
#include "fattree.h"
#include "packet.h"

namespace fattree{

/*
A class for the comparison of different cache placement strategies
*/
class CachePlaceComp{
public:
    void last_hop();

private:
    std::vector<Switch*> get_switches(Packet& p,Engine & e); 
};

}

#endif
