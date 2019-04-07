#include "Artefact.h"

Artefact::Artefact(std::string line) {
    char type = line[0];
    if(type < 'A' || type > 'C') throw std::invalid_argument("Artefact can only be of type A,B or C not " + std::string(1, type));
    this->type = static_cast<char> (1 << (type - 'A'));
    line = line.substr(2, std::string::npos);
    this->x = std::stoul(line, nullptr, 10);
    this->y = std::stoul(line.substr(line.find(';') + 1, std::string::npos), nullptr, 10);
}

unsigned int Artefact::getPositionInOneD(unsigned int len) {
    return tdtod(x, y, len);
}

char Artefact::getType() {
    return type;
}
