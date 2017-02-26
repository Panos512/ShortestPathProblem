#ifndef JOB_QUEUE_HPP
#define JOB_QUEUE_HPP

#include <iostream>
#include "Job.hpp"

using namespace std;

struct JobQueueNode {
        Job* job;
        JobQueueNode * next;
    };
    
class JobQueue{
    
    private:
        JobQueueNode* head;
        JobQueueNode* tail;
        size_t size;
       
    public:
        JobQueue();
        ~JobQueue();

        JobQueueNode* getHead();

        Job* popFront();
        void pushBack(Job*);
        void pushFront(Job*);

        void print();
        bool isEmpty();
        uint32_t getQueueSize();
        size_t getSize();
        void appendQueue(JobQueue*);



};


#endif /* JOB_QUEUE_HPP */

