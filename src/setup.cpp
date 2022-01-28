#include "fluid.h"

vector<double> createWaveLength(int n, int l){

    vector<double> k1(n/2 + 1);
    vector<double> k2(n/2 - 1);

    for(int i=0; i<=n/2; ++i){
        k1[i] = i / l * 2 * PI;
    }

    int j = -n/2+1;
    for(int i=0; i<n/2; ++i){
        k2[i] = j / l * 2 * PI;
        ++j;
    }

    k1.insert(k1.end(), k2.begin(), k2.end());

    return k1;
}


