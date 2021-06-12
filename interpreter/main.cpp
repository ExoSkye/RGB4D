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
    std::string filename = std::string(argv[1]);
    readFromFile(space,filename);

    int iteration = 0;
    int place = 0;

    while(running) {
        runInst(space[PC.w][PC.x][PC.y][PC.z],A,CellPtr,cells,curDirection,running,functions,def_function,PC,funcStack);
        if (verbose) {

            printf("Debug Output for iteration %i\nPosition: (%i,%i,%i,%i)\nDirection: (%i,%i,%i,%i)\nCurrent Colour: (%i,%i,%i,%i)\nCurrent A: %i\nCurrent cell value: %i\nCurrent function stack:\n",
                   iteration,PC.x,PC.y,PC.z,PC.w,curDirection.x,curDirection.y,curDirection.z,curDirection.w,
                   space[PC.w][PC.x][PC.y][PC.z].r,space[PC.w][PC.x][PC.y][PC.z].g,space[PC.w][PC.x][PC.y][PC.z].b,space[PC.w][PC.x][PC.y][PC.z].a,
                   A,cells[CellPtr]);

            std::stack<returnData> tempStack = funcStack;
            place = 0;
            while (!tempStack.empty()) {
                auto top = tempStack.top();
                printf("%i: Pos = (%i,%i,%i,%i) Dir = (%i,%i,%i,%i)\n",place,top.location.x,top.location.y,top.location.z,top.location.w,top.direction.x,top.direction.y,top.direction.z,top.direction.w);
                place++;
                tempStack.pop();
            }
            printf("Current functions:\n");
            for (auto function : functions) {
                printf("%i: (%i,%i,%i,%i)\n",function.first,function.second.x,function.second.y,function.second.z,function.second.w);
            }
        }
        if (!running) {
            break;
        }
        PC.update(curDirection);
        iteration++;
    }

    printf("Ending program since program reached transparent block at (%i,%i,%i,%i)\n",PC.x,PC.y,PC.z,PC.w);

    return 0;
}
