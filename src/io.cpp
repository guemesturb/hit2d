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