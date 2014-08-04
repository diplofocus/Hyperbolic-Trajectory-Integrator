#ifndef __GALAXY_H__
#define __GALAXY_H__

class Body;

void CreateGalaxy(Body** B, double GalaxyMass, Vect GalaxyPos, Vect GalaxyVel, double Scale, int Direction, int Start);
void CreatePointMass(Body** B, double GalaxyMass, Vect GalaxyPos, Vect GalaxyVel, int Start);

#endif
