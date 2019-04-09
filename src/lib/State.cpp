#include "State.h"

State::State(){
    this->playground = nullptr;
    this->x = -1;
    this->y = -1;
    this->artifacts = static_cast<char>(0xff);
    this->xPrev = -1;
    this->yPrev = -1;
    this->artifactsPrev = static_cast<char>(0xff);
    this->g = -1;
}

/**
 * Construct a valid state object
 * @param playground Reference to the playground this state was generated on
 * @param x Coordinate
 * @param y Coordinate
 * @param artifacts Bitmask representing which artifacts are picked up already
 * @param g Movement cost already taken to get into this state
 */
State::State(const Playground &playground, int x, int y, char artifacts, int g): State(playground, x, y, artifacts, g, -1, -1, static_cast<char>(0xff)) {}

/**
 * Construct a valid state object
 * @param playground Reference to the playground this state was generated on
 * @param x Coordinate
 * @param y Coordinate
 * @param artifacts Bitmask representing which artifacts are picked up already
 * @param g Movement cost already taken to get into this state
 * @param previous The State to backtrack the path
 */
State::State(const Playground &playground, int x, int y, char artifacts, int g, const State& previous) : State(playground, x, y, artifacts, g, previous.x, previous.y, previous.artifacts){}

/**
 * Internal constructor for easier handling
 * @param playground
 * @param x
 * @param y
 * @param artifacts
 * @param g
 * @param xPrev
 * @param yPrev
 * @param prevArtifacts
 */
State::State(const Playground &playground, int x, int y, char artifacts, int g, int xPrev, int yPrev, char prevArtifacts): playground(&playground), x(x), y(y), artifacts(artifacts), g(g), xPrev(xPrev), yPrev(yPrev), artifactsPrev(prevArtifacts) {}
/**
 * Get the one D coordinate of this artifact
 * @param width The width of the playground
 * @return integer index
 */
int State::getPositionInOneD(int len) const{
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
int State::getFullWeight() {
    if(!this->fetchedH) {
        h = this->playground->getEstimate(x, y, artifacts);
        this->fetchedH = true;
    }
    return g + h;
}

/**
 * Returns if this state is at the same position and artifact as the other
 * @param other state to compare to
 * @return True if same
 */
bool State::isSame(const State &other) {
    return this->x == other.x && this->y == other.y && this->artifacts == other.artifacts;
}

/**
 * Copy the values of h and g to the other state. If they are better than the other state
 * @param other reference to the state to copy to.
 */
void State::copyToIfBetter(State& other) const{
#ifdef _DEBUG
    if(!this->fetchedH) throw std::runtime_error("This shouldn't be called on this kind of node");
#endif
    if(this->g <= other.g) return;
    other.g = this->g;
    other.h = this->h;
    other.xPrev = this->xPrev;
    other.yPrev = this->yPrev;
    other.artifactsPrev = this->artifactsPrev;
}

/**
 * Expand this node. And update known states and queue accordingly.
 * @param allKnownStates all states that have been visited
 * @param queue openList
 */
void State::expand(std::vector<State> &allKnownStates, PriorityQueue &queue) {
    this->expand(allKnownStates, queue, x + 1, y, false);
    this->expand(allKnownStates, queue, x - 1, y, false);
    this->expand(allKnownStates, queue, x, y + 1, false);
    this->expand(allKnownStates, queue, x, y - 1, false);
    if(!hasB(artifacts) && hasB(this->playground->getArtifactOnField(x, y))) {
        this->expand(allKnownStates, queue, x, y, true);
    }
}


/**
 * Expand from this node to the given position.
 *
 * Checks if the new Position is out of Bounds. Will not automaticcally pick up B when no specified.
 * @param allKnownStates all states that have been visited
 * @param queue openList
 * @param x
 * @param y
 * @param pickUpB if true B will be picked up and it is assumed that no move happened (Else move is assumed)
 */
void State::expand(std::vector<State> &allKnownStates, PriorityQueue &queue, int x, int y, bool pickUpB) {
    if(!this->playground->isMoveAble(this->x, this->y, x, y, this->artifacts)) return;

    if(!pickUpB && !hasB(playground->getArtifactOnField(x, y))) {
        allKnownStates.emplace_back(*playground, x, y, this->artifacts | playground->getArtifactOnField(x, y), g + 1, *this);
    } else if(!pickUpB) {
        allKnownStates.emplace_back(*playground, x, y, this->artifacts, g + 1, *this);
    } else if(!hasB(this->artifacts) && hasB(playground->getArtifactOnField(x, y))){
        allKnownStates.emplace_back(*playground, x, y, this->artifacts | playground->getArtifactOnField(x, y), g, *this);
    } else {
        return; // No need to pickUp be if already held
    }

    bool isKnown = false;
    for(const State& state : allKnownStates) {
        throw std::runtime_error("This is unepected...");
    }
    if(queue.updateStateIfBetter(allKnownStates.back())) return;
    allKnownStates.pop_back();
}

