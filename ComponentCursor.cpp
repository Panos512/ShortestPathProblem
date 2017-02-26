#include "ComponentCursor.hpp"

ComponentCursor::ComponentCursor(SCC* sccPointer) {
    this->total_components = sccPointer->getCurrentComponentsCount();
    this->component_ptr = (Component*) malloc(sizeof(Component) * this->total_components);
    this->current_component_index = -1;
    
    for(int index = 0; index < sccPointer->getCurrentComponentsCount(); index++) {
        this->component_ptr[index] = sccPointer->getComponentAtIndex(index);
    }
}

void ComponentCursor::setTotalComponents(uint32_t total_components) {
    this->total_components = total_components;
}

int ComponentCursor::getTotalComponents() {
    return this->total_components;
}

Component ComponentCursor::getCurrentComponent() {
    return this->component_ptr[this->current_component_index];
}

bool ComponentCursor::moveComponent() {
    
    this->current_component_index++;
    
    if(this->current_component_index == this->total_components)
        return false;
    else
        return true;
}

