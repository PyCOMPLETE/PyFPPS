
#include <fstream>
#include <stdlib.h>
#include <iostream>

#include "FPPSTest.h"

using namespace std;

void test() {
    int nSource = 1000;
    double* xSource = new double[nSource];
    double* ySource = new double[nSource];
    double* chargeSource = new double[nSource];

    for(int i=0;i<nSource;++i) {
        xSource[i] = 2.0*rand()/RAND_MAX-1.0;
        ySource[i] = 2.0*rand()/RAND_MAX-1.0;
        chargeSource[i] = 1.0;
    }

    double* Ex = new double[nSource];
    double* Ey = new double[nSource];

    double a = 0.1;
    double nTheta = 40;
    double nR = 40;

    ChangeCoord_Frac g(a);
    NonLinearMesh chargeDistributionMesh(nTheta,nR,1.0,&g);
    NonLinearMesh radialField(nTheta,nR,1.0,&g);
    NonLinearMesh polarField(nTheta,nR,1.0,&g);
    ChargeDistribution myChargeDistribution(&chargeDistributionMesh);
    FastPolarPoissonSolver fastPolarPoissonSolver(&myChargeDistribution);
    ElectricFieldSolver electricFieldSolver(&fastPolarPoissonSolver,&radialField,&polarField);

    PolarBeamRepresentation polarBeamRepresentation(nSource);
    polarBeamRepresentation.update(xSource,ySource,chargeSource);
    myChargeDistribution.fill(&polarBeamRepresentation);
    electricFieldSolver.solve();
    electricFieldSolver.getField(&polarBeamRepresentation,xSource,ySource,Ex,Ey);

    std::ofstream* out;
    out = new std::ofstream;
    out->open("output.csv");
    cout<<"Ciuao"<<endl;
    for(int i=0;i<nSource;++i) {
        *out << xSource[i] << "," << ySource[i] << "," << Ex[i] << "," << Ey[i];
        if(i<nSource-1) {
            *out << endl;
        }
    }
    out->close();

    delete xSource;
    delete ySource;
    delete chargeSource;
    delete Ex;
    delete Ey;
	
}


FPPS::FPPS(int nTheta, int nR, double a){
		g = new ChangeCoord_Frac(a);
		chargeDistributionMesh = new NonLinearMesh(nTheta,nR,1.0,g);
		radialField = new NonLinearMesh(nTheta,nR,1.0,g);
		polarField = new NonLinearMesh(nTheta,nR,1.0,g);
		chargeDistribution = new ChargeDistribution(chargeDistributionMesh);
		fastPolarPoissonSolver = new FastPolarPoissonSolver(chargeDistribution);
		electricFieldSolver = new ElectricFieldSolver(fastPolarPoissonSolver,radialField,polarField);	
	}
	
void FPPS::solveall(int nSource, double* xSource, double* ySource, double* chargeSource,
				 double* Ex, double* Ey){
	PolarBeamRepresentation polarBeamRepresentation(nSource);
    polarBeamRepresentation.update(xSource,ySource,chargeSource);
    chargeDistribution->fill(&polarBeamRepresentation);
    electricFieldSolver->solve();
    electricFieldSolver->getField(&polarBeamRepresentation,xSource,ySource,Ex,Ey);
    
}
