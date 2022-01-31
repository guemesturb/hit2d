#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <complex> 
#include <fftw3.h>

using namespace std;

#define PI 3.14159265f

// Define structures

struct grid_t{
  vector<vector<double>> XX;
  vector<vector<double>> YY;
};

struct velocity_t{
  vector<vector<complex<double>>> u;
  vector<vector<complex<double>>> v;
};

// Define variables 

extern int NX;
extern int NY;
extern int NXP;
extern int NYP;
extern int LX;
extern int LY;
extern int IC;
extern bool PD;
extern grid_t grid;
extern vector<double> kx; 
extern vector<double> ky; 
extern vector<double> kxp;
extern vector<double> kyp;
extern double nu;

// Functions fft.cpp
vector<vector<complex<double>>> applyFFT2(vector<vector<double>>);
vector<vector<complex<double>>> applyIFFT2(vector<vector<complex<double>>>);
vector<vector<complex<double>>> applyFFT2Complex(vector<vector<complex<double>>>);

// Functions ic.cpp
vector<vector<complex<double>>> initialConditions();
vector<vector<complex<double>>> taylorVortex(double, double, double, double);

// Functions io.cpp
void saveData(vector<vector<complex<double>>>, double);

// Functions nonLinear.cpp
void rk4(vector<vector<complex<double>>>*, double);
vector<vector<complex<double>>> rhs(vector<vector<complex<double>>>);
vector<vector<complex<double>>> advection(vector<vector<complex<double>>>);
vector<vector<complex<double>>> pad(vector<vector<complex<double>>>);
vector<vector<complex<double>>> chop(vector<vector<complex<double>>>);

// Functions setup.cpp
vector<double> createWaveLength(int, int);

// Functions tools.cpp
vector<double> linspace(int, int, int);
grid_t meshGrid(vector<double>, vector<double>);
vector<vector<double>> sumMatrices(vector<vector<double>>, vector<vector<double>>);
vector<vector<complex<double>>> sumComplexMatrices(vector<vector<complex<double>>>, vector<vector<complex<double>>>);
velocity_t omega2velocity(vector<vector<complex<double>>>);
void computeReynolds(vector<vector<complex<double>>>);


