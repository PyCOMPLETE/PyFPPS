#ifndef __FPPSTEST
#define __FPPSTEST


#include "NonLinearMesh.h"
#include "ChangeCoord_Frac.h"
#include "ChargeDistribution.h"
#include "FastPolarPoissonSolver.h"
#include "ElectricFieldSolver.h"
#include "PolarBeamRepresentation.h"

void test();



class FPPS{
public:
	FPPS(int nTheta, int nR, double a);
	void solveall(int nSource, double* xSource, double* ySource, double* chargeSource,
				 double* Ex, double* Ey);
protected:
	ChangeCoord_Frac *g;
	NonLinearMesh *chargeDistributionMesh;
	NonLinearMesh *radialField;
	NonLinearMesh *polarField;
	ChargeDistribution *chargeDistribution;
	FastPolarPoissonSolver *fastPolarPoissonSolver;
	ElectricFieldSolver *electricFieldSolver;

};

#endif
