/*
 * File:   scc.hpp
 * Author: nikos
 *
 * Created on November 29, 2016, 2:41 AM
 */

#ifndef SCC_HPP
#define	SCC_HPP

#define UINT32_T_MAX (0xffffffff)

#include <iostream>
#include <climits>
#include "stack.hpp"
#include "Index.hpp"
#include "IndexNode.hpp"
#include "Component.hpp"
#include "stack.hpp"

class SCC {
    private:
        Component* components;
        int currentComponentsCount;
        uint32_t currentComponentId;
        int maxComponentsCount;
        bool* visited;
        Stack* stack;
        int time;
        int* lowlink;
        int* disc;
        
    public:
        // Auxiliary functions

        void increaseCurrentComponentsCount();
        int addComponent(Component);
        void setIdToComponent(uint32_t, Component);
        bool SCCisFull();
        void SCCDoubleMaxComponentsCount();
        int getCurrentComponentsCount();
        int getMaxComponentsCount();
        Component getComponentAtIndex(uint32_t);

        ~SCC();
        SCC(int);
        void Tarjan(int, Index*, Index*);
        void dfs(int u, Index*, Index*);
        uint32_t findNodeStronglyConnectedComponentID(uint32_t);
        void iterateStronglyConnectedComponentID();
        int estimateShortestPathStronglyConnectedComponents(Index*, Index*, uint32_t, uint32_t, int);

    uint32_t* id_belongs_to_component;
};

#endif	/* SCC_HPP */
