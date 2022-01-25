import numpy as np
import matplotlib.pyplot as plt


def main():

    omega = np.reshape(np.loadtxt('test.txt'), (NY, NX))

    plt.pcolor(omega)
    plt.savefig('IC.png')

    return


if __name__ == '__main__':

    NX = 128
    NY = 128

    main()