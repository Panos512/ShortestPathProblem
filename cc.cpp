#include "cc.hpp"
#include "queue.hpp"
#include "ArrayQueue.hpp"

CC::CC(uint32_t graphSize){
    this->graphSize = graphSize;
    this->ccCounter = 0;

    this->updateIndexSize = 0;


    this->ccindex = (uint32_t*) malloc(sizeof(uint32_t)*graphSize);

    this->visited = (int*) malloc(sizeof(int)*graphSize);

    for(int i = 0; i < graphSize; i++){
        this->ccindex[i] = UINT32_T_MAX;
        this->visited[i] = -1;
    }

    this->updateIndex = NULL;

    this->queue = new ArrayQueue(graphSize);
    this->neighbors =  new ArrayQueue(graphSize);
    this->neighbors2 = new ArrayQueue(graphSize);
}
CC::~CC(){

    //delete this->updateIndex;
    free(this->ccindex);
    free(this->visited);
    free(this->updateIndex);
    delete this->queue;
    delete this->neighbors;
    delete this->neighbors2;

}

void CC::print(){
    for(int i = 0; i < this->graphSize; i++){
        cout << i << " -> " << this->ccindex[i] << endl;
    }
    if(this->updateIndex != NULL)
    for(int i = 0; i < this->ccCounter; i++){
        cout << i << " -> " << this->updateIndex[i] << endl;
    }
}

void CC::insert(uint32_t nodeId, uint32_t componentId){
    this->ccindex[nodeId] = componentId;
}

bool CC::inComponent(uint32_t nodeId){
    if(this->ccindex[nodeId] == UINT32_T_MAX)
        return false;
    else
        return true;
}

void CC::findCC(Index* indexExternal, Index* indexInternal, uint32_t nodeId, uint32_t ccId){
    uint32_t version = ccId;

    this->queue->Reset();
    queue->Enqueue(nodeId);
    visited[nodeId] = version;
    while(!queue->IsEmpty()){
        nodeId = queue->Dequeue();
        this->ccindex[nodeId] = ccId;
        neighbors->Reset();
        indexExternal->getNeighborsOfNode(neighbors, nodeId);
        neighbors2->Reset();
        indexInternal->getNeighborsOfNode(neighbors2, nodeId);


        while(!neighbors->IsEmpty()){
            uint32_t neighbor = neighbors->Dequeue();

            if(visited[neighbor] != version){
                queue->Enqueue(neighbor);

                visited[neighbor] = version;
            }
        }

         while(!neighbors2->IsEmpty()){
            uint32_t neighbor = neighbors2->Dequeue();
            if(visited[neighbor] != version){
                queue->Enqueue(neighbor);

                visited[neighbor] = version;

            }
        }

    }



}

void CC::findCCAll(Index* indexInternal, Index* indexExternal){
    uint32_t ccCounter = 0;

    this->ccCounter = 0;
    for(int i = 0; i < this->graphSize; i++){

        if(indexExternal->isAllocated(i) && !inComponent(i)){

            findCC(indexExternal, indexInternal, i, ccCounter);
            this->ccCounter = ccCounter;

            ccCounter++;
        }
    }
    this->ccCounter = ccCounter;

}
int CC::insertNewEdge(uint32_t nodeIdS, uint32_t nodeIdT, uint32_t version){

    while(nodeIdS > this->graphSize || nodeIdT > this->graphSize){

        uint32_t oldSize = this->graphSize;
        uint32_t newSize = this->graphSize * 2;
        this->ccindex = (uint32_t*) realloc(this->ccindex, newSize * sizeof(uint32_t));
        for(int i = oldSize; i < newSize; i ++){
            this->ccindex[i] = UINT32_T_MAX;
        }

        this->graphSize = newSize;
    }
    if(!inComponent(nodeIdS) && !inComponent(nodeIdT)){
      this->ccindex[nodeIdS] = this->ccCounter;
      this->ccindex[nodeIdT] = this->ccCounter;
      if(this->ccCounter  >= this->updateIndexSize){
        uint32_t oldSize = this->updateIndexSize;
        uint32_t newSize = this->updateIndexSize * 2;
        this->updateIndex = (uint32_t*) realloc(this->updateIndex, newSize * sizeof(uint32_t));
        for(int i = oldSize; i < newSize; i++){
          this->updateIndex[i] = UINT32_T_MAX;
        }
        this->updateIndexSize = newSize;

      }
      this->ccCounter++;

      return 1;
    }

    if(inComponent(nodeIdS) && !inComponent(nodeIdT)){
      this->ccindex[nodeIdT] = this->ccindex[nodeIdS];
      return 1;
    }

    if(!inComponent(nodeIdS) && inComponent(nodeIdT)){
      this->ccindex[nodeIdS] = this->ccindex[nodeIdT];
      return 1;
    }

    if(inComponent(nodeIdS) && inComponent(nodeIdT)){
        uint32_t componentS = this->ccindex[nodeIdS];
        uint32_t componentT = this->ccindex[nodeIdT];

        if(this->updateIndex[componentS] == UINT32_T_MAX && this->updateIndex[componentT] == UINT32_T_MAX){
            this->updateIndex[componentS] = version;
            this->updateIndex[componentT] = version;



        }else if(this->updateIndex[componentS] != UINT32_T_MAX && this->updateIndex[componentT] == UINT32_T_MAX){
            uint32_t toUpdate1 = this->updateIndex[componentS];

            for(int i = 0 ; i < ccCounter; i++){
                if(this->updateIndex[i] == toUpdate1){
                    this->updateIndex[i] = version;
                }

            }
            this->updateIndex[componentT] = version;

        }else if(this->updateIndex[componentS] == UINT32_T_MAX && this->updateIndex[componentT] != UINT32_T_MAX){
            uint32_t toUpdate1 = this->updateIndex[componentT];


            for(int i = 0 ; i < ccCounter; i++){
                if(this->updateIndex[i] == toUpdate1){
                    this->updateIndex[i] = version;
                }

            }
            this->updateIndex[componentS] = version;
        }else if(this->updateIndex[componentS] != UINT32_T_MAX && this->updateIndex[componentT] != UINT32_T_MAX){
            if(this->updateIndex[componentS] == this->updateIndex[componentT])
                return 0;
            uint32_t toUpdate1 = this->updateIndex[componentS];
            uint32_t toUpdate2 = this->updateIndex[componentT];
            for(int i = 0 ; i < ccCounter; i++){
                if(this->updateIndex[i] == toUpdate1 || this->updateIndex[i] == toUpdate2){
                    this->updateIndex[i] = version;
                }

            }

        }



        return 1;



    }

}
uint32_t CC::getCcCounter(){
    return this->ccCounter;
}

bool CC::sameComponent(uint32_t nodeS, uint32_t nodeT){
    if(this->ccindex[nodeS] == this->ccindex[nodeT])
        return true;
    else{

        uint32_t compS = this->ccindex[nodeS];
        uint32_t compT = this->ccindex[nodeT];
        if(this->updateIndex[compS] == this->updateIndex[compT])
            return true;
        else return false;
    }

}

void CC::setUpdateIndex(){
    this->updateIndex = (uint32_t*) malloc(sizeof(uint32_t)*ccCounter);
    for(int i = 0 ; i < ccCounter; i++)
        this->updateIndex[i] = UINT32_T_MAX;

    this->updateIndexSize = this->ccCounter;
}
