//
// Created by Panos Paparrigopoulos on 08/12/2016.
//

#ifndef SHORTESTPATHPROBLEM_SOFTDEV2017_GRAILSNODE_H
#define SHORTESTPATHPROBLEM_SOFTDEV2017_GRAILSNODE_H


#include <cstdint>

class GrailsNode {
private:
    uint32_t min_rank;
    uint32_t rank;
    bool visited;
public:

    GrailsNode();
    ~GrailsNode();

    uint32_t getMinRank();
    void setMinRank(uint32_t);

    uint32_t getRank();
    void setRank(uint32_t);

    bool getVisited();
    void setVisited(bool);
    void switchVisited();

};


#endif //SHORTESTPATHPROBLEM_SOFTDEV2017_GRAILSNODE_H
