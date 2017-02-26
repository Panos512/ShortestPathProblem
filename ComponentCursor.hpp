/* 
 * File:   ComponentCursor.hpp
 * Author: nikos
 *
 * Created on December 8, 2016, 9:19 PM
 */

#ifndef COMPONENTCURSOR_HPP
#define	COMPONENTCURSOR_HPP

#define UINT32_T_MAX (0xffffffff)

#include <iostream>
#include "Index.hpp"
#include "Component.hpp"
#include "scc.hpp"

class ComponentCursor {
    private:
        Component* component_ptr;
        int total_components;
        int current_component_index;
    public:
        ComponentCursor(SCC*);
        ~ComponentCursor();
        void setTotalComponents(uint32_t);
        int getTotalComponents();
        Component getCurrentComponent();
        bool moveComponent();
};

#endif	/* COMPONENTCURSOR_HPP */

