#include "fluid.h"


int main(int argc, char **argv) {
    
    // Domain size
    
    int LX = 1; // Simulation-box size in the X direction
    int LY = 1; // Simulation-box size in the Y direction
    int NX = 128; // Number of grid points in the X direction
    int NY = 128; // Number of grid points in the Y direction
    float dx = float(LX) / float(NX);
    float dy = float(LY) / float(NY);

    // Dealiasing

    int NXP = NX * 3 / 2;
    int NYP = NY * 3 / 2;

    // Viscosity

    float nu = 0.0005;

    // Time step setup

    float dt = 1.0/ float(NX) / 4.0; 
    float tmax = 0.5;
    float tout = 0.1;
    float nt = ceil(tmax/dt);
    int nout = ceil(tout/dt);

    // Fourier wavelengths

    vector<double> kx = createWaveLength(NX, LX);
    vector<double> ky = createWaveLength(NY, LY);
    vector<double> kxp = createWaveLength(NXP, LX);
    vector<double> kyp = createWaveLength(NYP, LY);

    // Grid generation

    vector<double> x = linspace(0, LX, NX + 1);
    vector<double> y = linspace(0, LY, NY + 1);

    // Initial conditions

    vector<vector<double>> omghat = initialConditions();

    // for (size_t i = 0; i < omghat.size(); i++) {
    //     for (size_t j = 0; j < omghat[0].size(); j++) {
    //         cout << "[i]=" << i << " ";
    //         cout << "[j]=" << j << "\n";
    //         cout << omghat[i][j] << "\n";
    //     }
    // }

    cout << "Simulation is finished\n";
    
    return 0;
}

