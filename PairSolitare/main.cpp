//
//  main.cpp
//  PairSolitare
//
//  Created by Suu on 12/03/2016.
//  Copyright © 2016 suu. All rights reserved.
//

#include <iostream>
#include "State.hpp"
#include "SearchTree.hpp"
#include "Fringe.hpp"
#include <unordered_set>

using namespace std;

/*
 Spade:		0b000000
 Heart:		0b010000
 Diamond:	0b100000
 Club:		0b110000
 */

#define SP 0b000000+
#define HE 0b010000+
#define DI 0b100000+
#define CL 0b110000+

int heu(vector<uint8_t> state)
{
	int retVal = 0;
	
	if (state.size()<2)
	{
		return 0;
	}
	
	if (state.size()==2 && (((state[0]&0b110000) == (state[1]&0b110000)) || ((state[0]&0xf) == (state[1]&0xf))))
	{
		return 1;
	}
	
	for (vector<uint8_t>::iterator it = state.begin() ; it != state.end()-2; ++it)
	{
		if ((((*it) & 0b110000)>>4) == (((*(it+2)) & 0b110000)>>4))
		{
			retVal ++;
		}
		else if (((*it) & 0xf) == ((*(it+2)) & 0xf))
		{
			retVal ++;
		}
	}
	
	return retVal;
}

class Max
{
public:
	Max(int value, int heu, Max *prev){this->value = value; this->heu = heu; this->prev = prev;}
	~Max(){};
	
	Max *getFinal()
	{
		Max *tmp = this;
		while (tmp->prev)
		{
			if (!tmp->prev->prev)
			{
				break;
			}
			tmp = tmp->prev;
		}
		return tmp;
	}
	
	int value;
	int heu;
	Max *prev;
};

int findBest(vector<uint8_t> state)
{
	int maxIndex = 0;
	int maxNum = 0;
	
	for (vector<uint8_t>::iterator it = state.begin() ; it != state.end()-2; ++it)
	{
		if ((((*it) & 0b110000)>>4) == (((*(it+2)) & 0b110000)>>4))
		{
			vector<uint8_t> tmp = vector<uint8_t>(state);
			tmp.erase(tmp.begin()+distance(state.begin(),it));
			if (maxNum < heu(tmp))
			{
				maxNum = heu(tmp);
				maxIndex = int(distance(state.begin(),it));
			}
			tmp = vector<uint8_t>(state);
			tmp.erase(tmp.begin()+distance(state.begin(),it+2));
			if (maxNum < heu(tmp))
			{
				maxNum = heu(tmp);
				maxIndex = int(distance(state.begin(),it+2));
			}
		}
		else if (((*it) & 0xf) == ((*(it+2)) & 0xf))
		{
			vector<uint8_t> tmp = vector<uint8_t>(state);
			tmp.erase(tmp.begin()+distance(state.begin(),it));
			if (maxNum < heu(tmp))
			{
				maxNum = heu(tmp);
				maxIndex = int(distance(state.begin(),it));
			}
			tmp = vector<uint8_t>(state);
			tmp.erase(tmp.begin()+distance(state.begin(),it+2));
			if (maxNum < heu(tmp))
			{
				maxNum = heu(tmp);
				maxIndex = int(distance(state.begin(),it+2));
			}
		}
	}
	
	return maxIndex;
}

