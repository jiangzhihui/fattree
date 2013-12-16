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
using namespace std; 

struct Host;
struct Switch{
    Host * host;
    Switch(){}
    void set_host(Host*h);
    void recv();
};

void Switch::set_host(Host*h){
    host = h;
}

void Switch::recv(){
    cout << "I am s switch and i receive a packet from host " << endl;
}

struct Host{
    Switch * swi ; 
    Host(){}
    void set_switch(Switch*s);
    void send();
};

void Host::send(){
    cout << "I am a host and i send a packet to the switch i'm connected" << endl;
    swi->recv();    
}

void Host::set_switch(Switch * s){
    swi = s;
}

#define GREEN "\033[32m" 
#define DEFAULT "\033[0m"

int main()
{
    /*
    Switch s; 
    Host h;
    h.set_switch(&s);
    s.set_host(&h);
    h.send();
    cout << fattree::vi.size() << endl;
    */
    
    cout << GREEN << " hello word" << DEFAULT << endl; 
}

