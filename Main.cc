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
using fattree::Engine;

int main()
{
    Engine e(4);    
    /*
    e.print_cores();
    e.print_aggrs();
    e.print_hosts();
    e.print_edges();
    */
    e.print_edge_table();
}

