#ifndef WBS_SUCHEA_A1_ARTEFACT_H
#define WBS_SUCHEA_A1_ARTEFACT_H

class Artefact;

#include "Helper.h"
#include "Playground.h"
#include <string>
#include <limits>
#include <vector>

class Artefact {
public:
    //Artefact(unsigned int x, unsigned int y, char type);
    Artefact(std::string line);
    unsigned int getPositionInOneD(unsigned int len) const;
    char getType() const;
    unsigned int getEstimate(char artefactsHolding) const;
    unsigned int getEstimate(char artefactsHolding, unsigned int x, unsigned int y) const;
    void fillAssumptionToCollect(std::vector<Artefact>& otherArtifacts, char level);
private:
    unsigned int x, y;
    // Should only needs states (w, v) are the other artefacts (0, 1), (1, 0), (0, 0)
    // Other states are not needed as they can be deducted from the above state
    // But it would introduce a lot of complexity to convert abc to vw thus more storage is traded for cleaner code
    unsigned int estimationCache[ARTEFACT_BYTE_MASK + 1];
    char type;
};


#endif //WBS_SUCHEA_A1_ARTEFACT_H
