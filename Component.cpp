#include "Component.hpp"

Component::Component(uint32_t componentId) {
    this->component_id = componentId;
    this->setComponentSize(1);
    this->included_nodes_count = 0;
    this->included_node_ids = (uint32_t*) malloc(sizeof(uint32_t) * this->getComponentSize());
    for(int i = 0; i < this->getComponentSize(); i++){
        this->included_node_ids[i] = UINT32_T_MAX;
    }
}

Component::~Component() {
    
}

int Component::getIncludedNodesCount() {
    return this->included_nodes_count;
}

void Component::increaseIncludedNodesCount() {
    this->included_nodes_count++;
}

int Component::addIncludedNode(uint32_t nodeId) {
    
    if(this->included_nodes_count == 0) {
        this->included_node_ids = (uint32_t*) malloc(sizeof(uint32_t));
    }
    
    if(this->isFullComponent()) {
        // if the component is full
        // reallocate it to its double size
        if((this->included_node_ids = (uint32_t*) realloc(this->included_node_ids, sizeof(uint32_t) * this->getComponentSize() * 2)) != NULL){
             
            // set the size variable to its double value
            this->doubleComponentSize();
            
            // add the node to the included nodes array (because we start from zero,
            // we can safely add it to the included_nodes_count position)
            this->included_node_ids[this->included_nodes_count] = nodeId;
            
            // we finally augment the count
            this->increaseIncludedNodesCount();
             
        } else {
            return -1;
        }
    } else {
        // no need to double the size
        // hence, just add it
    
        this->included_node_ids[this->included_nodes_count] = nodeId;
        
        // we finally augment the count
        this->increaseIncludedNodesCount();
    }
}

bool Component::isFullComponent() {
    return this->included_nodes_count == this->getComponentSize();
}

uint32_t Component::getComponentId() {
    return this->component_id;
}

 int Component::getIncludedNodeIdAtPosition(int position) {
     return this->included_node_ids[position];
 }
 
 void Component::setComponentSize(int newSize) {
     this->componentSize = newSize;
 }
 
 int Component::getComponentSize() {
     return this->componentSize;
 }
 
 void Component::doubleComponentSize() {
     this->componentSize *= 2;
 }
 
 void Component::setIncludedNodesCount(int nodesCount) {
    this->included_nodes_count = nodesCount;
}
 
 void Component::setComponentId(uint32_t componentId) {
     this->component_id = componentId;
 }
