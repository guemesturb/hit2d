#include "fluid.h"

vector<vector<double>> initialConditions(){

    // Case 1
    // vector<vector<double>> omghat = taylorVortex(float(LX)/2.0, float(LY)/2.0, float(LX)/8.0, 1.0);
    // Case 2
    // vector<vector<double>> omghat1 = taylorVortex(float(LX)/2.0, float(LY)*0.4, float(LX)/10.0, 1.0);
    // vector<vector<double>> omghat2 = taylorVortex(float(LX)/2.0, float(LY)*0.6, float(LX)/10.0, 1.0);
    // vector<vector<double>> omghat = sumMatrices(omghat1, omghat2);
    // Case 3
    int nv = 100;
    srand((unsigned int)time(NULL));
    vector<vector<double>> omghat = taylorVortex(float(LX) * float(rand()) / float(RAND_MAX), float(LY) * float(rand()) / float(RAND_MAX), float(LX)/20.0, float(rand()) / float(RAND_MAX) * 2.0 - 1.0);
    for (int i=0; i<nv; i++){
        omghat = sumMatrices(omghat, taylorVortex(float(LX) * float(rand()) / float(RAND_MAX), float(LY) * float(rand()) / float(RAND_MAX), float(LX)/20.0, float(rand()) / float(RAND_MAX) * 2.0 - 1.0));
    }
    return omghat;
}

vector<vector<double>> taylorVortex(float x0, float y0, float a0, float Umax){

    vector<vector<double>> omg(NY, vector<double> (NX, 0));
    vector<vector<double>> omghat(NY , vector<double> (NX, 0));
    vector<vector<double>> r2(NY , vector<double> (NX, 0));

    for (int i=-1; i<=1; i++) {
        for (int j=-1; j<=1; j++) {
            for (int ig=0; ig<NY; ig++) {
                for (int jg=0; jg<NX; jg++) {
                    r2[ig][jg] = pow(grid.XX[ig][jg] - x0 - double(i)*double(LX), 2.0) + pow(grid.YY[ig][jg] - y0 - double(j)*double(LY), 2.0);
                    omg[ig][jg] = omg[ig][jg] + Umax/a0*(2.0-r2[ig][jg]/pow(a0,2.0))*exp(0.5*(1.0-r2[ig][jg]/pow(a0,2.0)));
                }
            }
        }
    }
    
    omghat = omg;

    return omghat;
}

// omg = zeros(size(xx));
// for i = -1:1
//     for j = -1:1 % making sure to add periodic images
//         r2  = (xx-x0-i*Lx).^2 + (yy-y0-j*Ly).^2;
//         omg = omg + Umax/a0*(2-r2/a0^2).*exp(0.5*(1-r2/a0^2));
//     end
// end
// omghat = fft2(omg);