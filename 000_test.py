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
xSource = r * np.cos( phi )
ySource = r * np.sin( phi )
charge = 1.+0.*xSource

fpps = CyFPPS.PyFPPS(nTheta=40, nR=100, a=.5)
fpps.scatter(xSource, ySource, charge)
fpps.solve()

for offset in np.arange(-3*R,3*R,6*R/10):
    x = np.arange(-3*R,3*R,6*R/1000)
    y = np.zeros_like(x)+offset

    Ex, Ey = fpps.gather(x,y)

    pl.figure(0)
    pl.plot(x,Ex, '.')

fpps = CyFPPS.PyFPPS(nTheta=40, nR=100, a=.5,useSourceAsProbe=True)
fpps.scatter(xSource, ySource, charge)
fpps.solve()
Ex, Ey = fpps.gather(xSource,ySource)
pl.figure(1)
pl.plot(r,np.sqrt(Ex**2+Ey**2), '.')

pl.show()





