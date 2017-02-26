#include "scc.hpp"
#include "ComponentCursor.hpp"
#include "bfs.hpp"


// This function is the equivalent to destroyStronglyConnectedComponents
SCC::~SCC() {
    free(this->components);
    free(this->id_belongs_to_component);
    delete this->stack;
    delete[] this->visited;
    delete[] this->lowlink;
    delete[] this->disc;
}

/* This function is the equivalent to estimateStronglyConnectedComponents
 *
 * The input is a graph, the strongly connected components of which we
 * need to find (it is basically an implementation of the Tarjan algorithm). */
SCC::SCC(int graphSize) {

    // First, initialize the SCC structure
    this->currentComponentsCount = 0;
    this->currentComponentId = 0;
    this->maxComponentsCount = 1;
    this->components = (Component*) malloc(sizeof(Component));
    this->id_belongs_to_component = (uint32_t*) malloc(sizeof(uint32_t) * graphSize);
    for(int i = 0; i < graphSize; i++) {
        this->id_belongs_to_component[i] = UINT32_MAX;
    }
}

void SCC::Tarjan(int graphSize, Index* indexExternal, Index* indexInternal) {

    int V = graphSize;
    this->disc = new int[V];
    this->lowlink = new int[V];
    this->visited = new bool[V];
    this->stack = new Stack(V);

    for(int i = 0; i < V; i++) {
        this->lowlink[i] = -1;
        this->disc[i] = -1;
        this->visited[i] = false;
    }

    for(int i = 0; i < V; i++) {
        if(disc[i] == -1)
            this->dfs(i, indexExternal, indexInternal);
    }


}

void SCC::dfs(int u, Index* indexExternal, Index* indexInternal) {


    Queue* neighborsExt = indexInternal->getNeighborsOfNode(u);
    //neighborsExt->appendQueue(indexInternal->getNeighborsOfNode(u));

    static int time = 0;

    this->disc[u] = time;
    this->lowlink[u] = time;
    time++;
    this->stack->push(u);
    this->visited[u] = true;



    while(! (neighborsExt->isEmpty()) ) {
        uint32_t v = neighborsExt->popFront();

        if(this->disc[v] == -1) {
            dfs(v, indexExternal, indexInternal);

            this->lowlink[u] = min(this->lowlink[u], this->lowlink[v]);
        }

        else if(this->visited[v] == true)
            this->lowlink[u] = min(this->lowlink[u], this->disc[v]);
    }

    if(this->lowlink[u] == this->disc[u]) {
        uint32_t w = UINT32_MAX;

        this->components =  (Component*) realloc(this->components, sizeof(Component) * (this->currentComponentsCount + 1));

        this->components[this->currentComponentsCount].setComponentId(this->currentComponentId);
        this->components[this->currentComponentsCount].setIncludedNodesCount(0);
        this->components[this->currentComponentsCount].setComponentSize(1);
        //std::cout << "Found component" << std::endl;
        //std::cout << "Its nodes are:" << std::endl;
        do {
            w = this->stack->peek();
            this->components[this->currentComponentsCount].addIncludedNode(w);
            //std::cout << w << std::endl;
            //this->setIdToComponent(w, this->components[this->currentComponentsCount]);
            this->id_belongs_to_component[w] = this->currentComponentId;
            this->visited[w] = false;
            this->stack->pop();

        }while(w != u);
        this->currentComponentsCount++;
        this->currentComponentId++;
    }

    delete neighborsExt;
}

/* This function initializes the cursor object ComponentCursor of the SCC
 * structure appropriately */
void SCC::iterateStronglyConnectedComponentID() {
    ComponentCursor* cursor = new ComponentCursor(this);
    while(cursor->moveComponent()) {
        std::cout << "Found component with ID: " << cursor->getCurrentComponent().getComponentId() << std::endl;
        std::cout << "Its nodes are:" << std::endl;
        for(int i = 0; i < cursor->getCurrentComponent().getIncludedNodesCount(); i++) {
            std::cout << cursor->getCurrentComponent().getIncludedNodeIdAtPosition(i) << std::endl;
        }
    }

    for(int i = 0; i < 11; i++) {
        std::cout <<  "The id of node " << i << "is: " << this->id_belongs_to_component[i] << std::endl;
    }
}

/* This function estimates the shortest path between two nodes belonging to
 * the same strongly connected component. It returns the shortest path, or -1
 * if the nodes are not in the same component. The paths must be pruned accordingly
 * because we need to extend only the paths that exist in the same strongly
 * connected component. */
int SCC::estimateShortestPathStronglyConnectedComponents(Index* indexInternal, Index* indexExternal, uint32_t sourceNode, uint32_t targetNode, int version) {
    if(this->id_belongs_to_component[sourceNode] == this->id_belongs_to_component[targetNode]) {
        BFS* bfs = new BFS(2700000);
        return bfs->findShortestPath(indexInternal, indexExternal, sourceNode, targetNode, version, 0);
    }
    else
        return -1;
}

uint32_t SCC::findNodeStronglyConnectedComponentID(uint32_t nodeId) {
    // This function returns the component to which
    // the node specified by nodeId belongs.

    return this->id_belongs_to_component[nodeId];
}

void SCC::increaseCurrentComponentsCount() {
    this->currentComponentsCount++;
}

int SCC::getCurrentComponentsCount() {
    return this->currentComponentsCount;
}

void SCC::SCCDoubleMaxComponentsCount() {
    this->maxComponentsCount *=2;
}

int SCC::getMaxComponentsCount() {
    return this->maxComponentsCount;
}

int SCC::addComponent(Component c) {
    if(this->SCCisFull()) {
        // if the component is full
        // reallocate it to its double size
        if((this->components = (Component*) realloc(this->components, sizeof(Component) * this->maxComponentsCount * 2)) != NULL){

            // set the size variable to its double value
            this->SCCDoubleMaxComponentsCount();

            // add the node to the included nodes array (because we start from zero,
            // we can safely add it to the included_nodes_count position)
            this->components[this->currentComponentsCount] = c;

            // we finally augment the count
            this->increaseCurrentComponentsCount();

        } else {
            return -1;
        }
    } else {
        // no need to double the size
        // hence, just add it
        this->components[this->currentComponentsCount] = c;

        // we finally augment the count
        this->increaseCurrentComponentsCount();

        return 0;
    }
}

void SCC::setIdToComponent(uint32_t nodeId, Component c) {
    // This function sets the nodeId to Component c
    // both in the SCC structure and the equivalent
    // Component structure.
    this->id_belongs_to_component[nodeId] = c.getComponentId();

}

bool SCC::SCCisFull() {
    return this->maxComponentsCount == this->currentComponentsCount;
}

Component SCC::getComponentAtIndex(uint32_t index) {
    return this->components[index];
}
