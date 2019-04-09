#ifndef WBS_SUCHEA_A1_PRIORITYQUEUE_H
#define WBS_SUCHEA_A1_PRIORITYQUEUE_H

class PriorityQueue;
#include "State.h"
#include <vector>
#include <limits>

class PriorityQueue {
public:
    PriorityQueue();
    State * pop();
    bool updateStateIfBetter(const State &from);
    void addState(State * toAdd);
    bool addStateIfBetter(State * toAdd);
    bool isEmpty() const;
private:
    std::vector<State*> heap;
};


#endif //WBS_SUCHEA_A1_PRIORITYQUEUE_H
