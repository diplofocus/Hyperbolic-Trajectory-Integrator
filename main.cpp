#include <iostream>
#include <math.h>
#include <fstream>

#include "vect.h"
#include "consts.h"
#include "kepcart.h"

const double G =  6.67e-11;
const double tmax = 2 * (60*60*24*365.25);
const double dt = 0.001 * 86400;

const int elements = 2;
const int snapshot = 50;

ofstream out;
ofstream enout;

double perc, currPerc, frame;

double cube(double a)
{
  return a*a*a;
}

double sqr(double a)
{
  return a*a;
}

double PotEn(double x, double y)
{
  double dist = sqrt(x*x + y*y);
  double rez = -G * (2e30*6e24) / dist;
  return rez;
}

double KinEn(Vect V)
{
  double rez = 6e24 * (V.x*V.x + V.y*V.y)  / 2.0;
  return rez;
}

class Body
{
public:
  Vect r,r1,r2,r3,r4;
  Vect v,v1,v2,v3,v4;
  Vect a,a1,a2,a3,a4;
  double m;
  
  Body()
  {
    m = 0;
  }
};

Vect VectDist;
double ScalDist;


int main()
{

  int frame = snapshot;
  double perc = 0;
  int currPerc = 0;

  
  
  out.open("out.txt");
  enout.open("energy.txt");
  Body* bodies[elements];
  for(int i = 0; i < elements; i++)
    {
      bodies[i] = new Body();
    }
  
  PhaseState* PState = new PhaseState();
  OrbitalElements *oe = new OrbitalElements {
    150e9, 1.1, 1e-30, 0, 0, -0.30*3.1415926};

  cartesian(1.334e20, *oe, PState);

  cout << PState->x << ", " << PState->y << endl << PState->xd << ", " << PState->yd << endl;

  bodies[0]->m = 2e30;
  bodies[0]->v.y = -0.09;
  bodies[1]->m = 6e24;
  bodies[1]->r.x = PState->x;
  bodies[1]->r.y = PState->y;
  bodies[1]->v.x = PState->xd;
  bodies[1]->v.y = PState->yd;

  bodies[0]->v = bodies[1]->v * (-bodies[1]->m / bodies[0]->m);
  
  for(int t = 0; t < tmax; t += dt)
    {
      if(perc >= tmax / 100.0)
	{
	  cout.flush();
	  currPerc++;
	  cout << currPerc << endl;
	  perc=0;
	}
      
      
      if((frame % snapshot) == 0)
	{
	  for(int i = 0; i < elements; i++)
	    {
	      out << bodies[i]->r.x << ", " << bodies[i]->r.y << ", " << bodies[i]->r.z  << endl;
	      enout << (t/30780000.0) << ", " << PotEn(bodies[1]->r.x, bodies[1]->r.y) + KinEn(bodies[1]->v) << endl;
	    }
	}
      
      perc += dt;
      frame++;
      
      //k1
      for(int i = 0; i < elements; i++)
	{
	  bodies[i]->r1 = bodies[i]->r;
	  bodies[i]->v1 = bodies[i]->v;
	}
      for(int i = 0; i < elements; i++)
	for(int j = 0; j < elements; j++)
	  {
	    if(i == j)
	      continue;
	    VectDist = bodies[i]->r1 - bodies[j]->r1;
	    ScalDist = VectDist.Int();
	    bodies[i]->a1 += VectDist * (-G * bodies[j]->m / cube(ScalDist));
	  }
      //end k1
      
      //k2
      for(int i = 0; i < elements; i++)
	{
	  bodies[i]->v2 = bodies[i]->v1 + bodies[i]->a1 * (dt/2.0);
	  bodies[i]->r2 = bodies[i]->r1 + bodies[i]->v1 * (dt/2.0);
	}
      for(int i = 0; i < elements; i++)
	for(int j = 0; j < elements; j++)
	  {
	    if(i == j)
	      continue;
	    VectDist = bodies[i]->r2 - bodies[j]->r2;
	    ScalDist = VectDist.Int();
	    bodies[i]->a2 += VectDist * (-G * bodies[j]->m / cube(ScalDist));
	  }
      //end k2
      
      //k3
      for(int i = 0; i < elements; i++)
	{
	  bodies[i]->v3 = bodies[i]->v1 + bodies[i]->a2 * (dt/2.0);
	  bodies[i]->r3 = bodies[i]->r1 + bodies[i]->v2 * (dt/2.0);
	}
      for(int i = 0; i < elements; i++)
	for(int j = 0; j < elements; j++)
	  {
	    if(i == j)
	      continue;
	    VectDist = bodies[i]->r3 - bodies[j]->r3;
	    ScalDist = VectDist.Int();
	    bodies[i]->a3 += VectDist * (-G * bodies[j]->m / cube(ScalDist));
	  }
      //end k3
      
      //k4
      for(int i = 0; i < elements; i++)
	{
	  bodies[i]->v4 = bodies[i]->v1 + bodies[i]->a3 * dt;
	  bodies[i]->r4 = bodies[i]->r1 + bodies[i]->v3 * dt;
	}

      for(int i = 0; i < elements; i++)
	for(int j = 0; j < elements; j++)
	  {
	    if(i == j)
	      continue;
	    VectDist = bodies[i]->r4 - bodies[j]->r4;
	    ScalDist = VectDist.Int();
	    bodies[i]->a4 += VectDist * (-G * bodies[j]->m / cube(ScalDist));
	  }
      //end k4
            
      for(int i = 0; i < elements; i++)
	{
	  bodies[i]->v += (bodies[i]->a1 + bodies[i]->a2*2 + bodies[i]->a3*2 + bodies[i]->a4) * dt/6.0;
	  bodies[i]->r += (bodies[i]->v1 + bodies[i]->v2*2 + bodies[i]->v3*2 + bodies[i]->v4) * dt/6.0;
	}
            
      //flush
      for(int i = 0; i < elements; i++)
	{
	  bodies[i]->a1.x = 0;
	  bodies[i]->a1.y = 0;
	  bodies[i]->a2.x = 0;
	  bodies[i]->a2.y = 0;
	  bodies[i]->a3.x = 0;
	  bodies[i]->a3.y = 0;
	  bodies[i]->a4.x = 0;
	  bodies[i]->a4.y = 0;	  
	}
      //flush
      
    }
  out.close();
  enout.close();
  return 0;
}










































//If you venture here, be warned
//Deni be gay.Protect yer buttholes.
