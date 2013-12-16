#include <iostream>
#include "../fattree.h"

using namespace std; 

void test_generate_rand_packet(){
    using fattree::Engine; 
    using fattree::Packet;
    Engine e(4);
    for(int i = 0;i < 100; i ++){
        Packet pkt = e.generate_rand_packet();    
        cout << pkt.src << "->" << pkt.dest << ":" << endl; 
        for(int i = 0; i < fattree::MAX_LENGTH; i++)
            cout << (int)pkt.data[i] <<" "; 
        cout << endl << endl;
    }
}

int main()
{
    test_generate_rand_packet();
}

