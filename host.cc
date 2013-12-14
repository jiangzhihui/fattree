#include "host.h"

namespace fattree{

void Host::send_packet(Packet& pkt){
    swit.send_packet(pkt); 
}

}//fattree
