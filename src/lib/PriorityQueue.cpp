#include "PriorityQueue.h"

/**
 * Creates a priority queue containing the first element
 * @param playground A reference to the playground the states are on to contstruct a dummy state for filling the queue
 * @param firstElement the first element which is copied to the queue
 */
PriorityQueue::PriorityQueue(): heap(std::vector<State*>(1, nullptr)) {}

/**
 * Pops the current highest element from the priority queue removing it from the queue
 * @return A pointer to the element with the smallest fullWeight
 */
State* PriorityQueue::pop() {
    int i = 1;
    std::swap(heap[1], heap.back());
    State * returnValue = heap.back();
    heap.pop_back();
    while(i * 2 < heap.size()) {
        if(heap[i]->getFullWeight() > heap[i*2]->getFullWeight()) {
            std::swap(heap[i], heap[i*2]);
            i *= 2;
            continue;
        }
        if(i * 2 + 1 < heap.size()) {
            if(heap[i]->getFullWeight() > heap[i*2 + 1]->getFullWeight()) {
                std::swap(heap[i], heap[i*2 + 1]);
                i = i * 2 + 1;
                continue;
            }
        }
        break;
    }
}

/**
 * Update the state equal to this one to reflect the shorter distance. This changes the order or the queue
 * @param from The state to update to
 */
bool PriorityQueue::updateState(const State &from) {
    for (unsigned int i = 1; i < heap.size(); i++) {
        if (heap[i]->isSame(from)) {
            from.copyTo(heap[i]);
            while (i > 1) {
                if (heap[i]->getFullWeight() < heap[i / 2]->getFullWeight()) {
                    std::swap(heap[i], heap[i / 2]);
                    i = i / 2;
                } else {
                    break;
                }
            }
            return true;
        }
    }
    return false;
}

/**
 * Adds a state to the priority queue
 * @param toAdd The pointer to the state to add
 */
void PriorityQueue::addState(State * toAdd) {
    this->heap.push_back(toAdd);
    unsigned int i = heap.size() - 1;
    while( i > 1) {
        if(toAdd->getFullWeight() < heap[i/2]->getFullWeight()) {
            std::swap(heap[i], heap[i/2]);
            i = i / 2;
        } else {
            break;
        }
    }
}

/**
 * @return True if the queue is empty
 */
bool PriorityQueue::isEmpty() const {
    return this->heap.size() > 1; // First element is normally size of heap (not used here...)
}



