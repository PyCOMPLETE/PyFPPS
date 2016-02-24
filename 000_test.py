import CyFPPS
from numpy.random import rand
import numpy as np
import pylab as pl

pl.close('all')

R = 1.
N_points = 1000000

phi = rand(N_points)*2*np.pi
u = rand(N_points)

r = R * np.sqrt( u )

x = r * np.cos( phi )
y = r * np.sin( phi )

charge = 1.+0.*x

charge[x**2+y**2<0.5**2] = 0.

pl.figure()
pl.plot(x,y, '.')
pl.axis('equal')
pl.show()

fpps = CyFPPS.PyFPPS(nTheta=40, nR=100, a=.5)
Ex, Ey = fpps.solveall(x, y, charge)

pl.figure(100)
pl.plot(np.sqrt(x**2+y**2),np.sqrt(Ex**2+Ey**2), '.')

pl.show()





