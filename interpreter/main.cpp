#include "pch.h"
#include "commands.h"
#include "file.h"


int main(int argc, char** argv) {
    bool verbose = false;
    if (argc > 2) {
        if (std::string(argv[2]) == "--debug") {
            verbose = true;
        }
    }

    Coord PC{0,0,0,0};
    Direction curDirection{1,0,0,0};
    std::vector<Colour*> space;
    std::array<uint16_t,256> cells{};
    uint16_t A = 0;
    uint8_t CellPtr = 0;
    std::map<int,Coord> functions;
    bool running = true;
    bool def_function = false;
    Coord retLocation = Coord{0,0,0,0};
    Direction retDirection = Direction{0,0,0,0};
    std::string filename = std::string(argv[1]);
    readFromFile(space,filename);

    int iteration = 0;

    while(running) {
        runInst(space[PC.w][getIndex(PC)],A,CellPtr,cells,curDirection,running,functions,def_function,PC,retLocation,retDirection);
        if (verbose) {
            printf("Debug Output for iteration %i\nPosition: (%i,%i,%i,%i)\nCurrent Colour: (%i,%i,%i,%i)\n",iteration,PC.x,PC.y,PC.z,PC.w,space[PC.w][getIndex(PC)].r,space[PC.w][getIndex(PC)].g,space[PC.w][getIndex(PC)].b,space[PC.w][getIndex(PC)].a);
        }
        if (!running) {
            break;
        }
        PC.update(curDirection);
        iteration++;
    }

    printf("Ending program since program reached transparent block at (%i,%i,%i,%i)\n",PC.x,PC.y,PC.z,PC.w);

    // Clean up

    for (auto & i : space) {
        free(i);
    }

    return 0;
}
