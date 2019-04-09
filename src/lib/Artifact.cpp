#include "Artifact.h"

/**
 * Build an artifact from a given input line
 *
 * W is A, B or C (Only one characte)
 * x, y the coordinates as integer (Can be multiple characters)
 * @param line of format W;x;y
 */
Artifact::Artifact(std::string line) {
    char type = line[0];
    if(type < 'A' || type > 'C') throw std::invalid_argument("Artifact can only be of type A,B or C not " + std::string(1, type));
    this->type = static_cast<char> (1 << (type - 'A'));

    line = line.substr(2, std::string::npos);
    this->x = std::stoul(line, nullptr, 10);
    this->y = std::stoul(line.substr(line.find(';') + 1, std::string::npos), nullptr, 10);

    for (int &x : this->estimationCache) {
        x = std::numeric_limits<int>::max();
    }
    this->estimationCache[ARTIFACT_BYTE_MASK] = 0;
    this->estimationCache[ARTIFACT_BYTE_MASK & ~type] = 0;
}

/**
 * Get the one D coordinate of this artifact
 * @param width The width of the playground
 * @return integer index
 */
int Artifact::getPositionInOneD(int width) const{
    return tdtod(x, y, width);
}

char Artifact::getType() const{
    return type;
}

/**
 * Get the optimistic estimate from this Artifact when holding the specified artifacts till goal
 * @param artifactsHolding The artifacts holding in bit coded
 * @return Estimation of moves till termination
 */
int Artifact::getEstimate(char artifactsHolding) const{
#ifdef _DEBUG
    if(this->estimationCache[artifactsHolding] == std::numeric_limits<int>::max()) {
        throw std::runtime_error("Try to access cache that is not yet set");
    }
#endif
    return this->estimationCache[artifactsHolding];
}

/**
 * Same as Artifact::getEstimate(artifactsHolding) + shortest distance from specified point
 * @param artifactsHolding The artifacts holding in bit coded
 * @param x
 * @param y
 * @return Estimation of moves till termination
 */
int Artifact::getEstimate(char artifactsHolding, int x, int y) const {
    return this->getEstimate(artifactsHolding) + Helper::manhattanDistance(x, y, this->x, this->y);
}

/**
 * Fill in the assumptions on the given level assumes that on the other artifacts the assumptions of higher levels are filled in
 * @param otherArtifacts vector of the other artifacts
 * @param level amount of artifacts that are allready assumed to be collected when comming here 0 / 1
 */
void Artifact::fillAssumptionToCollect(std::vector<Artifact>& otherArtifacts, char level) {
    for(char x = 0; x < ARTIFACT_BYTE_MASK + 1; x++) {
        for(const Artifact& other : otherArtifacts) {
            if(other.type == this->type) continue;
            if(Helper::countBits(x | this->type | other.type) != level + 2) continue;
            this->estimationCache[x] = std::min(
                    this->estimationCache[x],
                    other.getEstimate(x | this->type | other.type) + Helper::manhattanDistance(this->x, this->y, other.x, other.y));
        }
    }
}
