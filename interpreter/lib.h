//
// Created by avalibit on 03/06/2021.
//

#include "pch.h"
#include "commands.h"
#include "file.h"

class interpreter {
public:
    Coord PC{0,0,0,0};
    Direction curDirection{1,0,0,0};
    std::vector<plane> space;
    std::array<uint16_t,256> cells{};
    uint16_t A = 0;
    uint8_t CellPtr = 0;
    std::map<int,Coord> functions;
    bool running = true;
    bool def_function = false;
    Coord retLocation = Coord{0,0,0,0};
    Direction retDirection = Direction{0,0,0,0};
    std::string filename;
    int iteration = 0;

    void init(std::string& _filename) {
        filename = _filename;
        readFromFile(space,filename);
    }

    explicit interpreter(std::string& _filename) {
        init(filename);
    }

    interpreter() = default;

    void step() {
        runInst(space[PC.w][PC.x][PC.y][PC.z],A,CellPtr,cells,curDirection,running,functions,def_function,PC,retLocation,retDirection);
        PC.update(curDirection);
        iteration++;
    }
};