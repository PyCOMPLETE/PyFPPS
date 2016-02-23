import numpy as np
from matplotlib import pyplot as plt

if __name__ == '__main__':
    data = np.loadtxt('output.csv',delimiter=',')
    plt.plot(data[:,0],data[:,2],'x')
    plt.show()
