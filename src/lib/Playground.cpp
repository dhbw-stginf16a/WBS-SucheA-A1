#include "Playground.h"

/**
 * Initialise an new Playground object by parsing the input files
 *
 * The format is expected to be a semicolon seperated file with each line representing one line of the field
 * @param inputFile The file name to read the playground of lands in.
 * @param width The width of the playground (amount of fields per line)
 * @param height The height of the playground (amount of lines in file)
 * @param component The file to parse for the components per line format of W;x;y with W being A,B or C and x, y being the coordinates from top left of field
 */
Playground::Playground(const std::string &inputFile, int width, int height, const std::string &component) : width(width), height(height) {
    std::ifstream fileStream(inputFile, std::ifstream::in);
    std::ifstream componentStream(component, std::ifstream::in);

    // Length of one input line * height
    // Two characters per field number and ;
    const int bytesToRead = (width*2) * height;
    char buffer[std::max(bytesToRead, 1000)];

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
    componentStream.read(buffer, std::max(bytesToRead, 1000));
    std::string lines(buffer, componentStream.gcount());
    //ignore first line as it is explaining the file format
    lines = lines.substr(lines.find('\n') + 1, std::string::npos);
    while(lines.size() >= 5) {
        this->components.emplace_back(std::string(lines));

        Component& a = components[components.size() - 1];
        this->field[a.getPositionInOneD(width)] |= shiftComponent(a.getType());

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

/**
 * Prints the field with one cell beeing X(Y) with X being the Land and Y beeing the Component if any
 * @param delimField
 * @param delimLine
 * @param color True if colored output should be given
 * @return
 */
std::string Playground::printFieldFancy(const std::string &delimField, const std::string &delimLine, bool color) {
    std::stringstream output ("");
    for (int y = 0; y < height; y++) {
        for(int x = 0; x < width - 1; x++) {
            output << (color?Helper::getColorForLand(this->getLandOnField(x, y)):"") << static_cast<char>('0' + this->getLandOnField(x, y)) << "(" << Helper::printComponent(this->getComponentOnField(x, y)) << ");";
        }
        output << (color?Helper::getColorForLand(this->getLandOnField(width - 1, y)):"") << static_cast<char>('0' + this->getLandOnField(width - 1, y)) << "("<< Helper::printComponent(this->getComponentOnField(width - 1, y)) <<")" << "\n";
    }
    return output.str();
}

Playground::~Playground() {
    delete this->field;
}

/**
 * Fills all caches in the components with how long the estimate till termination is
 */
void Playground::fillPathCache() {
    for(char level = static_cast<char>(Helper::countBits(COMPONENT_BYTE_MASK) - 2); level >= 0; level--) {
        for(Component& component : this->components) {
            component.fillAssumptionToCollect(this->components, level);
        }
    }
}

/**
 * Get the estimation from a specific field, based on the amount of components allready holding
 * @param x Coordinate
 * @param y Coordinate
 * @param components Bitmask with smallest bit being A and 3 Bit representing C
 * @return The estimate till termination in moves needed
 */
int Playground::getEstimate(int x, int y, char components) const {
#ifdef _DEBUG
    if(!this->inField(x, y)) throw std::runtime_error("Not in field");
#endif
    int min = std::numeric_limits<int>::max();
    for(const Component &component : this->components) {
        min = std::min(min, component.getEstimate(components, x, y));
    }
    return min;
}

/**
 * Calculate a path from the given start position collecting all components
 * @param x
 * @param y
 * @return TBD
 */
void Playground::calculatePath(int x, int y) {
    if(!this->inField(x, y)) throw std::runtime_error("You started outside the field");
    if(this->isWater(x, y)) throw std::runtime_error("You started in water");
    std::vector<State> closedList;
    PriorityQueue openList; // Closed list fehlt... TODO

    char componentOnStart = this->getComponentOnField(x, y);
    //Don't auto pick up B on the start field
    State startState;
    if(hasB(componentOnStart)) {
        startState = State(*this, x, y, 0, 0);
    } else {
        startState = State(*this, x, y, componentOnStart, 0);
    }
    openList.addState(startState);

    while(!openList.isEmpty()) {
        State currentState = openList.pop();
        if(currentState.isFinalState()) {
            while(!currentState.isSame(startState)) {
                std::cout << currentState.toString() << "\n";
                bool foundNext = false;
                for(State &state : closedList) {
                    if(state.isParentOf(currentState)) {
                        currentState = state;
                        foundNext = true;
                        break;
                    }
                }
                if(!foundNext) throw std::runtime_error("Couldn't traverse path backwards :(");
            }
            std::cout << "Done printing reverse path" << std::endl;
            return;
        }

        currentState.expand(closedList, openList);
        closedList.push_back(currentState);
    }
    throw std::runtime_error("No Path Found");
}

/**
 * Get the component mask on this specific field
 * @param x x-Cord
 * @param y y-Cord
 * @return The bitmask of the component
 */
char Playground::getComponentOnField(int x, int y) const {
#ifdef _DEBUG
    if(!this->inField(x, y)) throw std::runtime_error("Not in field");
#endif
    return getComponent(this->field[tdtod(x, y, width)]);
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
 * Determine if it is possible to move from from to to with component holding
 * @param xFrom
 * @param yFrom
 * @param xTo
 * @param yTo
 * @param component
 * @return true if move is possible
 */
bool Playground::isMoveAble(int xFrom, int yFrom, int xTo, int yTo, char component) const {
    if(!this->inField(xTo, yTo)) return false;
    if(!this->inField(xFrom, yFrom)) return false;
    if(this->isWater(xTo, yTo)) return false;
    if(hasB(component)) {
        const char l1 = this->getLandOnField(xTo, yTo);
        const char l2 = this->getLandOnField(xFrom, yFrom);
        return 0 == !(l1 & l2);
    }
    return true;
}
