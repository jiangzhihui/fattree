/*                                                                              
 ============================================================================
 Name        : 
 Author      : Zhihui,Jiang             
 Email       : coboy123456@gmail.com    
 Version     : 0.0 
 Copyright   : Your copyright notice    
 Description :  
 ============================================================================
 */

#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<map> 
#include<set>
#include<deque>
#include<list>
#include<algorithm>
#include<cmath>
#include "fattree.h"
#include "packet.h"

using namespace std; 
using fattree::Engine;
using fattree::Packet;

int main()
{
    Engine e(4);    
    /*
    e.print_cores();
    e.print_aggrs();
    e.print_hosts();
    e.print_edges();
    */
    for(int i = 0; i < 10; i ++){
        Packet p = e.generate_rand_packet();
        e.send_packet(p);
    }
}


