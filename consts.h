#ifndef consts_h
#define consts_h


const double G =  6.67e-11;
const double tmax = 500e7 * (60*60*24*365.25);
const double dt = 100000 * (60*60*24*365.25);

const int elements = 122;
const double snapshot = 40 * dt;

const double Rmin = 25 * 3.08567758e19;

const double rad = 0.0174532925;

const double Galaxy1Mass = 1e11 * 2e30;
const double Galaxy2Mass = 1e11 * 2e30;

const double damp = 1e50;


#endif
