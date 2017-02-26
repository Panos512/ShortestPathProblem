#ifndef CC_HPP
#define CC_HPP

#define UINT32_T_MAX (0xffffffff)
#include <iostream>
#include "Index.hpp"
#include "ArrayQueue.hpp"
using namespace std;

class CC{
    private:
        uint32_t* ccindex;
        uint32_t* updateIndex;
        uint32_t metricVal;
        uint32_t graphSize;
        uint32_t ccCounter;
        uint32_t updateIndexSize;
        ArrayQueue* queue;
        ArrayQueue* neighbors;
        ArrayQueue* neighbors2;

        int* visited;
    public:
        CC(uint32_t);
        ~CC();
        void setUpdateIndex();
        void print();
        void insert(uint32_t, uint32_t);
        bool inComponent(uint32_t);
        void findCC(Index*, Index*, uint32_t, uint32_t);
        void findCCAll(Index* , Index* );
        int insertNewEdge(uint32_t, uint32_t, uint32_t);
        uint32_t getCcCounter();
        bool sameComponent(uint32_t , uint32_t );

};


#endif /* CC_HPP */
