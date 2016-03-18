//
//  Fringe.hpp
//  SearchAlgorithm
//
//  Created by Suu on 05/02/2016.
//  Copyright © 2016 suu. All rights reserved.
//

#ifndef Fringe_hpp
#define Fringe_hpp

#include <iostream>
#include <vector>

#include "state.hpp"
#include "Node.hpp"

class Fringe
{
public:
    Fringe();
    
    std::vector<Node *> *fringeArray;
    
    Node *expandFirstNode();
    void addNode(Node *node);
    bool empty(){return fringeArray->size()<1;};
    
    void printFringe();
    
private:
    unsigned long leftSucc(unsigned long pos);
    unsigned long rightSucc(unsigned long pos);
    long long predecessor(unsigned long pos);
};

#endif /* Fringe_hpp */
