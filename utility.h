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

using std::string;

std::vector<int> split_ip(string ip);

string connect_ip(const string  s1, const string s2 , const string  s3, const string  s4);

//convert an int to a string 
string itoa(int i);

//get a random int in the range [low,high)
int get_rand(int low , int high);

/*
get a random host ip address 
ports is the number of port of the switches
*/
string rand_ip(int ports);

class Packet;
unsigned int generate_pkt_key(const Packet & pkt);

}//fattree


#endif 
