#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fftw3.h>
#include <complex> 

using namespace std;

#define PI 3.14159265f



struct grid_t{
  vector<vector<double>> XX;
  vector<vector<double>> YY;
};

struct complex_t{
  vector<vector<double>> real;
  vector<vector<double>> imag;
};

extern int NX;
extern int NY;
extern int LX;
extern int LY;
extern int IC;
extern grid_t grid;

vector<double> createWaveLength(int, int);
vector<double> linspace(int, int, int);
vector<vector<complex<double>>> initialConditions();
vector<vector<complex<double>>> taylorVortex(float, float, float, float);
vector<vector<double>> sumMatrices(vector<vector<double>>, vector<vector<double>>);
vector<vector<complex<double>>> sumComplexMatrices(vector<vector<complex<double>>>, vector<vector<complex<double>>>);
grid_t meshGrid(vector<double>, vector<double>);
vector<vector<complex<double>>> applyFFT2(vector<vector<double>>);
vector<vector<double>> applyIFFT2(vector<vector<complex<double>>>);