#include <iostream>
#include <stdlib.h>
#include "vect.h"
#include "consts.h"
#include "bodies.h"
#include <fstream>

int NodeCounter = 0;

//Contructor
Node::Node(Vect _center, double _size)
{
	center = _center;
	size = _size;// + (_size * 0.1);
	ne = se = sw = nw = NULL;
	NodeCounter++;
}

//Destructor. Deletes each subnode.
Node::~Node()
{
	// if (nw != NULL) delete nw;
	// if (ne != NULL) delete ne;
	// if (se != NULL) delete se;
	// if (sw != NULL) delete sw;
	// if (NodeBody != NULL) delete &NodeBody;
	this->NodeBodyCount = 0;
	NodeBody = NULL;
	NodeCounter--;
	// NodeCounter--;

	// cout << center << endl;

	delete nw;
	delete ne;
	delete se;
	delete sw;
	// delete NodeBody;

}

//Inserts a body in to a Node, as described above each case a body may encounter.
void Node::InsertToNode(Body *NewBody)
{
	//If node has more bodies, check if desired node exists.
	//If it does, InsertToNode there, if not, create 4 subnodes,
	//then insert to desired node.
	if (this->NodeBodyCount > 1)
	{
		// cout << size;
		int asd;
		int quad = GetQuad(NewBody);

		switch (quad)
		{
		case 1 :
		{
			if (ne == NULL)
			{
				Vect neCent;
				neCent.x = center.x + (size / 2.0);
				neCent.y = center.y + (size / 2.0);
				ne = new Node(neCent, (size / 2.0));
			}
			ne->InsertToNode(NewBody);
		} break;

		case 2 :
		{
			if (se == NULL)
			{
				Vect seCent;
				seCent.x = center.x + (size / 2.0);
				seCent.y = center.y - (size / 2.0);
				se = new Node(seCent, (size / 2.0));
			}
			se->InsertToNode(NewBody);
		} break;

		case 3 :
		{
			if (nw == NULL)
			{
				Vect nwCent;
				nwCent.x = center.x - (size / 2.0);
				nwCent.y = center.y + (size / 2.0);
				nw = new Node(nwCent, (size / 2.0));
			}
			nw->InsertToNode(NewBody);
		} break;

		case 4 :
		{
			if (sw == NULL)
			{
				Vect swCent;
				swCent.x = center.x - (size / 2.0);
				swCent.y = center.y - (size / 2.0);
				sw = new Node(swCent, (size / 2.0));
			}
			sw->InsertToNode(NewBody);
		} break;
		}

	}
	else
	{
		// cout << size;
		//If node has one body, find it's new quadrant. If the new quadrant exists, place it there. If it doesn't,
		//create it and place it there.
		//Then take the new body and find it's own quadrant and check if it exists. If it does, place it there,
		//if not, create it and place it there.
		if (this->NodeBodyCount == 1)
		{
			int quad = GetQuad(NodeBody);

			switch (quad)
			{
			case 1 :
			{
				if (ne == NULL)
				{
					Vect neCent;
					neCent.x = center.x + (size / 2.0);
					neCent.y = center.y + (size / 2.0);
					ne = new Node(neCent, (size / 2.0));
					ne->InsertToNode(NodeBody);
				}
				else
				{
					ne->InsertToNode  (NodeBody);
				}
			} break;

			case 2 :
			{
				if (se == NULL)
				{
					Vect seCent;
					seCent.x = center.x + (size / 2.0);
					seCent.y = center.y - (size / 2.0);
					se = new Node(seCent, (size / 2.0));
					se->InsertToNode  (NodeBody);
				}
				else
				{
					se->InsertToNode  (NodeBody);
				}
			} break;

			case 3 :
			{
				if (nw == NULL)
				{
					Vect nwCent;
					nwCent.x = center.x - (size / 2.0);
					nwCent.y = center.y + (size / 2.0);
					nw = new Node(nwCent, (size / 2.0));
					nw->InsertToNode(NodeBody);
				}
				else
				{
					nw->InsertToNode(NodeBody);
				}
			} break;

			case 4 :
			{

				if (sw == NULL)
				{
					Vect swCent;
					swCent.x = center.x - (size / 2.0);
					swCent.y = center.y - (size / 2.0);
					sw = new Node(swCent, (size / 2.0));
					sw->InsertToNode(NodeBody);
				}
				else
				{
					sw->InsertToNode(NodeBody);
				}
			} break;
			}
			quad = GetQuad(NewBody);
			switch (quad)
			{
			case 1 :
			{
				if (ne == NULL)
				{
					Vect neCent;
					neCent.x = center.x + (size / 2.0);
					neCent.y = center.y + (size / 2.0);
					ne = new Node(neCent, (size / 2.0));
				}
				ne->InsertToNode(NewBody);
			} break;

			case 2 :
			{
				if (se == NULL)
				{
					Vect seCent;
					seCent.x = center.x + (size / 2.0);
					seCent.y = center.y - (size / 2.0);
					se = new Node(seCent, (size / 2.0));
				}
				se->InsertToNode(NewBody);
			} break;

			case 3 :
			{
				if (nw == NULL)
				{
					Vect nwCent;
					nwCent.x = center.x - (size / 2.0);
					nwCent.y = center.y + (size / 2.0);
					nw = new Node(nwCent, (size / 2.0));
				}
				nw->InsertToNode(NewBody);
			} break;

			case 4 :
			{
				if (sw == NULL)
				{
					Vect swCent;
					swCent.x = center.x - (size / 2.0);
					swCent.y = center.y - (size / 2.0);
					sw = new Node(swCent, (size / 2.0));
				}
				sw->InsertToNode(NewBody);
			} break;
			}
		}
		//If the node is emtpy, store the new body as the Node Body
		else
		{
			// cout << size;
			NodeBody = NewBody;
		}

	}
	//Increase the number of particles in the node;
	this->NodeBodyCount++;
}


int Node::BHcount()
{
	int num = 0;
	if (ne != NULL)
	{
		num += ne->BHcount();
	}
	if (nw != NULL)
	{
		num += nw->BHcount();
	}
	if (se != NULL)
	{
		num += se->BHcount();
	}
	if (sw != NULL)
	{
		num += sw->BHcount();
	}
	return num;
}


//Returns the quadrant in which the forwarded body belongs.
//Returns number from 1 to 4.
int Node::GetQuad(Body *body)
{
	if (body->r.x > this->center.x)
	{
		if (body->r.y > this->center.y)
		{
			return 1; //NE
		}
		else
		{
			return 2; //SE
		}

	}
	else
	{
		if (body->r.y > this->center.y)
		{
			return 3; //NW
		}
		else
		{
			return 4; //SW
		}
	}
}

void Node::ComputeMassDistribution()
{
	if (this->NodeBodyCount == 1)
	{
		centerOfMass = NodeBody->r;
		mass = NodeBody->m;
	}
	else
	{
		/* code */
	}
}

//Overloaded operator that allows the user to recursively output the center and size of each node and with subnodes.
ostream &operator<<(ostream &O, Node &B)
{
	O << B.center << "\t" << B.size << endl;
	if (B.ne != NULL)
		O << *B.ne;
	if (B.nw != NULL)
		O << *B.nw;
	if (B.sw != NULL)
		O << *B.sw;
	if (B.se != NULL)
		O << *B.se;

	return O;
}

