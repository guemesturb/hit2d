import numpy as np
import matplotlib.pyplot as plt


def main():

    omega = np.reshape(np.loadtxt('omega.txt'), (NY, NX))

    plt.pcolor(
        omega, 
        vmin=-100,
        vmax=100, 
        cmap='magma'
    )
    
    plt.savefig('IC.png')

    return


if __name__ == '__main__':

    NX = 128
    NY = 128

    main()