#include <iostream>
#include "../utility.h"

using namespace std; 

void test_get_rand(){
    int low = 1; 
    int high = 3; 
    for(int i = 0; i < 100; i ++)
        cout << fattree::get_rand(low,high) << endl;
}

void test_rand_ip(){
    int ports = 4; 
    for(int i = 0; i < 30; i ++)
        cout << fattree::rand_ip(ports) << endl;
    cout << endl;
}

int main(){
    test_rand_ip();
}

