#include "Artefact.h"

Artefact::Artefact(std::string line) {
    char type = line[0];
    if(type < 'A' || type > 'C') throw std::invalid_argument("Artefact can only be of type A,B or C not " + std::string(1, type));
    this->type = static_cast<char> (1 << (type - 'A'));
    line = line.substr(2, std::string::npos);
    this->x = std::stoul(line, nullptr, 10);
    this->y = std::stoul(line.substr(line.find(';') + 1, std::string::npos), nullptr, 10);

    for (unsigned int &x : this->assumptionToCollect) {
        x = std::numeric_limits<unsigned int>::max();
    }
    this->assumptionToCollect[ARTEFACT_BYTE_MASK] = 0;
    this->assumptionToCollect[ARTEFACT_BYTE_MASK & ~type] = 0;
}

unsigned int Artefact::getPositionInOneD(unsigned int len) const{
    return tdtod(x, y, len);
}

char Artefact::getType() const{
    return type;
}

unsigned int Artefact::getAssumptionToCollect(char artefactsHolding) const{
    // Stuff that would convert from abc to vw notation
    /*char bytemask = type;
    char toShift = static_cast<char>(0xff);
    while(bytemask) {
        toShift ^= bytemask;
        bytemask = static_cast<char>((bytemask >> 1) & 0x7f); // keep bytemask at one bit with
    }
    artefactsHolding = (artefactsHolding & toShift) >> 1 | (artefactsHolding | (~toShift & ~type));
    return this->assumptionToCollect[artefactsHolding];*/
    /*artefactsHolding &= ~type;
    char vw;
    if(type == 1) {
        vw = (artefactsHolding << 1);
    } else {
        vw = artefactsHolding;
        if(vw & 6) {
            vw |= 2;
        }
    }
    vw &= 3;
    return this->assumptionToCollect[vw];*/
#ifdef _DEBUG
    if(this->assumptionToCollect[artefactsHolding] == std::numeric_limits<unsigned int>::max()) {
        throw std::runtime_error("foo");
    }
#endif
    return this->assumptionToCollect[artefactsHolding];
}

unsigned int Artefact::getAssumptionToCollect(char artefactsHolding, unsigned int x, unsigned int y) const {
    return this->assumptionToCollect[artefactsHolding] + Helper::manhattanDistance(x, y, this->x, this->y);
}

/**
 * Fill in the assumptions on the given level assumes that on the other artifacts the assumptions of higher levels are filled in
 * @param otherArtifacts vector of the other artifacts
 * @param level amount of artefacts that are allready assumed to be collected when comming here 0 / 1
 */
void Artefact::fillAssumptionToCollect(std::vector<Artefact>& otherArtifacts, char level) {
    for(char x = 0; x < ARTEFACT_BYTE_MASK + 1; x++) {
        for(const Artefact& other : otherArtifacts) {
            if(other.type == this->type) continue;
            if(Helper::countBits(x | this->type | other.type) != level + 2) continue;
            this->assumptionToCollect[x] = std::min(
                    this->assumptionToCollect[x],
                    other.getAssumptionToCollect(x | this->type | other.type) + Helper::manhattanDistance(this->x, this->y, other.x, other.y));
        }
    }
}
