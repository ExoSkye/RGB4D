#include "pch.h"
#include "commands.h"
#include "file.h"


int main(int argc, char** argv) {

    Coord PC{0,0,0,0};
    Direction curDirection{1,0,0,0};
    std::vector<plane> space;
    std::array<uint16_t,256> cells{};
    uint16_t A = 0;
    uint8_t CellPtr = 0;
    std::map<int,Coord> functions;
    bool running = true;
    bool def_function = false;
    std::stack<returnData> funcStack;
    auto retLocation = Coord{0,0,0,0};
    auto retDirection = Direction{0,0,0,0};
    if (argc != 2) {
        printf("Wrong amount of arguments");
        exit(1);
    }
    std::string filename = std::string(argv[1]);
    readFromFile(space,filename);

    int iteration = 0;

    while(running) {
        runInst(space[PC.w][PC.x][PC.y][PC.z],A,CellPtr,cells,curDirection,running,functions,def_function,PC,funcStack);
        PC.update(curDirection);
        iteration++;
    }

    printf("Ending program since program reached transparent block at (%i,%i,%i,%i)\n",PC.x,PC.y,PC.z,PC.w);

    return 0;
}
