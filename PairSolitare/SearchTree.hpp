//
//  SearchTree.hpp
//  SearchAlgorithm
//
//  Created by Suu on 06/02/2016.
//  Copyright © 2016 suu. All rights reserved.
//

#ifndef SearchTree_hpp
#define SearchTree_hpp

#include <iostream>
#include <vector>

#include "State.hpp"
#include "Fringe.hpp"
#include "Node.hpp"

class SearchTree
{
public:
    SearchTree(State *initialState, Fringe *myFringe);
    
    void start();
    
private:
    Node *rootNode;
    
    Fringe *myFringe;
    
    void expandNode(Node *expandNode);
    
    void printTree(int count, Node *startNode);
    
    vector<State *> *expandedState;
    
};

#endif /* SearchTree_hpp */
