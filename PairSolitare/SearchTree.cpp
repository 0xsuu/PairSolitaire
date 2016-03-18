//
//  SearchTree.cpp
//  SearchAlgorithm
//
//  Created by Suu on 06/02/2016.
//  Copyright © 2016 suu. All rights reserved.
//

#include "SearchTree.hpp"
#include "State.hpp"

using namespace std;

SearchTree::SearchTree(State *initialState, Fringe *myFringe)
{
    this->rootNode = new Node;
    this->rootNode->value = initialState;
	this->rootNode->predecessor = NULL;
    this->rootNode->successors = new vector<Node *>();
    this->myFringe = myFringe;
    expandedState = new vector<State *>;
}

int countE=0;
void SearchTree::expandNode(Node *expandNode)
{
    /*for (int i = 0; i < expandedState->size(); i++)
    {
        if (expandedState->at(i)->sameState(expandNode->value))
        {
            return;
        }
    }
    expandedState->push_back(expandNode->value);*/
    
    //cout << "Expanding node: " << expandNode->value->getExpresstion() << endl;
    //cout << "Expanding node: " << expandNode->value->value() << " with f()=" << expandNode->value->fitness() << " with fringe: ";
    countE++;
	
	for (vector<uint8_t>::iterator it = expandNode->value->state->begin() ; it != expandNode->value->state->end()-2; ++it)
	{
		bool expand = false;
		if ((((*it) & 0b110000)>>4) == (((*(it+2)) & 0b110000)>>4))
		{
			expand = true;
		}
		else if (((*it) & 0xf) == ((*(it+2)) & 0xf))
		{
			expand = true;
		}
		
		if (expand)
		{			
			Node *expNode = new Node();
			vector<uint8_t> *expVec = new vector<uint8_t>(*expandNode->value->state);
			long a = distance(expandNode->value->state->begin(),it);
			expVec->erase(expVec->begin()+a);
			State *expState = new State(expVec);
			expState->removed = *it;
			expState->state = expVec;
			expNode->value = expState;
			expNode->predecessor = expandNode;
			this->myFringe->addNode(expNode);
		}
	}
}

void SearchTree::printTree(int count, Node *startNode)
{
    for (int i = 0; i < count; i++)
    {
        cout << "    ";
    }
    cout << startNode->value->state << "=" << startNode->value->value() << endl;
    count++;
    for (int i = 0; i < startNode->successors->size(); i++)
    {
        this->printTree(count, startNode->successors->at(i));
    }
}





void SearchTree::start()
{
    myFringe->addNode(rootNode);
	
	int currentBest = 53;
    while (!myFringe->empty())
    {
        Node *expand = myFringe->expandFirstNode();

		if (expand->value->totalCost()==52)
		{
			cout << "Found, tried: " << countE << " times" << endl;
			exit(0);
		}
		else if (expand->value->heuristic()==0)
		{
			if (52-expand->value->totalCost()<currentBest)
			{
				currentBest = 52-expand->value->totalCost();
				cout << "Got one path, " << 52-expand->value->totalCost() << " left." << endl;
				while (expand->predecessor)
				{
					if (((expand->value->removed&0b110000)>>4) == 0)
					{
						cout << "♠️";
					}
					else if (((expand->value->removed&0b110000)>>4) == 1)
					{
						cout << "♥️";
					}
					else if (((expand->value->removed&0b110000)>>4) == 2)
					{
						cout << "♦️";
					}
					else if (((expand->value->removed&0b110000)>>4) == 3)
					{
						cout << "♣️";
					}
					cout << " " << (expand->value->removed&0xf) << endl;
					expand=expand->predecessor;
				}
			}
		}
		
        expandNode(expand);
        //myFringe->printFringe();
    }
    //this->printTree(0, this->rootNode);
    cout << "Didn't find, tried: " << countE << " times" << endl;
}
