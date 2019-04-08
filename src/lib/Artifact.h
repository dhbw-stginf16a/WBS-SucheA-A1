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
    //Artifact(unsigned int x, unsigned int y, char type);
    Artifact(std::string line);
    unsigned int getPositionInOneD(unsigned int width) const;
    char getType() const;
    unsigned int getEstimate(char artifactsHolding) const;
    unsigned int getEstimate(char artifactsHolding, unsigned int x, unsigned int y) const;
    void fillAssumptionToCollect(std::vector<Artifact>& otherArtifacts, char level);
private:
    unsigned int x, y;
    // Should only needs states (w, v) are the other artifacts (0, 1), (1, 0), (0, 0)
    // Other states are not needed as they can be deducted from the above state
    // But it would introduce a lot of complexity to convert abc to vw thus more storage is traded for cleaner code
    unsigned int estimationCache[ARTIFACT_BYTE_MASK + 1];
    char type;
};


#endif //WBS_SUCHEA_A1_ARTIFACT_H
