//
//  state.hpp
//  SearchAlgorithm
//
//  Created by Suu on 05/02/2016.
//  Copyright © 2016 suu. All rights reserved.
//

#ifndef state_hpp
#define state_hpp

#include <iostream>
#include <vector>
#include <string>

#define BSIZE 10

using namespace std;

class State
{
public:
    State(vector<uint8_t> *state);
	
	uint8_t removed;
	
    vector<uint8_t> *state;
	int pointer;
    
    int value();
    
    int fitness();
    int heuristic();
    int totalCost();
	
	void printBoard();
};

#endif /* state_hpp */
