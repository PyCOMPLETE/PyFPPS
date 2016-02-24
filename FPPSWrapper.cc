
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
}

void FPPSWrapper::solveall(int nSource, double* xSource, double* ySource, double* chargeSource,
				 double* Ex, double* Ey){
	PolarBeamRepresentation polarBeamRepresentation(nSource);
    polarBeamRepresentation.update(xSource,ySource,chargeSource);
    chargeDistribution->fill(&polarBeamRepresentation);
    electricFieldSolver->solve();
    electricFieldSolver->getField(&polarBeamRepresentation,xSource,ySource,Ex,Ey);
    
}
