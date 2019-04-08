#include "State.h"

State::State(const Playground &playground, unsigned int x, unsigned int y, char artefacts, unsigned int g) : playground(playground), x(x), y(y), artefacts(artefacts), g(g) {}

unsigned int State::getPositionInOneD(unsigned int len) const{
    return tdtod(x, y, len);
}

bool State::isFinalState() const {
    return (this->artefacts & 7) == 7;
}

unsigned int State::getFullEstimate() {
    if(!this->fetchedH) {
        h = this->playground.getEstimate(x, y, artefacts);
        this->fetchedH = true;
    }
    return g + h;
}
