#ifndef _FATTREE_UTILITY_H
#define _FATTREE_UTILITY_H

/*
define some utility functions and types
*/

#include <map> 
#include <string>
#include <vector>

namespace fattree{

//a map from ip to output port of a switch
typedef std::map<std::string,int> IpPortTable;

std::vector<int> split_ip(std::string ip);

//convert an int to a string 
std::string itoa(int i);

}//fattree

#endif 