void expandWithMax(vector<Max *> *storage, Max *m, vector<uint8_t> state, int depth)
{
	if (depth == 0)
	{
		storage->push_back(m);
		
		return;
	}
	else if (m->heu == 0 && m->prev)
	{
		delete m;
		
		return ;
	}
	else
	{
		Max *empty = new Max(0, -1, NULL);
		vector<Max *> toExpand = vector<Max *>(4,empty);
		for (vector<uint8_t>::iterator it = state.begin() ; it != state.end()-2; ++it)
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
				vector<uint8_t> tmp = vector<uint8_t>(state);
				tmp.erase(tmp.begin()+distance(state.begin(),it));
				
				if (heu(tmp) > toExpand.at(3)->heu)
				{
					if (toExpand[3]->heu!=-1)
						delete toExpand[3];
					Max *max1 = new Max(int(distance(state.begin(), it)), heu(tmp), m);
					if (heu(tmp) > toExpand.at(2)->heu)
					{
						if (heu(tmp) > toExpand.at(1)->heu)
						{
							if (heu(tmp) > toExpand.at(0)->heu)
							{
								toExpand[3] = toExpand[2];
								toExpand[2] = toExpand[1];
								toExpand[1] = toExpand[0];
								toExpand[0] = max1;
							}
							else
							{
								toExpand[3] = toExpand[2];
								toExpand[2] = toExpand[1];
								toExpand[1] = max1;
							}
						}
						else
						{
							toExpand[3] = toExpand[2];
							toExpand[2] = max1;
						}
					}
					else
					{
						toExpand[3] = max1;
					}
				}
				//expandWithMax(storage, max1, tmp, depth-1);
				
				vector<uint8_t> tmp2 = vector<uint8_t>(state);
				tmp2.erase(tmp2.begin()+distance(state.begin(),it+2));
				if (heu(tmp2) > toExpand.at(3)->heu)
				{
					if (toExpand[3]->heu!=-1)
						delete toExpand[3];
					Max *max1 = new Max(int(distance(state.begin(), it+2)), heu(tmp2), m);
					if (heu(tmp2) > toExpand.at(2)->heu)
					{
						if (heu(tmp2) > toExpand.at(1)->heu)
						{
							if (heu(tmp2) > toExpand.at(0)->heu)
							{
								toExpand[3] = toExpand[2];
								toExpand[2] = toExpand[1];
								toExpand[1] = toExpand[0];
								toExpand[0] = max1;
							}
							else
							{
								toExpand[3] = toExpand[2];
								toExpand[2] = toExpand[1];
								toExpand[1] = max1;
							}
						}
						else
						{
							toExpand[3] = toExpand[2];
							toExpand[2] = max1;
						}
					}
					else
					{
						toExpand[3] = max1;
					}
				}
				
				//expandWithMax(storage, max2, tmp2, depth-1);
			}
		}
		
		for (vector<Max *>::iterator it = toExpand.begin() ; it != toExpand.end(); ++it)
		{
			if ((*it)->heu != -1)
			{
				vector<uint8_t> tmp = vector<uint8_t>(state);
				tmp.erase(tmp.begin()+(*it)->value);
				expandWithMax(storage, *it, tmp, depth-1);
			}
		}
		
		delete empty;
	}
}

int searchWithDepth(vector<uint8_t> state, int depth)
{
	vector<uint8_t> tmp = state;
	Max *decision = new Max(0, 0, NULL);
	
	vector<Max *> *someMax = new vector<Max *>();
	
	int d = depth;
	if (state.size()-1<depth) d = int(state.size())-1;
	while (someMax->size()==0)
	{
		expandWithMax(someMax, decision, state, d);
		d--;
	}
	
	Max *maxMax = someMax->at(0);
	for (vector<Max *>::iterator it = someMax->begin()+1 ; it != someMax->end(); ++it)
	{
		if ((*it)->heu > maxMax->heu)
		{
			maxMax = *it;
		}
	}
	
	int retVal = maxMax->getFinal()->value;
	
	unordered_set<Max *> toDelete = unordered_set<Max *>();
	for (vector<Max *>::iterator it = someMax->begin(); it != someMax->end(); ++it)
	{
		toDelete.insert(*it);
		while ((*it)->prev)
		{
			toDelete.insert((*it)->prev);
			*it = (*it)->prev;
		}
	}
	for (unordered_set<Max *>::iterator it = toDelete.begin(); it != toDelete.end(); ++it)
	{
		delete *it;
	}
	
	delete someMax;
	
	return retVal;

}

void doSearch(State s)
{
	if (s.state->size()==1)
	{
		cout << "Solved" << endl;
		return;
	}
	else if(heu(*s.state) == 0)
	{
		cout << s.state->size() << " left." << endl;
		return;
	}
	else
	{
		int maxIndex = searchWithDepth(*s.state, 5); //Setting search depth here
		
		uint8_t del = s.state->at(maxIndex);
		if (((del & 0b110000)>>4) == 0)
		{
			cout << "♠️";
		}
		else if (((del & 0b110000)>>4) == 1)
		{
			cout << "♥️";
		}
		else if (((del & 0b110000)>>4) == 2)
		{
			cout << "♦️";
		}
		else if (((del & 0b110000)>>4) == 3)
		{
			cout << "♣️";
		}
		cout <<" "<< (del & 0xf)<< endl;
		
		s.state->erase(s.state->begin()+maxIndex);
		
		doSearch(s.state);
	}
}

