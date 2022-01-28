#include "fluid.h"


vector<vector<complex<double>>> applyFFT2(vector<vector<double>> A){
    
    vector<vector<complex<double>>> output(A.size() , vector<complex<double>> (A.size(), 0));

    fftw_complex *in;
    fftw_complex *out;
    fftw_plan p;
    in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * A.size()*A[0].size());
    out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * A.size()*A[0].size());
    
    p = fftw_plan_dft_2d(A.size(), A[0].size(), in, out, FFTW_FORWARD, FFTW_MEASURE);

    for(size_t i = 0; i < A.size(); i++){
        for(size_t j = 0; j < A[0].size(); j++){
            in[i*A.size()+j][0]=A[i][j];
            in[i*A.size()+j][1]=0.0;
        }
    }
    fftw_execute(p); 

    for(size_t i = 0; i < A.size(); i++){
        for(size_t j = 0; j < A[0].size(); j++){
            complex<double> temp(out[i*A.size()+j][0], out[i*A.size()+j][1]);
            output[i][j] = temp;
        }
    }
    
    fftw_destroy_plan(p);
    fftw_free(in); 
    fftw_free(out);

    return output;
}


vector<vector<complex<double>>> applyFFT2Complex(vector<vector<complex<double>>> A){
    
    vector<vector<complex<double>>> output(A.size() , vector<complex<double>> (A.size(), 0));

    fftw_complex *in;
    fftw_complex *out;
    fftw_plan p;
    in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * A.size()*A[0].size());
    out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * A.size()*A[0].size());
    
    p = fftw_plan_dft_2d(A.size(), A[0].size(), in, out, FFTW_FORWARD, FFTW_MEASURE);
    for(size_t i = 0; i < A.size(); i++){
        for(size_t j = 0; j < A[0].size(); j++){
            in[i*A.size()+j][0]=A[i][j].real();
            in[i*A.size()+j][1]=A[i][j].imag();
        }
    }
    fftw_execute(p); 

    for(size_t i = 0; i < A.size(); i++){
        for(size_t j = 0; j < A[0].size(); j++){
            complex<double> temp(out[i*A.size()+j][0], out[i*A.size()+j][1]);
            output[i][j] = temp;
        }
    }
    
    fftw_destroy_plan(p);
    fftw_free(in); 
    fftw_free(out);

    return output;
}


vector<vector<complex<double>>> applyIFFT2(vector<vector<complex<double>>> A){
    
    vector<vector<complex<double>>> output(A.size() , vector<complex<double>> (A[0].size(), 0));


    fftw_complex *out;
    fftw_complex *in;
    fftw_plan p;
    
    in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * A.size()*A[0].size());
    out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * A.size()*A[0].size());

    
    p = fftw_plan_dft_2d(A.size(), A[0].size(), in, out, FFTW_BACKWARD, FFTW_MEASURE);
    for(size_t i = 0; i < A.size(); i++){
        for(size_t j = 0; j < A[0].size(); j++){
            in[i*A.size()+j][0]=A[i][j].real();
            in[i*A.size()+j][1]=A[i][j].imag();
        }
    }
    fftw_execute(p); 
    
    for(size_t i = 0; i < A.size(); i++){
        for(size_t j = 0; j < A[0].size(); j++){
            output[i][j] = out[i*A.size()+j][0] / A.size() / A[0].size() + out[i*A.size()+j][1] / A.size() / A[0].size();
        }
    }
    
    fftw_destroy_plan(p);
    fftw_free(in); 
    fftw_free(out);

    return output;
}
