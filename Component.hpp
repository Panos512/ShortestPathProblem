/* 
 * File:   component.hpp
 * Author: nikos
 *
 * Created on November 28, 2016, 1:29 AM
 */

#ifndef COMPONENT_HPP
#define	COMPONENT_HPP

#define UINT32_T_MAX (0xffffffff)

#include <iostream>
#include "Index.hpp"

class Component {
    
    private:
        uint32_t component_id;
        int included_nodes_count;
        uint32_t* included_node_ids;
        int componentSize;
    public:
        Component(uint32_t);
        ~Component();
        void increaseIncludedNodesCount();
        int addIncludedNode(uint32_t);
        uint32_t getComponentId();
        int getIncludedNodeIdAtPosition(int);
        int getComponentSize();
        int getIncludedNodesCount();
        void setComponentSize(int);
        void setIncludedNodesCount(int);
        void doubleComponentSize();
        bool isFullComponent();
        void setComponentId(uint32_t);
};

#endif	/* COMPONENT_HPP */