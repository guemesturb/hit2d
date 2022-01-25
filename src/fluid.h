#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#define PI 3.14159265f

struct grid_t{
  vector<vector<double>> XX;
  vector<vector<double>> YY;
};

extern int NX;
extern int NY;
extern int LX;
extern int LY;
extern grid_t grid;

vector<double> createWaveLength(int, int);
vector<double> linspace(int, int, int);
vector<vector<double>> initialConditions();
vector<vector<double>> taylorVortex(float, float, float, float);
vector<vector<double>> sumMatrices(vector<vector<double>>, vector<vector<double>>);
grid_t meshGrid(vector<double>, vector<double>);