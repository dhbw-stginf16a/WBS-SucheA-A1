#include "State.h"

/**
 * Default constructor for first spot in vector
 */
State::State(){
    this->playground = nullptr;
    this->x = -1;
    this->y = -1;
    this->components = static_cast<char>(0xff);
    this->xPrev = -1;
    this->yPrev = -1;
    this->componentsPrev = static_cast<char>(0xff);
    this->g = -1;
}

/**
 * Construct a valid state object
 * @param playground Reference to the playground this state was generated on
 * @param x Coordinate
 * @param y Coordinate
 * @param components Bitmask representing which components are picked up already
 * @param g Movement cost already taken to get into this state
 */
State::State(const Playground &playground, int x, int y, char components, int g): State(playground, x, y, components, g, -1, -1, static_cast<char>(0xff)) {}

/**
 * Construct a valid state object
 * @param playground Reference to the playground this state was generated on
 * @param x Coordinate
 * @param y Coordinate
 * @param components Bitmask representing which components are picked up already
 * @param g Movement cost already taken to get into this state
 * @param previous The State to backtrack the path
 */
State::State(const Playground &playground, int x, int y, char components, int g, const State& previous) : State(playground, x, y, components, g, previous.x, previous.y, previous.components){}

/**
 * Internal constructor for easier handling
 * @param playground
 * @param x
 * @param y
 * @param components
 * @param g
 * @param xPrev
 * @param yPrev
 * @param prevComponents
 */
State::State(const Playground &playground, int x, int y, char components, int g, int xPrev, int yPrev, char prevComponents): playground(&playground), x(x), y(y), components(components), g(g), xPrev(xPrev), yPrev(yPrev), componentsPrev(prevComponents) {
    h = this->playground->getEstimate(x, y, components);
}
/**
 * Get the one D coordinate of this component
 * @param width The width of the playground
 * @return integer index
 */
int State::getPositionInOneD(int len) const{
    return tdtod(x, y, len);
}

/**
 * Determine if this is a terminating state (All components are picked up
 * @return true if it is a terminating state
 */
bool State::isFinalState() const {
    return (this->components & COMPONENT_BYTE_MASK) == COMPONENT_BYTE_MASK;
}

/**
 * Get the full weight of this State including the path lenght already taken and the estimation till a final state is reached
 * @return The estimated full path length till reaching the goal
 */
int State::getFullWeight() const{
    return g + h;
}

/**
 * Returns if this state is at the same position and component as the other
 * @param other state to compare to
 * @return True if same
 */
bool State::isSame(const State &other) const{
    return this->x == other.x && this->y == other.y && this->components == other.components;
}

/**
 * Returns if this state is the parent of the given state
 * @param other state to compare to
 * @return True if parent
 */
bool State::isParentOf(const State &other) const {
    return this->x == other.xPrev && this->y == other.yPrev && this->components == other.componentsPrev;
}

/**
 * Copy the values of h and g to the other state. If they are better than the other state
 * @param other reference to the state to copy to.
 */
void State::copyToIfBetter(State& other) const{
    if(this->g <= other.g) return;
    other.g = this->g;
    other.h = this->h;
    other.xPrev = this->xPrev;
    other.yPrev = this->yPrev;
    other.componentsPrev = this->componentsPrev;
}

/**
 * Expand this node. And update known states and queue accordingly.
 * @param closedList all states that have been visited
 * @param openList openList
 */
void State::expand(const std::vector<State> &closedList, PriorityQueue &openList) {
    this->expand(closedList, openList, x + 1, y, false);
    this->expand(closedList, openList, x - 1, y, false);
    this->expand(closedList, openList, x, y + 1, false);
    this->expand(closedList, openList, x, y - 1, false);
    if(!hasB(components) && hasB(this->playground->getComponentOnField(x, y))) {
        this->expand(closedList, openList, x, y, true);
    }
}


/**
 * Expand from this node to the given position.
 *
 * Checks if the new Position is out of Bounds. Will not automaticcally pick up B when no specified.
 * @param closedList all states that have been visited
 * @param openList openList
 * @param x
 * @param y
 * @param pickUpB if true B will be picked up and it is assumed that no move happened (Else move is assumed)
 */
void State::expand(const std::vector<State> &closedList, PriorityQueue &openList, int x, int y, bool pickUpB) {
    if(!this->playground->isMoveAble(this->x, this->y, x, y, this->components)) return;
    State newState;
    if(!pickUpB && !hasB(playground->getComponentOnField(x, y))) {
        newState = State(*playground, x, y, this->components | playground->getComponentOnField(x, y), g + 1, *this);
    } else if(!pickUpB) {
        newState = State(*playground, x, y, this->components, g + 1, *this);
    } else if(!hasB(this->components) && hasB(playground->getComponentOnField(x, y))){
        newState = State(*playground, x, y, this->components | playground->getComponentOnField(x, y), g, *this);
    } else {
        return; // No need to pickUp be if already held
    }

    //Every state in the closed list must be better that the new state.
    for(const State& state : closedList) {
        if(state.isSame(newState)) return;
    }

    if(!openList.addStateIfBetter(newState)) return;
}

/**
 * Generates a string to represent this State
 * @return string
 */
std::string State::toString() {
    std::stringstream output ("");
    output << "(" << xPrev << ", " << yPrev << ") " << Helper::printComponentString(componentsPrev, 3) << "<-" << "(" << x<< ", " << y<< ")" << Helper::printComponentString(
            components, 3) << " g=" << g << " h=" << h;
    return output.str();
}

