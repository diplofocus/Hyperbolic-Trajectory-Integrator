#include <iostream>
#include <math.h>
#include <fstream>

#include "vect.h"
#include "consts.h"
#include "kepcart.h"
#include "galaxy.h"
#include "bodies.h"

Body** GetMassiveBodies(Body** B)
{
  int bodyCount = GetMassiveBodyCount(B);

  Body** massiveBodies = new Body*[bodyCount];
  bodyCount = 0;
  
  for(int i = 0; i < elements; i++)
    {
      if(B[i]->IsMassive())
	{
	  massiveBodies[bodyCount++] = B[i];
	}
    }

  return massiveBodies;
}

int GetMassiveBodyCount(Body** B)
{
  int bodyCount = 0;
  Body* MassiveBodies;
  for(int i = 0; i < elements; i++ )
    {
      if(B[i]->IsMassive())
	bodyCount++;
    }

  return bodyCount;
}

ostream& operator<<(ostream& O, Body& B)
{
  O << B.r.x << "\t" << B.r.y << "\t" << B.parent;
  return O;
}
