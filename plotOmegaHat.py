import numpy as np
import matplotlib.pyplot as plt


def main():

    def transform_complex(line):
        return line.replace(b'+-',b'-')

    with open('test.txt', 'rb') as f:
        lines = map(transform_complex, f)
        omegaHat = np.reshape(np.loadtxt(lines, dtype=np.complex128), (NY, NX))

    # omegaHat = np.reshape(np.loadtxt('test.txt', converters={0: lambda x: x.replace('+-','-')}), (NY, NX))

    plt.pcolor(
        np.abs(omegaHat[32:-32,32:-32]), 
        cmap='magma'
    )
    
    plt.savefig('omegaHatIC.png')

    return


if __name__ == '__main__':

    NX = 128
    NY = 128

    main()