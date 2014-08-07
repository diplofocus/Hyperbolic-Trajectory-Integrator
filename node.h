#ifndef __NODE_H__
#define __NODE_H__

#include <iostream>
#include <fstream>
#include "vect.h"
#include "bodies.h"

extern int NodeCounter;
class Body;

class Node
{
public:
	Vect center;
	bool Contains(Vect r);
	double size;
	Node *ne, *nw, *sw, *se;
	Body *NodeBody;
	int NodeBodyCount;
	Vect centerOfMass;
	double mass;

	Node(Vect _center, double size);
	~Node();
	void InsertToNode(Body *NewBody);
	void ComputeMassDistribution();
	int BHcount();
	int GetQuad(Body *body);
	//double GetSize(Body **bodies);

};

ostream &operator<<(ostream &O, Node &B);
#endif