#ifndef __FPPSTEST
#define __FPPSTEST


#include "NonLinearMesh.h"
#include "ChangeCoord_Frac.h"
#include "ChargeDistribution.h"
#include "FastPolarPoissonSolver.h"
#include "ElectricFieldSolver.h"
#include "PolarBeamRepresentation.h"

class FPPSWrapper{
public:
	FPPSWrapper(int nTheta, int nR, double a);
    void scatter(double* x,double* y,double* charge,int n);
    void gather(double* x,double* y,double* Ex, double* Ey,int n);
	void solve();
    void useSourceAsProbe();

protected:
    bool sourceIsProbe;
	ChangeCoord_Frac *g;
	NonLinearMesh *chargeDistributionMesh;
	NonLinearMesh *radialField;
	NonLinearMesh *polarField;
	ChargeDistribution *chargeDistribution;
	FastPolarPoissonSolver *fastPolarPoissonSolver;
	ElectricFieldSolver *electricFieldSolver;
    PolarBeamRepresentation* sourcePolarBeamRepresentation;
    PolarBeamRepresentation* probePolarBeamRepresentation;
};

#endif
