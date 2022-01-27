#include "fluid.h"


int LX; // Simulation-box size in the X direction
int LY; // Simulation-box size in the Y direction
int NX;
int NY;
int IC;
grid_t grid;

int main(int argc, char **argv) {
    
    // Domain size
    
    LX = 1; // Simulation-box size in the X direction
    LY = 2; // Simulation-box size in the Y direction
    NX = 128; // Number of grid points in the X direction
    NY = 128; // Number of grid points in the Y direction
    float dx = float(LX) / float(NX);
    float dy = float(LY) / float(NY);

    // Initial conditions

    IC = 3;

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

    grid = meshGrid(vector<double>(x.begin(), x.end() - 1), vector<double>(y.begin(), y.end() - 1));

    vector<vector<complex<double>>> omegaHat = initialConditions();


    // for (size_t i = 0; i < grid.XX.size(); i++) {
    //     for (size_t j = 0; j < grid.XX[0].size(); j++) {
    //         cout << "[i]=" << i << " ";
    //         cout << "[j]=" << j << "\n";
    //         cout << grid.XX[i][j] << "\n";
    //         cout << grid.YY[i][j] << "\n";
    //     }
    // }

    ofstream output_file("test.txt");
    for (size_t i = 0; i < omegaHat.size(); i++)
    {
        for (size_t j = 0; j < omegaHat[0].size(); j++) {
            // output_file << omegaHat[i][j].real() << endl; 
            output_file << omegaHat[i][j].real() << "+" << omegaHat[i][j].imag() << "j\n";
        }
    }
    // ostream_iterator<int> output_iterator(output_file, "\n");
    // copy( omegaHat.begin( ), omegaHat.end( ), output_iterator );

    // for (size_t i = 0; i < omegaHat.size(); i++) {
    //     for (size_t j = 0; j < omegaHat[0].size(); j++) {
    //         cout << "[i]=" << i << " ";
    //         cout << "[j]=" << j << "\n";
    //         cout << omegaHat[i][j].real() << "\n";
    //     }
    // }

    cout << "Simulation is finished\n";
    
    return 0;
}

