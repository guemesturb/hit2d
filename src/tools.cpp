#include "fluid.h"

vector<vector<double>> sumMatrices(vector<vector<double>> A, vector<vector<double>> B){

    vector<vector<double>> C(A.size() , vector<double> (A[0].size(), 0));

    for(size_t i = 0; i < A.size(); i++){
        for(size_t j = 0; j < A[0].size(); j++){
            C[i][j] = A[i][j] + B[i][j];
        }
    }

    return C;
}