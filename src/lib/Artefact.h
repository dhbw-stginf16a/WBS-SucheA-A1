#ifndef WBS_SUCHEA_A1_ARTEFACT_H
#define WBS_SUCHEA_A1_ARTEFACT_H

class Artefact;
#include "Playground.h"
#include <string>

class Artefact {
public:
    //Artefact(unsigned int x, unsigned int y, char type);
    Artefact(std::string line);
    unsigned int getPositionInOneD(unsigned int len);
    char getType();
private:
    unsigned int x, y;
    unsigned int assumptionToCollect[8];
    char type;
};


#endif //WBS_SUCHEA_A1_ARTEFACT_H
