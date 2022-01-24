#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

#define PI 3.14159265f

extern int LX;
extern int LY;

vector<double> createWaveLength(int, int);
vector<double> linspace(int, int, int);
vector<vector<double>> initialConditions();
vector<vector<double>> taylorVortex(int, int, int, int);
vector<vector<double>> sumMatrices(vector<vector<double>>, vector<vector<double>>);