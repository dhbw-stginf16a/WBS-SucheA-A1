#ifndef WBS_SUCHEA_A1_ARTIFACT_H
#define WBS_SUCHEA_A1_ARTIFACT_H

class Artifact;

#include "Helper.h"
#include "Playground.h"
#include <string>
#include <limits>
#include <vector>

class Artifact {
public:
    //Artifact(int x, int y, char type);
    Artifact(std::string line);
    int getPositionInOneD(int width) const;
    char getType() const;
    int getEstimate(char artifactsHolding) const;
    int getEstimate(char artifactsHolding, int x, int y) const;
    void fillAssumptionToCollect(std::vector<Artifact>& otherArtifacts, char level);
private:
    int x, y;
    // Should only needs states (w, v) are the other artifacts (0, 1), (1, 0), (0, 0)
    // Other states are not needed as they can be deducted from the above state
    // But it would introduce a lot of complexity to convert abc to vw thus more storage is traded for cleaner code
    int estimationCache[ARTIFACT_BYTE_MASK + 1];
    char type;
};


#endif //WBS_SUCHEA_A1_ARTIFACT_H
