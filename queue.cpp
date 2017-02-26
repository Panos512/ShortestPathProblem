#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <stdio.h>
#include <sstream>
#include <stdint.h>
#include "queue.hpp"


Queue::Queue(){
    this->head = NULL;
    this->tail = NULL;
    this->size = 0;
   
 }

Queue::~Queue(){
    while(this->head != NULL) {
        QueueNode * node = head->next;
        delete head;
        head = node;
    }
    this->head = NULL;
    this->tail = NULL;
}

uint32_t Queue::popFront(){
    uint32_t returnValue;
    if(this->head != NULL){
        
        QueueNode* temp = this->head;
        
        this->head = this->head->next;
        returnValue = temp->nodeId;  
        delete temp;
        this->size--;

        return returnValue;
    }
}


uint32_t Queue::getIdFront(){
    return this->head->nodeId;
}


uint32_t Queue::getLevelFront(){
    uint32_t returnValue;
    if(this->head != NULL){
        //cout << "epistrefw level gia komvo " << this->head->nodeId << endl;
        return this->head->level;
    }
    else 
        return -1;
}

void Queue::pushBack(uint32_t nodeId){
    QueueNode* newNode = new QueueNode();
    newNode->nodeId = nodeId;
    newNode->next = NULL;
    if(this->head == NULL){
        this->head = newNode;
        this->tail = newNode;
        this->size++;
        
    }else{
        this->tail->next = newNode;
        this->tail = newNode;
        this->size++;
    }
    
}

void Queue::setLevelBack(uint32_t level){
    this->tail->level = level;
}
void Queue::pushFront(uint32_t nodeId){
    QueueNode* newNode = new QueueNode();
    newNode->nodeId = nodeId;
    newNode->next = NULL;
    if(this->head == NULL){
        this->head = newNode;
        this->tail = newNode;
        this->size++;
    }else{ 
        newNode->next = this->head;
        this->head = newNode;
        this->size++;
        
    }
}

void Queue::print(){
    QueueNode * temp = this->head;
    while(temp != NULL){
        cout << temp->nodeId << " ";
        temp = temp->next;
    }
    cout << endl;
}

void Queue::printAsPath(uint32_t targetNodeId){
    while(this->head != NULL){
        if(this->head->nodeId != targetNodeId)
            cout << this->head->nodeId << " -> ";
        else
            cout << this->head->nodeId;
        this->head = this->head->next;
    }
    cout << endl;
}

bool Queue::isEmpty(){
    if(this->head == NULL)
        return true;
    else 
        return false;
}

size_t Queue::getSize(){
    return this->size;
}

uint32_t Queue::getNthNeighbor(uint32_t n){
    while(this->head != NULL){
        if(this->head->nodeId == n)
            return this->head->nodeId;
        //cout << this->head->nodeId << endl;
        this->head = this->head->next;
    }
}

void Queue::appendQueue(Queue* queue){
    this->tail = queue->getHead();
}

QueueNode* Queue::getHead(){
    return this->head;

}

uint32_t Queue::getLevelOf(uint32_t nodeId){
    QueueNode * temp = this->head;
    while(temp != NULL){
        if(temp->nodeId == nodeId)
            return temp->level;
        temp = temp->next;
    }
    return -1;
}


int Queue::getSizeOfLevel(int level){
    QueueNode * temp = this->head;
    int size = 0;
    while(temp != NULL && temp->level == level){
        size++;
        temp = temp->next;
    }
    return size;
}
