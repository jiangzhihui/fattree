#include <cmath>
#include <cstdlib>
#include <iostream>
#include "zipf.h"

using namespace fattree; 
using namespace std;

Zipf::Zipf(double alpha, double N):alpha(alpha),N(N){
    norm_const = 0;
    for(int i = 1; i <= N; i++){
        double p = pow((double)i,alpha);
        norm_const += (1.0/p);       
    }
    norm_const = 1.0 / norm_const;
}

int Zipf::next(){
    double rnd;  
    do{
        rnd = rand();
        rnd = rnd / RAND_MAX;
    }while(rnd == 0 || rnd == 1);
    
    //cout << "rand " << rnd << endl; 
    double prob_sum = 0; // the probability sum 
    for(int i = 1; i <= N; i ++){
        prob_sum += norm_const / pow((double)i,alpha);
        //cout << prob_sum << endl;
        if(prob_sum >= rnd)
            return i;
    }

    return 1;
}

int main(){
    cout << "test pr" << endl;
}
