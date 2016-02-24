
#include <fstream>
#include <stdlib.h>
#include <iostream>

#include "FPPSWrapper.h"

FPPSWrapper::FPPSWrapper(int nTheta, int nR, double a){
		g = new ChangeCoord_Frac(a);
		chargeDistributionMesh = new NonLinearMesh(nTheta,nR,1.0,g);
		radialField = new NonLinearMesh(nTheta,nR,1.0,g);
		polarField = new NonLinearMesh(nTheta,nR,1.0,g);
		chargeDistribution = new ChargeDistribution(chargeDistributionMesh);
		fastPolarPoissonSolver = new FastPolarPoissonSolver(chargeDistribution);
		electricFieldSolver = new ElectricFieldSolver(fastPolarPoissonSolver,radialField,polarField);
        sourcePolarBeamRepresentation = new PolarBeamRepresentation(0);
        probePolarBeamRepresentation = new PolarBeamRepresentation(0);
}

void FPPSWrapper::scatter(double* x,double* y,double* charge,int n) {
    sourcePolarBeamRepresentation->update(x,y,charge,n); // compute the polar coordinates of each source particle
    chargeDistribution->fill(sourcePolarBeamRepresentation); // scatter the charge on the polar grid
}
void FPPSWrapper::gather(double* x,double* y,double* Ex, double* Ey,int n) {
    probePolarBeamRepresentation->update(x,y,n); // compute the polar coordinates of each probe particle
    electricFieldSolver->getField(probePolarBeamRepresentation,x,y,Ex,Ey); // Gather the fields in polar coordinates and project into cartesian coordinates.
}
void FPPSWrapper::solve() {
    electricFieldSolver->solve();
}
