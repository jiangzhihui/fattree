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
#include "../zipf.h"

using namespace std; 
using namespace fattree;

int main()
{
    Zipf zip(0.5,10);
    for(int i = 0; i < 200; i ++)
        cout << zip.next() << endl;
}

