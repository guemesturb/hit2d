#include "fluid.h"


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

vector<vector<double>> sumMatrices(vector<vector<double>> A, vector<vector<double>> B){

    vector<vector<double>> C(A.size() , vector<double> (A[0].size(), 0));

    for(size_t i = 0; i < A.size(); i++){
        for(size_t j = 0; j < A[0].size(); j++){
            C[i][j] = A[i][j] + B[i][j];
        }
    }

    return C;
}

grid_t meshGrid(vector<double> X, vector<double> Y){

    vector<vector<double>> XX(Y.size() , vector<double> (Y.size(), 0));
    vector<vector<double>> YY(Y.size() , vector<double> (Y.size(), 0));

    for(size_t j = 0; j < Y.size(); j++){
        XX[j] = X;
        for(size_t i = 0; i < X.size(); i++){
            YY[j][i] = Y[j];
        }
    }

    grid_t tmp_grid;

    tmp_grid.XX = XX;
    tmp_grid.YY = YY;

    return tmp_grid;
}