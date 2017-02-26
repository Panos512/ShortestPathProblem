#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <stdio.h>
#include <sstream>
#include <stdint.h>
#include "JobQueue.hpp"


JobQueue::JobQueue(){
    this->head = NULL;
    this->tail = NULL;
    this->size = 0;
   
 }

JobQueue::~JobQueue(){
    while(this->head != NULL) {
        JobQueueNode * node = head->next;
        delete head->job;
        delete head;
        head = node;
    }
    this->head = NULL;
    this->tail = NULL;
}

Job* JobQueue::popFront(){
    Job* returnValue;
    if(this->head != NULL){

        JobQueueNode* temp = this->head;
        
        this->head = this->head->next;
        returnValue = temp->job;
        delete temp;
        this->size--;

        return returnValue;
    }
}


void JobQueue::pushBack(Job* job){
    JobQueueNode* newNode = new JobQueueNode();
    newNode->job = job;
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


void JobQueue::pushFront(Job* job){
    JobQueueNode* newNode = new JobQueueNode();
    newNode->job = job;
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

void JobQueue::print(){
    JobQueueNode * temp = this->head;
    while(temp != NULL){
        cout << temp->job->getType() << " " << temp->job->getNodeFrom() << " " << temp->job->getNodeTo() << endl;
        temp = temp->next;
    }
}


bool JobQueue::isEmpty(){
    if(this->head == NULL)
        return true;
    else 
        return false;
}

size_t JobQueue::getSize(){
    return this->size;
}


void JobQueue::appendQueue(JobQueue* queue){
    this->tail = queue->getHead();
}

JobQueueNode* JobQueue::getHead(){
    return this->head;

}

