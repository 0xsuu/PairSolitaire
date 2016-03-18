//
//  Node.hpp
//  SearchAlgorithm
//
//  Created by Suu on 07/02/2016.
//  Copyright © 2016 suu. All rights reserved.
//

#ifndef Node_hpp
#define Node_hpp

#include <stdio.h>
#include "State.hpp"

class Node
{
public:
    State *value;
    
    Node *predecessor;
    std::vector<Node *> *successors;
};

#endif /* Node_hpp */
