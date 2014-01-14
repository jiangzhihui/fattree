#include <iostream>
#include "host.h"
#include "EdgeSwitch.h"
#include "packet.h"
#include "debug.h"
#include "Switch.h"

namespace fattree{

void Host::send_packet(const Packet& pkt){
    Debug::info("Host " + get_ip() + " sends a packet to " + swit->get_ip());
    swit->send_packet(pkt); 
}

void Host::recv_packet(const Packet& pkt){
    Debug::info("Host " + get_ip() + " recvs a packet from " + pkt.src);
}

Switch* Host::next_hop(Packet& pkt){
    return swit;
}

}//fattree
