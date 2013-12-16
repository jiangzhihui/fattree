#ifndef _FATTREE_DEBUG_H
#define _FATTREE_DEBUG_H

#include <string>

namespace fattree{

#define DEFAULT "\033[0m" 
#define BLACK   "\033[30m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[33m"

using std::string;

class Debug{
public:

    static void info(string s);
    static void error(string s);
    static void warning(string s);
};

}//fattree

#endif 
