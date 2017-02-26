#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <iostream>

using namespace std;

struct QueueNode {
        uint32_t nodeId;
        uint32_t level;
        QueueNode * next;
    };
    
class Queue{
    
    private:
        QueueNode* head;
        QueueNode* tail;
        size_t size;
       
    public:
        Queue();
        ~Queue();
        uint32_t popFront();
        void pushBack(uint32_t);
        void pushFront(uint32_t);
        void print();
        void printAsPath(uint32_t);
        bool isEmpty();
        uint32_t getQueueSize();
        size_t getSize();
        uint32_t getNthNeighbor(uint32_t);
        void appendQueue(Queue*);

        uint32_t getIdFront();
        



        uint32_t getLevelFront();
        void setLevelBack(uint32_t);
        uint32_t getLevelOf(uint32_t);

        QueueNode* getHead();
        
        int getSizeOfLevel(int);
};


#endif /* QUEUE_HPP */

