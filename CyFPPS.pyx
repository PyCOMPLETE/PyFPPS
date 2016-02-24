import numpy as np
cimport numpy as np
    
cdef extern from "FPPSWrapper.h":
    cdef cppclass FPPSWrapper:
        FPPSWrapper(int nTheta, int nR, double a) except + #propagates the exception correctly
        void scatter(double* x,double* y,double* charge,int n)
        void gather(double* x,double* y,double* Ex, double* Ey,int n)
        void solve()

    
cdef class PyFPPS:
    cdef FPPSWrapper *thisptr      # hold a C++ instance which we're wrapping
    def __cinit__(self, int nTheta, int nR, double a):
        self.thisptr = new FPPSWrapper(nTheta, nR, a)

    cpdef scatter(self, np.ndarray x, np.ndarray y, np.ndarray charge):
        cdef double* x_data = <double*>x.data
        cdef double* y_data = <double*>y.data
        cdef double* charge_data = <double*>charge.data

        self.thisptr.scatter(x_data,y_data,charge_data,len(x))

    cpdef gather(self, np.ndarray x, np.ndarray y):
        cdef double* x_data = <double*>x.data
        cdef double* y_data = <double*>y.data
        cdef np.ndarray Ex = 0.*x; 
        cdef np.ndarray Ey = 0.*x;
        
        cdef double* Ex_data = <double*>Ex.data
        cdef double* Ey_data = <double*>Ey.data

        self.thisptr.gather(x_data, y_data, Ex_data, Ey_data,len(x))
        return Ex, Ey

    cpdef solve(self):
        self.thisptr.solve()

