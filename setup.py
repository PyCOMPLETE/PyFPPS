from distutils.core import setup, Extension
from Cython.Build import cythonize

setup(ext_modules = cythonize(Extension(
           "FPPScy",                                # the extesion name
           sources=["FPPScy.pyx", "FPPSTest.cc",
           'ChangeCoord.cc', 'ElectricFieldSolver.cc', 'Mesh.cc',
		   'ChangeCoord_Frac.cc', 'FastPolarPoissonSolver.cc',  'NonLinearMesh.cc',
		   'ChangeCoord_Tanh.cc', 'PolarBeamRepresentation.cc',
		   'ChargeDistribution.cc', 'FunctionsFPPS.cc'], 				  # the Cython source and additional C++ source files generate and compile C++ code
           language="c++",  libraries=[	'fftw3']                      
      )))
