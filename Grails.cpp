//
// Created by Panos Paparrigopoulos on 08/12/2016.
//

#include <cstdlib>
#include "Grails.h"
#include "Index.hpp"

Grails::Grails(Index* index, uint32_t size) {
    this->size = size;
    this->index = index;
    this->currentRank = 1;
    nodes = (GrailsNode*) malloc(sizeof(GrailsNode) * size);
    for(uint32_t i=0; i<size; i++){
        nodes[i].setMinRank(-1);
        nodes[i].setRank(-1);
        nodes[i].setVisited(false);
    }

}

void Grails::buildIndex(){
    expandNode(0);
    nodes[0].setRank(this->currentRank);
    this->calculateMinRank(0);
    this->setCurrentRank(this->currentRank + 1);
    for(uint32_t i=0; i<size; i++){
        if(!nodes[i].getVisited()){
            expandNode(i);
            //std::cout << "Return from: " << i << std::endl;
            nodes[i].setRank(this->currentRank);
            this->calculateMinRank(i);
            this->setCurrentRank(this->currentRank + 1);

        }
    }
}

void Grails::calculateMinRank(uint32_t node_id){
    QueueNode* temp2 = index->getNeighborsOfNode(node_id)->getHead();
    if(index->getNeighborsOfNode(node_id)->getSize() == 0){
        nodes[node_id].setMinRank(this->currentRank );
    }
    else{
        uint32_t smallest_rank = nodes[temp2->nodeId].getMinRank();
        while(temp2 != NULL){
            if(nodes[temp2->nodeId].getMinRank() != -1 && nodes[temp2->nodeId].getMinRank() < smallest_rank){
                smallest_rank = nodes[temp2->nodeId].getMinRank();
            }
            temp2 = temp2->next;
        }
        nodes[node_id].setMinRank(smallest_rank);
    }
}

void Grails::expandNode(uint32_t node){
    //std::cout << "Calling for: " << node << std::endl;
    nodes[node].switchVisited();
    Queue* queue = index->getNeighborsOfNode(node);
    QueueNode * temp = queue->getHead();
    while(temp != NULL){
        if(!nodes[temp->nodeId].getVisited()){
            this->expandNode(temp->nodeId);
            //std::cout << "Return from: " << temp->nodeId << std::endl;
            nodes[temp->nodeId].setRank(this->currentRank);

            this->calculateMinRank(temp->nodeId);
            this->setCurrentRank(this->currentRank + 1);
        }
        temp = temp->next;
    }


}

void Grails::DoubleIndex(){
    size = 2*size;
    nodes = (GrailsNode*) realloc(nodes, size * sizeof(GrailsNode));
}

uint32_t Grails::getCurrentRank() {
    return currentRank;
}

void Grails::setCurrentRank(uint32_t rank){
    this->currentRank = rank;
}

bool Grails::isReachableGrailIndex(uint32_t source_node, uint32_t target_node){
    return isSubset(getNodesWithOffset(target_node), getNodesWithOffset(source_node));
}

bool Grails::isSubset(GrailsNode* node1, GrailsNode* node2) {
    return node1->getMinRank() >= node2->getMinRank() && node1->getRank() <= node2->getRank();
}

Grails::~Grails(){
    free(nodes);
}

GrailsNode* Grails::getNodesWithOffset(uint32_t offset){
    return nodes + offset;
}
