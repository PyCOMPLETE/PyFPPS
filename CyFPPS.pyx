import numpy as np
cimport numpy as np
	
cdef extern from "FPPSWrapper.h":
	cdef cppclass FPPSWrapper:
		FPPSWrapper(int, int, double) except + #propagates the exception correctly
		void solveall(int, double*, double*, double*,
				 double*, double*)

	
cdef class PyFPPS:
	cdef FPPSWrapper *thisptr      # hold a C++ instance which we're wrapping
	def __cinit__(self, int nTheta, int nR, double a):
		self.thisptr = new FPPSWrapper(nTheta, nR, a)
	cpdef solveall(self, np.ndarray xSource, np.ndarray ySource, 
		np.ndarray chargeSource):
		cdef double* xSource_data = <double*>xSource.data
		cdef double* ySource_data = <double*>ySource.data
		cdef double* chargeSource_data = <double*>chargeSource.data
		
		cdef np.ndarray Ex = 0.*xSource; 
		cdef np.ndarray Ey = 0.*xSource;
		
		cdef double* Ex_data = <double*>Ex.data
		cdef double* Ey_data = <double*>Ey.data
 
		self.thisptr.solveall(len(xSource),xSource_data, ySource_data, 
					chargeSource_data, Ex_data, Ey_data)
		return Ex, Ey

