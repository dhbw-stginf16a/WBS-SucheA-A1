#include "Playground.h"

Playground::Playground(const std::string &inputFile, unsigned int length, unsigned int height, const std::string &artefact) : length(length), height(height) {
    std::ifstream fileStream(inputFile, std::ifstream::in);
    std::ifstream artefactStream(artefact, std::ifstream::in);

    // Length of one input line * height
    const unsigned int bytesToRead = (length*2) * height;
    char buffer[bytesToRead];

    fileStream.read(buffer, bytesToRead);
    int bytesRead = fileStream.gcount();
    if (bytesToRead - 1 >= bytesRead) throw std::runtime_error("Failed to read enough characters");
    this->field = new char[length * height];
    this->length = length;
    this->height = height;

    for(unsigned int x = 0; x < length; x++)  {
        for(unsigned int y = 0; y < height; y++) {
            char read = buffer[tdtod(x * 2, y, length * 2)]; // Skip over ; input file
            if(read < '0' || read > '3') throw std::runtime_error("Only land of type 0,1,2,3 is allowed not " + std::string(1, read));
            this->field[tdtod(x, y, length)] = read - '0';
        }
    }

    //ignore first line
    artefactStream.read(buffer, bytesToRead);
    std::string lines(buffer, artefactStream.gcount());
    lines = lines.substr(lines.find('\n') + 1, std::string::npos);
    while(lines.size() >= 5) {
        this->artefacts.emplace_back(std::string(lines));
        Artefact& a = artefacts[artefacts.size() - 1];
        this->field[a.getPositionInOneD(length)] |= shiftArtefact(a.getType());
        lines = lines.substr(lines.find('\n') + 1, std::string::npos);
    }
}

/**
 * Print field for debug purposes
 * @param delimField The delimiters to use within a line
 * @param delimLine The delimiter to use between each line
 * @param bitmask The mask to aply on every field before printing it
 * @return A string represeenting the field
 */
std::string Playground::printField(const std::string &delimField, const std::string &delimLine, char bitmask) {
    std::stringstream output ("");
    for (unsigned int y = 0; y < height; y++) {
        for(unsigned int x = 0; x < length - 1; x++) {
            output << (int) this->field[tdtod(x, y, this->length)] << ";";
        }
        output << (int) (this->field[tdtod(length - 1, y, this->length)] & bitmask)<< "\n";
    }
    return output.str();
}

Playground::~Playground() {
    delete this->field;
}
