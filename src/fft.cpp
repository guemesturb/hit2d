#include "fluid.h"

vector<vector<complex<double>>> applyFFT2(vector<vector<double>> A){

    // complex_t output;
    
    vector<vector<complex<double>>> output(A.size() , vector<complex<double>> (A.size(), 0));


    double *in;
    fftw_complex *out;
    fftw_plan p;
    in = (double *)fftw_malloc(sizeof(double) * NX*NY);

    for(size_t i = 0; i < A.size(); i++){
        for(size_t j = 0; j < A[0].size(); j++){
            in[i*A.size()+j]=A[i][j];
        }
    }
    
    out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * NX*NY);
    
    p = fftw_plan_dft_r2c_2d(NX, NY, in, out, FFTW_ESTIMATE);
    fftw_execute(p); 

    for(size_t i = 0; i < A.size(); i++){
        for(size_t j = 0; j < A[0].size(); j++){

            complex<double> temp(out[i*A.size()+j][0], out[i*A.size()+j][1]);

            output[i][j] = temp;
            
            // tmpReal[i][j]=out[i*A.size()+j][0];
            // tmpImag[i][j]=out[i*A.size()+j][1];
        }
    }
    
    fftw_destroy_plan(p);
    fftw_free(in); 
    fftw_free(out);

    // output.real = tmpReal;
    // output.imag = tmpImag;

    return output;
}

vector<vector<double>> applyIFFT2(vector<vector<complex<double>>> A){

    // complex_t output;
    
    vector<vector<double>> output(A.size() , vector<double> (A.size(), 0));


    fftw_complex *out;
    fftw_complex *in;
    fftw_plan p;
    
    in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * NX*NY);

    for(size_t i = 0; i < A.size(); i++){
        for(size_t j = 0; j < A[0].size(); j++){
            in[i*A.size()+j][0]=A[i][j].real();
            in[i*A.size()+j][1]=A[i][j].imag();
        }
    }
    
    out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * NX*NY);
    
    p = fftw_plan_dft_2d(NX, NY, in, out, FFTW_BACKWARD, FFTW_ESTIMATE);
    fftw_execute(p); 

    for(size_t i = 0; i < A.size(); i++){
        for(size_t j = 0; j < A[0].size(); j++){

            complex<double> temp(out[i*A.size()+j][0], out[i*A.size()+j][1]);

            output[i][j] = temp.real();
            
            // tmpReal[i][j]=out[i*A.size()+j][0];
            // tmpImag[i][j]=out[i*A.size()+j][1];
        }
    }
    
    fftw_destroy_plan(p);
    fftw_free(in); 
    fftw_free(out);

    // output.real = tmpReal;
    // output.imag = tmpImag;

    return output;
}
