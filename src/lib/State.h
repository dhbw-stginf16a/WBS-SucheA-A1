#ifndef WBS_SUCHEA_A1_STATE_H
#define WBS_SUCHEA_A1_STATE_H

class State;
#include "Playground.h"
#include "PriorityQueue.h"

class State {
public:
    State();
    State(const Playground& playground, int x, int y, char artifacts, int g);
    State(const Playground& playground, int x, int y, char artifacts, int g, const State& previous);
    bool isFinalState() const;
    int getPositionInOneD(int len) const;
    int getFullWeight() const;
    bool isSame(const State & other) const;
    bool isParentOf(const State & other) const;
    void copyToIfBetter(State& other) const;
    void expand(const std::vector<State>& closedList, PriorityQueue& openList);
    void expand(const std::vector<State>& closedList, PriorityQueue& openList, int x, int y, bool pickUpB);
    std::string toString();
private:
    State(const Playground& playground, int x, int y, char artifacts, int g, int xPrev, int yPrev, char prevArtifacts);
    const Playground * playground;
    int x, y;
    int xPrev, yPrev;
    // g - shortest known path to this state
    // h - estimation till end from this node
    int g, h = -1;
    char artifacts, artifactsPrev;
};


#endif //WBS_SUCHEA_A1_STATE_H
