#ifndef __BODIES_H__
#define __BODIES_H__

#include <iostream>

class Body
{
public:
  Vect r,r1,r2,r3,r4;
  Vect v,v1,v2,v3,v4;
  Vect a,a1,a2,a3,a4;
  double m;
  int parent;
  
  Body()
  {
    m = 0;
  }

  bool IsMassive()
  {
    return m > 0;
  }

};

Body** GetMassiveBodies(Body** B);
int GetMassiveBodyCount(Body** B);
ostream& operator<<(ostream& O, Body& B);

#endif

