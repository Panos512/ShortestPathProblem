//
// Created by Panos Paparrigopoulos on 08/12/2016.
//

#ifndef SHORTESTPATHPROBLEM_SOFTDEV2017_GRAILS_H
#define SHORTESTPATHPROBLEM_SOFTDEV2017_GRAILS_H


#include "GrailsNode.h"
#include "Index.hpp"

class Grails {
private:
    Index* index;
    GrailsNode* nodes;
    uint32_t size;
    uint32_t currentRank;
  
public:
    Grails(Index* index, uint32_t size);
    ~Grails();
    void expandNode(uint32_t);
    void buildIndex();
    void DoubleIndex();
    GrailsNode* getNodesWithOffset(uint32_t);
    uint32_t getCurrentRank();

    bool isReachableGrailIndex(uint32_t, uint32_t);
    bool isSubset(GrailsNode*, GrailsNode*);

    void calculateMinRank(uint32_t);
    void setCurrentRank(uint32_t);
};


#endif //SHORTESTPATHPROBLEM_SOFTDEV2017_GRAILS_H
