//
//  Fringe.cpp
//  SearchAlgorithm
//
//  Created by Suu on 05/02/2016.
//  Copyright © 2016 suu. All rights reserved.
//

#include "Fringe.hpp"

using namespace std;

unsigned long Fringe::leftSucc(unsigned long pos)
{
    return pos*2+1;
}

unsigned long Fringe::rightSucc(unsigned long pos)
{
    return pos*2+2;
}

long long Fringe::predecessor(unsigned long pos)
{
    return pos?(pos-1)/2:-1;
}

Fringe::Fringe()
{
    this->fringeArray = new vector<Node *>();
}

void Fringe::printFringe()
{
    //for (int i = 0; i<fringeArray->size(); i++)
    //{
	unsigned long i = 0;
	i = fringeArray->size()-1;
        cout << this->fringeArray->at(i)->value->fitness() << ": ";
		for (int n = 0; n < fringeArray->at(i)->value->state->size(); n++)
		{
			cout << fringeArray->at(i)->value->state->at(n) << " ";
		}
		cout << endl;
    //}
    //cout << endl;
}

Node *Fringe::expandFirstNode()
{
    //DFS
    //Node *tmp = this->fringeArray->back();
    //fringeArray->pop_back();
    
    Node *tmp = this->fringeArray->front();
    fringeArray->erase(fringeArray->begin());
	
	return tmp;
}

void Fringe::addNode(Node *node)
{
    //BFS
    fringeArray->push_back(node);
    //A*
	
    unsigned long currentPos = fringeArray->size()-1;
    while (predecessor(currentPos)>=0)
    {
        Node *curr = fringeArray->at(currentPos);
        Node *pred = fringeArray->at(predecessor(currentPos));
        if (curr->value->fitness()>=pred->value->fitness())
        {
            iter_swap(curr,pred);
            currentPos = predecessor(currentPos);
        }
        else
        {
            break;
        }
    }
}
