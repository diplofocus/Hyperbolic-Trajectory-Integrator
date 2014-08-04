#include <iostream>
#include <math.h>
#include <stdlib.h>

#include "vect.h"
#include "bodies.h"
#include "consts.h"

using namespace std;

static int GalaxyID = 0;


Vect OrbitalSpeed(Body* B, double angle, double Dist, double Mass  ,double direction)
{
  double Speed = sqrt(G * (Mass + B->m) / Dist);
  Vect ret;
  ret.x = direction * Speed * cos(angle * rad + 90 * rad);
  ret.y = direction * Speed * sin(angle * rad + 90 * rad);
  return ret;
}

void CreateGalaxy(Body** bodies, double GalaxyMass, Vect GalaxyPos, Vect GalaxyVel, double Scale, int Direction, int Start)
{
	int bodyCount = Start;
	bodies[bodyCount]->m = GalaxyMass;
	bodyCount++;
	double r = 0.2 * Rmin * Scale;

	for(int theta = 0; theta < 360; theta++)
	{
	 if((theta % (360/12)) == 0)
	 {
		 	bodies[bodyCount]->r.x = r * cos(theta * rad);
			bodies[bodyCount]->r.y = r * sin(theta * rad);
			bodies[bodyCount]->v = OrbitalSpeed(bodies[bodyCount], theta, r, GalaxyMass, Direction);
			bodyCount++;
	 }
	}

	r = 0.3 * Rmin * Scale;
	for(int theta = 0; theta < 360; theta++)
	{
	 if((theta % (360/18)) == 0)
		{ 
	  bodies[bodyCount]->r.x = r * cos(theta * rad);
	  bodies[bodyCount]->r.y = r * sin(theta * rad);
	  bodies[bodyCount]->v = OrbitalSpeed(bodies[bodyCount], theta, r, GalaxyMass, Direction);
	  bodyCount++;
	}
	}

	r = 0.4 * Rmin * Scale;
	for(int theta = 0; theta < 360; theta++)
	{
	 if((theta % (360/24)) == 0)
	 {
	   bodies[bodyCount]->r.x = r * cos(theta * rad);
	   bodies[bodyCount]->r.y = r * sin(theta * rad);
	   bodies[bodyCount]->v = OrbitalSpeed(bodies[bodyCount], theta, r, GalaxyMass, Direction);
	   bodyCount++;
	 }
	}

 r = 0.5 * Rmin * Scale;
 for(int theta = 0; theta < 360; theta++)
 {
   if((theta % (360/30)) == 0)
	{
	  bodies[bodyCount]->r.x = r * cos(theta * rad);
	  bodies[bodyCount]->r.y = r * sin(theta * rad);
	  bodies[bodyCount]->v = OrbitalSpeed(bodies[bodyCount], theta, r, GalaxyMass, Direction);
	  bodyCount++;
	}
 }

 r = 0.6 * Rmin * Scale;
 for(int theta = 0; theta < 360; theta++)
 {
   if((theta % (360/36)) == 0)
	{
	  bodies[bodyCount]->r.x = r * cos(theta * rad);
	  bodies[bodyCount]->r.y = r * sin(theta * rad);
	  bodies[bodyCount]->v = OrbitalSpeed(bodies[bodyCount], theta, r, GalaxyMass, Direction);
	  bodyCount++;
	}
 }

 for(int i = Start; i < Start + 121; i++)
 {
 	bodies[i]->r += GalaxyPos;
 	bodies[i]->v += GalaxyVel;
 	bodies[i]->parent = GalaxyID;
 }
GalaxyID++;

}

void CreatePointMass(Body** bodies, double GalaxyMass, Vect GalaxyPos, Vect GalaxyVel, int Start)
{
	int bodyCount = Start;
	bodies[bodyCount]->m = GalaxyMass;
	bodies[bodyCount]->r += GalaxyPos;
	bodies[bodyCount]->v += GalaxyVel;
	bodies[bodyCount]->parent = GalaxyID;
	GalaxyID++;
}
