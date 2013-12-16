#include <iostream>
#include "debug.h"

namespace fattree{
    
    using namespace std; 
    void Debug::info(string s){
        cout << GREEN << s << DEFAULT << endl;    
    }

    void Debug::warning(string s){
        cout << YELLOW << s << DEFAULT << endl;
    }

    void Debug::error(string s){
        cout << RED << s << DEFAULT << endl;
    }

}//fattree

