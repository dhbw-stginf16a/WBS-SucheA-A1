#include "Component.h"

/**
 * Build an component from a given input line
 *
 * W is A, B or C (Only one characte)
 * x, y the coordinates as integer (Can be multiple characters)
 * @param line of format W;x;y
 */
Component::Component(std::string line) {
    char type = line[0];
    if(type < 'A' || type > 'C') throw std::invalid_argument("Component can only be of type A,B or C not " + std::string(1, type));
    this->type = static_cast<char> (1 << (type - 'A'));

    line = line.substr(2, std::string::npos);
    this->x = std::stoul(line, nullptr, 10);
    this->y = std::stoul(line.substr(line.find(';') + 1, std::string::npos), nullptr, 10);

    for (int &x : this->estimationCache) {
        x = std::numeric_limits<int>::max();
    }
    this->estimationCache[COMPONENT_BYTE_MASK] = 0;
    this->estimationCache[COMPONENT_BYTE_MASK & ~type] = 0;
}

/**
 * Get the one D coordinate of this component
 * @param width The width of the playground
 * @return integer index
 */
int Component::getPositionInOneD(int width) const{
    return tdtod(x, y, width);
}

char Component::getType() const{
    return type;
}

/**
 * Get the optimistic estimate from this Component when holding the specified components till goal
 * @param componentsHolding The components holding in bit coded
 * @return Estimation of moves till termination
 */
int Component::getEstimate(char componentsHolding) const{
#ifdef _DEBUG
    if(this->estimationCache[componentsHolding] == std::numeric_limits<int>::max()) {
        throw std::runtime_error("Try to access cache that is not yet set");
    }
#endif
    return this->estimationCache[componentsHolding];
}

/**
 * Same as Component::getEstimate(componentsHolding) + shortest distance from specified point
 * @param componentsHolding The components holding in bit coded
 * @param x
 * @param y
 * @return Estimation of moves till termination
 */
int Component::getEstimate(char componentsHolding, int x, int y) const {
    return this->getEstimate(componentsHolding) + Helper::manhattanDistance(x, y, this->x, this->y);
}

/**
 * Fill in the assumptions on the given level assumes that on the other components the assumptions of higher levels are filled in
 * @param otherComponents vector of the other components
 * @param level amount of components that are allready assumed to be collected when comming here 0 / 1
 */
void Component::fillAssumptionToCollect(std::vector<Component>& otherComponents, char level) {
    for(char x = 0; x < COMPONENT_BYTE_MASK + 1; x++) {
        for(const Component& other : otherComponents) {
            if(other.type == this->type) continue;
            if(Helper::countBits(x | this->type | other.type) != level + 2) continue;
            this->estimationCache[x] = std::min(
                    this->estimationCache[x],
                    other.getEstimate(x | this->type | other.type) + Helper::manhattanDistance(this->x, this->y, other.x, other.y));
        }
    }
}