int main(int argc, const char * argv[])
{
	//uint8_t board[52] = {CL 12,CL 3,HE 5,SP 12,HE 13,SP 9,DI 13,HE 7,DI 12,SP 10,DI 10,DI 4,SP 2,DI 2,HE 3,HE 11,DI 8,DI 9,DI 11,DI 5,HE 9,SP 4,SP 1,CL 2,HE 6,CL 11,SP 8,DI 7,HE 4,DI 3,SP 11,DI 6,HE 10,CL 1,CL 5,CL 10, HE 12, DI 1, SP 3, CL 4, CL 6, SP 6,SP 5, CL 7, SP 7,HE 8, CL 9, SP 13, CL 8, HE 2, HE 1, CL 13};
	//Solved
	
	//uint8_t board[52] = {CL 3, SP 8, DI 3, DI 11, DI 12, DI 7, HE 9, CL 9, CL 10, SP 9, DI 10, HE 10, HE 13, DI 5, DI 2, SP 10, CL 7, HE 12, HE 4, SP 1, CL 2, SP 7, CL 13, DI 1, CL 4, HE 2, HE 5, HE 3, SP 12, SP 2, HE 7, DI 8, DI 9, SP 3, HE 8, HE 1, SP 13, SP 6, CL 8, SP 4, DI 13, CL 1, CL 6, HE 11, SP 5, SP 11, DI 6, CL 12, CL 11, HE 6, CL 5, DI 4};
	//Solved
	
	//uint8_t board[52] = {CL 4, HE 7, CL 5, SP 9, CL 1, DI 13, CL 12, DI 11, CL 3, DI 5, SP 11, SP 12, HE 1, SP 1, SP 3, SP 4, HE 6, HE 10, DI 9, CL 10, SP 13, SP 6, SP 8, CL 2, HE 3, DI 4, HE 2, DI 10, HE 9, DI 1, SP 2, CL 13, CL 9, DI 8, SP 7, CL 8, HE 11, HE 13, DI 3, CL 7, CL 6, DI 7, HE 4, SP 5, DI 2, CL 11, SP 10, DI 12, HE 8, HE 12,DI 5, HE 5};
	
	//uint8_t board[52] = {CL 3, DI 4, HE 4, DI 11, CL 5, DI 13, SP 8, HE 13, HE 8, CL 10, SP 4,DI 6, HE 9, SP 5, SP 13, SP 7, HE 10, HE 7, CL 4, HE 2, SP 6, SP 3, SP 9, DI 7, DI 3, DI 8, SP 12, HE 5, SP 10, CL 8, HE 3, SP 1, HE 1,DI 9, CL 1, HE 11, HE 6, HE 12, CL 6, SP 11, DI 5, CL 11, CL 2, DI 2, CL 9, CL 13, DI 1, CL 12, SP 2, DI 12, CL 7, DI 10};
	
	//uint8_t board[52] = {HE 5, HE 9, HE 10, DI 2, CL 13, SP 1, HE 1, DI 10, HE 2, HE 4, CL 8, SP 7, SP 6, CL 1, SP 2, CL 10, CL 6, DI 9, DI 11, SP 9, DI 12, DI 7, DI 5, SP 8, CL 4, HE 12, HE 6, CL 3, DI 6, HE 3, CL 2, DI 13, DI 4, HE 13, SP 11, HE 11, SP 5, SP 12, DI 8, HE 7, DI 3, CL 5, CL 9, SP 10, HE 8, CL 11, DI 1, SP 13, SP 4, SP 3, CL 12, CL 7};
	
	//uint8_t board[52] = {DI 10, CL 7, DI 11, SP 11, CL 9, DI 4, SP 13, HE 10, SP 7, CL 10, CL 12, SP 6, SP 5, CL 11, HE 5, CL 6, HE 9, SP 1, DI 3, CL 4, CL 5, HE 6, DI 2, HE 12, HE 2, DI 13, DI 8, CL 2, DI 12, SP 4, CL 13, CL 3, SP 10, DI 6, HE 13, HE 11, HE 4, CL 1, SP 3, CL 8, HE 3, HE 1, DI 5, SP 8, DI 9, DI 7, SP 12, DI 1, HE 7, SP 2, SP 9, HE 8};
	//Solved
	
	//uint8_t board[52] = {CL 13, CL 5, CL 10, DI 4, SP 12, DI 11, HE 7, HE 3, SP 6, DI 10, CL 12, SP 5, HE 2, CL 9, HE 1, SP 10, CL 7, CL 6, DI 12, DI 5, CL 11, HE 9, HE 8, HE 12, SP 4, HE 11, HE 10, SP 11, HE 4, HE 13, DI 2, SP 7, SP 2, DI 8, CL 1, CL 3, DI 6, SP 13, SP 3, HE 6, SP 9, DI 3, DI 13, DI 7, SP 1, CL 8, HE 5, DI 1, CL 4, CL 2, DI 9, SP 8};
	//3
	
	uint8_t board[52] = {HE 13, DI 2, SP 6, DI 12, HE 11, DI 5, DI 13, CL 13, SP 9, HE 6, HE 2, HE 9, DI 1, DI 3, HE 7, DI 4, CL 5, CL 9, SP 10, SP 13, SP 2, SP 8, SP 4, SP 5, HE 3, CL 7, SP 3, CL 1, CL 8, CL 2, CL 12, SP 12, DI 7, DI 9, HE 1, CL 11, SP 11, HE 12, HE 10, HE 4, DI 11, DI 8, SP 1, DI 10, HE 5, CL 4, SP 7, HE 8, CL 6, CL 10, CL 3, DI 6};
	
	vector<uint8_t> *question = new vector<uint8_t>(board, board + sizeof(board) / sizeof(uint8_t));
	
	State game = State(question);
	game.printBoard();
	
	doSearch(game);
	/*Fringe *myFringe = new Fringe();
	 
	 SearchTree *tree = new SearchTree(game, myFringe);
	 
	 tree->start();*/
	
	return 0;
}
