import numpy as np
import matplotlib.pyplot as plt


def main():

    omega = np.reshape(np.loadtxt('omega.txt'), (NY, NX))

    plt.contourf(
        omega, 
        levels=[-100,-90,-80,-70,-60,-50,-40,-30,-20,-10,10,20,30,40,50,60,70,80,90,100], 
        cmap='RdGy_r', 
        extend='both'
    )
    
    plt.savefig('IC.png')

    return


if __name__ == '__main__':

    NX = 128
    NY = 128

    main()