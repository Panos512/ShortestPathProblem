//
// Created by Panos Paparrigopoulos on 08/12/2016.
//

#include "GrailsNode.h"

GrailsNode::GrailsNode(){
    min_rank = -1;
    rank = -1;
    visited = false;

}

uint32_t GrailsNode::getMinRank(){
    return min_rank;
}

void GrailsNode::setMinRank(uint32_t min_rank){
    this->min_rank = min_rank;
};

uint32_t GrailsNode::getRank(){
    return rank;
}

void GrailsNode::setRank(uint32_t rank){
    this->rank = rank;
};

bool GrailsNode::getVisited(){
    return visited;
}

void GrailsNode::setVisited(bool visited){
    this->visited = visited;
}

void GrailsNode::switchVisited(){
    visited = !visited;
}