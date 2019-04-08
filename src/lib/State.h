#ifndef WBS_SUCHEA_A1_STATE_H
#define WBS_SUCHEA_A1_STATE_H

class State;
#include "Playground.h"

class State {
public:
    State(const Playground& playground, unsigned int x, unsigned int y, char artifacts, unsigned int g);
    bool isFinalState() const;
    unsigned int getPositionInOneD(unsigned int len) const;
    unsigned int getFullWeight();
    bool isSame(const State & other);
    void copyTo(State * other) const;
private:
    const Playground& playground;
    unsigned int x, y;
    bool fetchedH = false;
    // g - shortest known path to this state
    // h - estimation till end from this node
    unsigned int g, h = 0;
    char artifacts;
};


#endif //WBS_SUCHEA_A1_STATE_H
