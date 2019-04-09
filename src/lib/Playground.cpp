#include "Playground.h"

/**
 * Initialise an new Playground object by parsing the input files
 *
 * The format is expected to be a semicolon seperated file with each line representing one line of the field
 * @param inputFile The file name to read the playground of lands in.
 * @param width The width of the playground (amount of fields per line)
 * @param height The height of the playground (amount of lines in file)
 * @param artifact The file to parse for the artifacts per line format of W;x;y with W being A,B or C and x, y being the coordinates from top left of field
 */
Playground::Playground(const std::string &inputFile, int width, int height, const std::string &artifact) : width(width), height(height) {
    std::ifstream fileStream(inputFile, std::ifstream::in);
    std::ifstream artifactStream(artifact, std::ifstream::in);

    // Length of one input line * height
    // Two characters per field number and ;
    const int bytesToRead = (width*2) * height;
    char buffer[bytesToRead];

    fileStream.read(buffer, bytesToRead);
    int bytesRead = fileStream.gcount();
    if (bytesToRead - 1 >= bytesRead) throw std::runtime_error("Failed to read enough characters");

    this->field = new char[width * height];
    for(int x = 0; x < width; x++)  {
        for(int y = 0; y < height; y++) {
            char read = buffer[tdtod(x * 2, y, width * 2)]; // Skip over ; in input file
            if(read < '0' || read > '3') throw std::runtime_error("Only land of type 0,1,2,3 is allowed not " + std::string(1, read));
            this->field[tdtod(x, y, width)] = read - '0';
        }
    }

    //Assume that amount of characters to read is less compared to the whole field
    artifactStream.read(buffer, bytesToRead);
    std::string lines(buffer, artifactStream.gcount());
    //ignore first line as it is explaining the file format
    lines = lines.substr(lines.find('\n') + 1, std::string::npos);
    while(lines.size() >= 5) {
        this->artifacts.emplace_back(std::string(lines));

        Artifact& a = artifacts[artifacts.size() - 1];
        this->field[a.getPositionInOneD(width)] |= shiftArtifact(a.getType());

        lines = lines.substr(lines.find('\n') + 1, std::string::npos);
    }

    fillPathCache();
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
    for (int y = 0; y < height; y++) {
        for(int x = 0; x < width - 1; x++) {
            output << (int) this->field[tdtod(x, y, this->width)] << ";";
        }
        output << (int) (this->field[tdtod(width - 1, y, this->width)] & bitmask)<< "\n";
    }
    return output.str();
}

Playground::~Playground() {
    delete this->field;
}

/**
 * Fills all caches in the artifacts with how long the estimate till termination is
 */
void Playground::fillPathCache() {
    for(char level = static_cast<char>(Helper::countBits(ARTIFACT_BYTE_MASK) - 2); level >= 0; level--) {
        for(Artifact& artifact : this->artifacts) {
            artifact.fillAssumptionToCollect(this->artifacts, level);
        }
    }
}

/**
 * Get the estimation from a specific field, based on the amount of artifacts allready holding
 * @param x Coordinate
 * @param y Coordinate
 * @param artifacts Bitmask with smallest bit being A and 3 Bit representing C
 * @return The estimate till termination in moves needed
 */
int Playground::getEstimate(int x, int y, char artifacts) const {
#ifdef _DEBUG
    if(!this->inField(x, y)) throw std::runtime_error("Not in field");
#endif
    int min = std::numeric_limits<int>::max();
    for(const Artifact &artifact : this->artifacts) {
        min = std::min(min, artifact.getEstimate(artifacts, x, y));
    }
    return min;
}

/**
 * Calculate a path from the given start position collecting all artifacts
 * @param x
 * @param y
 * @return TBD
 */
void Playground::calculatePath(int x, int y) {
#ifdef _DEBUG
    if(!this->inField(x, y)) throw std::runtime_error("You started outside the field");
    if(this->isWater(x, y)) throw std::runtime_error("You started in water");
#endif
    std::vector<State> allKnownStates;
    PriorityQueue queue; // Closed list fehlt... TODO

    char artifactOnStart = this->getArtifactOnField(x, y);
    //Don't auto pick up B on the start field
    if(hasB(artifactOnStart)) {
        allKnownStates.emplace_back(*this, x, y, 0, 0);
    } else {
        allKnownStates.emplace_back(*this, x, y, artifactOnStart, 0);
    }
    queue.addState(allKnownStates.back());

    while(!queue.isEmpty()) {
        State currentState = queue.pop();
        if(currentState.isFinalState()) {
            throw std::runtime_error("Found a path to lazy to print it :)");
        }

        currentState.expand(allKnownStates, queue);
    }
    throw std::runtime_error("No Path Found");
}

/**
 * Get the artifact mask on this specific field
 * @param x x-Cord
 * @param y y-Cord
 * @return The bitmask of the artifact
 */
char Playground::getArtifactOnField(int x, int y) const {
#ifdef _DEBUG
    if(!this->inField(x, y)) throw std::runtime_error("Not in field");
#endif
    return getArtifact(this->field[tdtod(x, y, width)]);
}

/**
 * Get the land ( or water) on this specific field
 * @param x x-Cord
 * @param y y-Cord
 * @return The number of the land
 */
char Playground::getLandOnField(int x, int y) const {
#ifdef _DEBUG
    if(!this->inField(x, y)) throw std::runtime_error("Not in field");
#endif
    return getLand(this->field[tdtod(x, y, width)]);
}

/**
 * Determine if the requested cords are in field
 * @param x x-Cord
 * @param y y-Cord
 * @return True if in field
 */
bool Playground::inField(int x, int y) const{
    return x >= 0 && y >=0 && x < width && y < height;
}

/**
 * Determine if the requested cords are water
 * @param x x-Cord
 * @param y y-Cord
 * @return True if water
 */
bool Playground::isWater(int x, int y) const {
#ifdef _DEBUG
    if(!this->inField(x, y)) throw std::runtime_error("Not in field");
#endif
    return this->getLandOnField(x, y) == 0;
}

/**
 * Determine if it is possible to move from from to to with artifact holding
 * @param xFrom
 * @param yFrom
 * @param xTo
 * @param yTo
 * @param artifact
 * @return true if move is possible
 */
bool Playground::isMoveAble(int xFrom, int yFrom, int xTo, int yTo, char artifact) const {
    if(!this->inField(xTo, yTo)) return false;
    if(!this->inField(xFrom, yFrom)) return false;
    if(!this->isWater(xTo, yTo)) return false;
    if(hasB(artifact)) {
        return 0 != this->getLandOnField(xTo, yTo) & this->getLandOnField(xFrom, yFrom);
    }
    return true;
}
