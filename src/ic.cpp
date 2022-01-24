#include "fluid.h"

vector<vector<double>> initialConditions(){

    // vector<vector<double>> omghat(3 , vector<double> (3, 0));

    vector<vector<double>> omghat = taylorVortex(LX/2, LY/2, LX/8, 1);
    // vector<vector<double>> omghat = taylorVortex(2, 2, 8, 1);

    return omghat;
}

vector<vector<double>> taylorVortex(int x0, int y0, int a0, int Umax){

    vector<vector<double>> omg(3 , vector<double> (3, 0));
    vector<vector<double>> omghat(3 , vector<double> (3, 0));
    vector<vector<double>> r2(3 , vector<double> (3, 1));

    for (int i=0; i<=1; i++) {
        for (int j=0; j<=1; j++) {
            omg = sumMatrices(omg, r2);
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