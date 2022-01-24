#include "fluid.h"

vector<double> createWaveLength(int n, int l){

    vector<double> k1(n/2 + 1);
    vector<double> k2(n/2);

    for(int i=0; i<=n/2; ++i){
        k1[i] = i / l * 2 * PI;
    }

    int j = -n/2;
    for(int i=0; i<n/2; ++i){
        k2[i] = j / l * 2 * PI;
        ++j;
    }

    k1.insert(k1.end(), k2.begin(), k2.end());

    return k1;
}

vector<double> linspace(int start_in, int end_in, int num_in)
{

    vector<double> linspaced;

    double start = static_cast<double>(start_in);
    double end = static_cast<double>(end_in);
    double num = static_cast<double>(num_in);

    if (num == 0) { return linspaced; }
    if (num == 1) 
        {
        linspaced.push_back(start);
        return linspaced;
        }

    double delta = (end - start) / (num - 1);

    for(int i=0; i < num-1; ++i)
        {
        linspaced.push_back(start + delta * i);
        }
    linspaced.push_back(end); 

    return linspaced;
}
