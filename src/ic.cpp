#include "fluid.h"

vector<vector<complex<double>>> initialConditions(){

    vector<vector<complex<double>>> omghat;

    if (IC == 1){
        omghat = taylorVortex(double(LX)/2.0, double(LY)/2.0, double(LX)/8.0, 1.0);
    } 
    else if (IC == 2){
         omghat = sumComplexMatrices(taylorVortex(double(LX)/2.0, double(LY)*0.4, double(LX)/10.0, 1.0), taylorVortex(double(LX)/2.0, double(LY)*0.6, double(LX)/10.0, 1.0));
    }
    else if (IC == 3){
        int nv = 100;
        srand((unsigned int)time(NULL));
        omghat = taylorVortex(double(LX) * double(rand()) / double(RAND_MAX), double(LY) * double(rand()) / double(RAND_MAX), double(LX)/20.0, double(rand()) / double(RAND_MAX) * 2.0 - 1.0);
        for (int i=0; i<nv; i++){
            omghat = sumComplexMatrices(omghat, taylorVortex(double(LX) * double(rand()) / double(RAND_MAX), double(LY) * double(rand()) / double(RAND_MAX), double(LX)/20.0, double(rand()) / double(RAND_MAX) * 2.0 - 1.0));
        }
    }

    return omghat;
}


vector<vector<complex<double>>> taylorVortex(double x0, double y0, double a0, double Umax){

    vector<vector<double>> omg(NY, vector<double> (NX, 0));
    vector<vector<complex<double>>> omghat(NY , vector<complex<double>> (NX, 0));
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
    
    omghat = applyFFT2(omg);

    return omghat;
}