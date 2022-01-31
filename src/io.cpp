#include "fluid.h"

void saveData(vector<vector<complex<double>>> omegaHat, double timeSimulation){

    vector<vector<complex<double>>> omega = applyIFFT2(omegaHat);
    velocity_t velocity = omega2velocity(omegaHat);
    char buffer[100];

    sprintf(buffer, "outs/omegaHat_%1.4f", timeSimulation);
    
    ofstream output_file(buffer);
    for (size_t i = 0; i < omegaHat.size(); i++) {
        for (size_t j = 0; j < omegaHat[0].size(); j++) {
            output_file << omegaHat[i][j].real() << "+" << omegaHat[i][j].imag() << "j\n";
        }
    }

    output_file.close();
    output_file.clear();

    sprintf(buffer, "outs/omega_%1.4f", timeSimulation);
    output_file.open(buffer);
    for (size_t i = 0; i < omega.size(); i++) {
        for (size_t j = 0; j < omega[0].size(); j++) {
            output_file << omega[i][j].real() << "\n";
        }
    }
}

void computeReynolds(vector<vector<complex<double>>> omegaHat){
    
    vector<vector<complex<double>>> omega = applyIFFT2(omegaHat);

    // Compute Reynolds

    velocity_t velocity = omega2velocity(omegaHat);

    // complex<double> ustar;

    double ustar;
    double lstar;
    double u2;
    double w2;

    for (int i=0; i<NX; i++) {
        for (int j=0; j<NY; j++) {
            ustar += pow(velocity.u[j][i].real(), 2.0) + pow(velocity.v[j][i].real(), 2.0);
        }
    }

    ustar = pow(ustar / NX / NY, 0.5);

    for (int i=0; i<NX; i++) {
        for (int j=0; j<NY; j++) {
            u2 += pow(velocity.u[j][i].real(), 2.0) + pow(velocity.v[j][i].real(), 2.0);
            w2 += pow(omega[j][i].real(), 2.0);
        }
    }

    u2 = u2 / NX / NY;
    w2 = w2 / NX / NY;

    lstar = pow(u2/w2, 0.5);

    double Re = ustar * lstar / nu;
}