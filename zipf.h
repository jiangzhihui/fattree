#ifndef _FATTREE_ZIPF_H
#define _FATTREE_ZIPF_H

namespace fattree{

class Zipf{

public:
    Zipf(double alpha = 0.5, double N = 65535);
    int next(); 

private:
    double alpha; 
    int N;  
    double norm_const;
};

}//fattree
#endif 
