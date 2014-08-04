#include <iostream>
#include <math.h>
#include <fstream>

#include "vect.h"
#include "consts.h"
#include "kepcart.h"
#include "galaxy.h"
#include "bodies.h"

Vect Galaxy1Pos(-3 * Rmin, -1 * Rmin, 0);
//Vect Galaxy1Vel(50000, -20000, 0);
Vect Galaxy2Pos(3 * Rmin, 1 * Rmin, 0);
//Vect Galaxy2Vel(-50000, 0, 0);

double LastSnapTime = 0;

ofstream out;
ofstream enout;
ofstream setup;

double perc, currPerc, frame;
Vect VectDist;
double ScalDist;

inline double cube(double a)
{
  return a*a*a;
}

inline double sqr(double a)
{
  return a*a;
}

int main()
{
  double lastPercTime = 0;
  int currPerc = 0;
  
  out.open("out.txt");
  enout.open("energy.txt");
  setup.open("setup.txt");

  setup << elements;

  Body* bodies[elements];
  Body** massiveBodies;
  Body *A, *B;

  for(int i = 0; i < elements; i++)
    {
      bodies[i] = new Body();
    }

  Galaxy1Vel = GalaxySpeed(Galaxy1Mass, Galaxy2Mass, Galaxy1Pos, Galaxy2Pos, Rmin) * -1;
  Galaxy2Vel = GalaxySpeed(Galaxy2Mass, Galaxy1Mass, Galaxy2Pos, Galaxy1Pos, Rmin) * -1;



  CreateGalaxy(bodies, Galaxy1Mass, Galaxy1Pos, Galaxy1Vel, 1, 1, 0);
  CreatePointMass(bodies, Galaxy2Mass, Galaxy2Pos, Galaxy2Vel, 121);
  bodies[121]->parent = 1;

  int massiveElements = GetMassiveBodyCount(bodies);
  massiveBodies = GetMassiveBodies(bodies);
 
  for(double t = 0; t <= tmax; t += dt)
    {
   	if(t/tmax >= lastPercTime + 0.01)
		{
  			cout << ++currPerc << endl;
  			lastPercTime = currPerc / 100.0;
		}
       
   //    if(t > LastSnapTime+snapshot)
			// {
			// //cout << "pls" << endl;
			// LastSnapTime = t;
		 //  	for(int i = 0; i < elements; i++)
		 //   	{
		 //      	out << *bodies[i] << endl;
		 //   	}
			// }

			if(t > LastSnapTime+snapshot)
			{
			//cout << "pls" << endl;
			LastSnapTime = t;
		  	for(int i = 0; i < massiveElements; i++)
		   	{
		      	out << *massiveBodies[i] << endl;
		   	}
			}	
      
      //k1

      for(int i = 0; i < elements; i++)
	{
	  bodies[i]->r1 = bodies[i]->r;
	  bodies[i]->v1 = bodies[i]->v;
	}

      for(int i = 0; i < elements; i++)
	for(int j = 0; j < massiveElements; j++)
	  {
	    A = bodies[i];
	    B = massiveBodies[j];

	    if(A == B)
	      continue;

	    VectDist = A->r1 - B->r1;
	    ScalDist = VectDist.Int();
	    A->a1 += VectDist * (-G * B->m / cube(ScalDist));
	    if(A->a1.Int() > damp)
	      {
		A->a1.x = 0;
		A->a1.y = 0;
	      }
	  }
      //end k1
      
      //k2
      for(int i = 0; i < elements; i++)
	{
	  bodies[i]->v2 = bodies[i]->v1 + bodies[i]->a1 * (dt/2.0);
	  bodies[i]->r2 = bodies[i]->r1 + bodies[i]->v1 * (dt/2.0);
	}
      for(int i = 0; i < elements; i++)
	for(int j = 0; j < massiveElements; j++)
	  {
	    
	    A = bodies[i];
	    B = massiveBodies[j];

	    if(A == B)
	      continue;

	    VectDist = A->r2 - B->r2;
	    ScalDist = VectDist.Int();
	    A->a2 += VectDist * (-G * B->m / cube(ScalDist));
	    if(A->a.Int() > damp)
	      {
		A->a2.x = 0;
		A->a2.y = 0;
	      }
	  }
      //end k2
      
      //k3
      for(int i = 0; i < elements; i++)
	{
	  bodies[i]->v3 = bodies[i]->v1 + bodies[i]->a2 * (dt/2.0);
	  bodies[i]->r3 = bodies[i]->r1 + bodies[i]->v2 * (dt/2.0);
	}
      for(int i = 0; i < elements; i++)
	for(int j = 0; j < massiveElements; j++)
	  {
	    A = bodies[i];
	    B = massiveBodies[j];

	    if(A == B)
	      continue;


	    VectDist = A->r3 - B->r3;
	    ScalDist = VectDist.Int();
	    A->a3 += VectDist * (-G * B->m / cube(ScalDist));
	    if(A->a3.Int() > damp)
	      {
		A->a3.x = 0;
		A->a3.y = 0;
	      }
	  }
      //end k3
      
      //k4
      for(int i = 0; i < elements; i++)
	{
	  bodies[i]->v4 = bodies[i]->v1 + bodies[i]->a3 * dt;
	  bodies[i]->r4 = bodies[i]->r1 + bodies[i]->v3 * dt;
	}

      for(int i = 0; i < elements; i++)
	for(int j = 0; j < massiveElements; j++)
	  {
	    A = bodies[i];
	    B = massiveBodies[j];

	    if(A == B)
	      continue;

	    VectDist = A->r4 - B->r4;
	    ScalDist = VectDist.Int();
	    A->a4 += VectDist * (-G * B->m / cube(ScalDist));
	    if(A->a4.Int() > damp)
	      {
		A->a4.x = 0;
		A->a4.y = 0;
	      }
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
  setup.close();

  return 0;
}










































//If you venture here, be warned
//Deni be gay.Protect yer buttholes.
