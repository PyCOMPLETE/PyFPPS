#include "PolarBeamRepresentation.h"
#include <cmath>

PolarBeamRepresentation::PolarBeamRepresentation(int n):
npart(n) {
    radius = new double[npart];
    angle = new double[npart];
}
PolarBeamRepresentation::~PolarBeamRepresentation() {
    delete radius;
    delete angle;
}

double PolarBeamRepresentation::getCharge(int i){
    return charge[i];
}
double PolarBeamRepresentation::getRadius(int i){
    return radius[i];
}
double PolarBeamRepresentation::getAngle(int i){
    return angle[i];
}
int PolarBeamRepresentation::getSize(){
    return npart;
}

void PolarBeamRepresentation::getField(int i,double* x,double* y,double* Ex,double* Ey,double radialField,double polarField) {
    double costheta=x[i]/radius[i];
    double sintheta=y[i]/radius[i];
    Ex[i] += costheta*radialField-sintheta*polarField;
    Ey[i] += sintheta*radialField+costheta*polarField;
}

void PolarBeamRepresentation::update(double* x,double* y,double* sourceCharge) {
    charge = sourceCharge;
    #pragma omp parallel for schedule(guided,1000)
    for(int i=0; i<npart; ++i){
        radius[i] = sqrt(x[i]*x[i]+y[i]*y[i]);
        angle[i] = atan2(y[i],x[i]);
        if (angle[i] < 0) angle[i] += 2.0*M_PI;
    }
}
