#include "State.h"

/**
 * Construct a valid state object
 * @param playground Reference to the playground this state was generated on
 * @param x Coordinate
 * @param y Coordinate
 * @param artifacts Bitmask representing which artifacts are picked up already
 * @param g Movement cost already taken to get into this state
 */
State::State(const Playground &playground, unsigned int x, unsigned int y, char artifacts, unsigned int g) : playground(playground), x(x), y(y), artifacts(artifacts), g(g) {}

/**
 * Get the one D coordinate of this artifact
 * @param width The width of the playground
 * @return unsigned integer index
 */
unsigned int State::getPositionInOneD(unsigned int len) const{
    return tdtod(x, y, len);
}

/**
 * Determine if this is a terminating state (All artifacts are picked up
 * @return true if it is a terminating state
 */
bool State::isFinalState() const {
    return (this->artifacts & ARTIFACT_BYTE_MASK) == ARTIFACT_BYTE_MASK;
}

/**
 * Get the full weight of this State including the path lenght already taken and the estimation till a final state is reached
 * @return The estimated full path length till reaching the goal
 */
unsigned int State::getFullWeight() {
    if(!this->fetchedH) {
        h = this->playground.getEstimate(x, y, artifacts);
        this->fetchedH = true;
    }
    return g + h;
}

