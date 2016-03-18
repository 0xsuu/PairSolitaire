//
//  state.cpp
//  SearchAlgorithm
//
//  Created by Suu on 05/02/2016.
//  Copyright © 2016 suu. All rights reserved.
//

#include "State.hpp"

using namespace std;


State::State(vector<uint8_t> *state)
{
    this->state = state;
}

int State::value()
{
	return this->fitness();
}



int State::fitness()
{
    return this->totalCost()*52+(52-this->heuristic())*10;
}

int State::heuristic()
{
	int retVal = 0;
	
	for (vector<uint8_t>::iterator it = state->begin() ; it != state->end()-2; ++it)
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

int State::totalCost()
{
    //return (int)this->getExpresstion().length()/2;
    return 52-int(state->size());
}


void State::printBoard()
{
	int a = 0;
	int b = 0;
	int c = 0;
	int d = 0;
	
	int num[13];
	for (int i = 1; i < 14; i ++)
	{
		num[i] = 0;
	}
	
	for (vector<uint8_t>::iterator it = state->begin(); it != state->end(); ++it)
	{
		num[(*it)&0xf] ++;
		if ((((*it) & 0b110000)>>4) == 0)
		{
			a ++;
			//cout << "♠️";
		}
		else if ((((*it) & 0b110000)>>4) == 1)
		{
			b ++;
			//cout << "♥️";
		}
		else if ((((*it) & 0b110000)>>4) == 2)
		{
			c ++;
			//cout << "♦️";
		}
		else if ((((*it) & 0b110000)>>4) == 3)
		{
			d ++;
			//cout << "♣️";
		}
		//cout <<" "<< ((*it) & 0xf)<< endl;
	}
	//cout << a << " " << b << " " << c << " " << d << endl;
	if (a!=13 || b!=13 || c!=13 || d!=13)
	{
		cout << "Error" << endl;
		cout << a << " " << b << " " << c << " " << d << endl;
		exit(0);
	}
	
	for (int i = 1; i < 14; i++)
	{
		if (num[i] != 4)
		{
			cout << "Number error: " << i << " has " << num[i] << endl;
			exit(0);
		}
	}
}
