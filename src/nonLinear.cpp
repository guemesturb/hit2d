#include "fluid.h"

vector<vector<complex<double>>> rk4(vector<vector<complex<double>>> f, double dt) {

    vector<vector<complex<double>>>   k1(f.size() , vector<complex<double>> (f[0].size(), 0));
    vector<vector<complex<double>>>   k2(f.size() , vector<complex<double>> (f[0].size(), 0));
    vector<vector<complex<double>>>   k3(f.size() , vector<complex<double>> (f[0].size(), 0));
    vector<vector<complex<double>>>   k4(f.size() , vector<complex<double>> (f[0].size(), 0));
    vector<vector<complex<double>>> fnew(f.size() , vector<complex<double>> (f[0].size(), 0));
    
    k1 = rhs(f);
    for (int i=0; i<NX; i++){
        for (int j=0; j<NY; j++){
            k2[j][i] = f[j][i] + 0.5 * dt * k1[j][i];
        }
    }
    k2 = rhs(k2);
    for (int i=0; i<NX; i++){
        for (int j=0; j<NY; j++){
            k3[j][i] = f[j][i] + 0.5 * dt * k2[j][i];
        }
    }
    k3 = rhs(k3);
    for (int i=0; i<NX; i++){
        for (int j=0; j<NY; j++){
            k4[j][i] = f[j][i] + dt * k3[j][i];
        }
    }
    k4 = rhs(k4);
    for (int i=0; i<NX; i++){
        for (int j=0; j<NY; j++){
            fnew[j][i] = f[j][i] + dt / 6.0 * (k1[j][i] + 2.0 * (k2[j][i] + k3[j][i]) + k4[j][i]);
        }
    }

    return fnew;
}

vector<vector<complex<double>>> rhs(vector<vector<complex<double>>> omegaHat){

    vector<vector<complex<double>>> lin(omegaHat.size() , vector<complex<double>> (omegaHat[0].size(), 0));

    for (int i=0; i<NY; i++){
        for (int j=0; j<NX; j++){
            lin[i][j] = -nu*(pow(kx[j], 2) + pow(ky[i], 2))*omegaHat[i][j];
        }
    }

    vector<vector<complex<double>>> adv = advection(omegaHat);

    vector<vector<complex<double>>> rhs(omegaHat.size(), vector<complex<double>> (omegaHat[0].size(), 0));

    for (int i=0; i<NY; i++){
        for (int j=0; j<NX; j++){
            rhs[i][j] = lin[i][j] + adv[i][j];
        }
    }

    return rhs;
}

vector<vector<complex<double>>> advection(vector<vector<complex<double>>> omegaHat){

    vector<vector<complex<double>>> nonLinear(NYP, vector<complex<double>> (NXP, 0));
    vector<vector<complex<double>>> uHat(omegaHat.size(), vector<complex<double>> (omegaHat[0].size(), 0));
    vector<vector<complex<double>>> vHat(omegaHat.size(), vector<complex<double>> (omegaHat[0].size(), 0));
    vector<vector<complex<double>>> psiHat(omegaHat.size(), vector<complex<double>> (omegaHat[0].size(), 0));
    vector<vector<complex<double>>> domgdx(omegaHat.size(), vector<complex<double>> (omegaHat[0].size(), 0));
    vector<vector<complex<double>>> domgdy(omegaHat.size(), vector<complex<double>> (omegaHat[0].size(), 0));

    for (int i=0; i<NX; i++){
        for (int j=0; j<NY; j++){
            if (i*j==0){
                psiHat[j][i] = 0;
            }
            else {
                psiHat[j][i] = omegaHat[j][i]/(pow(kx[i],2)+pow(ky[j],2));
            }
        }
    }

    for (int i=0; i<NX; i++){
        for (int j=0; j<NY; j++){
            domgdx[j][i] = 1i*kx[i]*omegaHat[j][i];
            domgdy[j][i] = 1i*ky[j]*omegaHat[j][i];
        }
    }

    for (int i=0; i<NX; i++){
        for (int j=0; j<NY; j++){
            uHat[j][i] =  1i*kx[i]*psiHat[j][i];
            vHat[j][i] = -1i*ky[j]*psiHat[j][i];
        }
    }

    if (PD==true){

        vector<vector<complex<double>>> up = applyIFFT2(pad(uHat));
        vector<vector<complex<double>>> vp = applyIFFT2(pad(vHat));
        
        vector<vector<complex<double>>> domgdxp = applyIFFT2(pad(domgdx));
        vector<vector<complex<double>>> domgdyp = applyIFFT2(pad(domgdy));
        
        for (int i=0; i<NXP; i++){
            for (int j=0; j<NYP; j++){
                nonLinear[j][i] = -up[j][i]*domgdxp[j][i] - vp[j][i]*domgdyp[j][i];
            }
        }
        
        nonLinear  = chop(applyFFT2Complex(nonLinear));

        for (int i=0; i<NX; i++){
            for (int j=0; j<NY; j++){
                nonLinear[j][i] = nonLinear[j][i] * 1.5*1.5;
            }
        }
    }

    return nonLinear;
}

vector<vector<complex<double>>> pad(vector<vector<complex<double>>> f){

    vector<vector<complex<double>>> fp(NYP, vector<complex<double>> (NXP, 0));
    
    for (int i=0; i<=NX/2; i++){
        for (int j=0; j<=NY/2; j++){
            fp[j][i] = f[j][i];
        }
    }

    for (int i=NXP-NX/2+1; i<NXP; i++){
        for (int j=0; j<=NY/2; j++){
            fp[j][i] = f[j][i-NX/2];
        }
    }

    for (int i=0; i<=NX/2; i++){
        for (int j=NYP-NY/2+1; j<NXP; j++){
            fp[j][i] = f[j-NY/2][i];
        }
    }

    for (int i=NXP-NX/2+1; i<NXP; i++){
        for (int j=NYP-NY/2+1; j<NXP; j++){
            fp[j][i] = f[j-NY/2][i-NX/2];
        }
    }

    return fp;
}

vector<vector<complex<double>>> chop(vector<vector<complex<double>>> fp){

    vector<vector<complex<double>>> f(NY, vector<complex<double>> (NX, 0));

    for (int i=0; i<=NX/2; i++){
        for (int j=0; j<=NY/2; j++){
            f[j][i] = fp[j][i];
        }
    }

    for (int i=NX/2+1; i<NX; i++){
        for (int j=0; j<=NY/2; j++){
            f[j][i] = fp[j][i+NX/2];
        }
    }

    for (int i=0; i<=NX/2; i++){
        for (int j=NY/2+1; j<NX; j++){
            f[j][i] = fp[j+NY/2][i];
        }
    }

    for (int i=NX/2+1; i<NX; i++){
        for (int j=NY/2+1; j<NX; j++){
            f[j][i] = fp[j+NY/2][i+NX/2];
        }
    }

    return f;
}