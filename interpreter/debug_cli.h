//
// Created by avalibit on 12/06/2021.
//

#ifndef RGB4D_DEBUG_CLI_H
#define RGB4D_DEBUG_CLI_H

#include "pch.h"

enum debugReason {
    error,
    breakhit
};

void debug(Instruction instruction, uint16_t A, uint8_t CellPtr, std::array<uint16_t,256>& cells, Direction direction, bool running, std::map<int,Coord>& functions, bool def_function, Coord curLocation, std::stack<returnData>& funcStack, debugReason why) {
    printf("Welcome to the RGB4D debugger\nThis has been opened because: %s\nType h for help\n\n",why == error ? "Your program caused an error" : "A breakpoint has been hit");
    running = true;
    while (running) {
        printf("> ");
        char first;
        char second;
        char input[2];
        scanf("%2s", input);
        while (getchar() != '\n');
        first = input[0];
        second = input[1];
        switch (first) {
            case 'h':
                printf("----\tCommand List\t----\nh\tOpen the help menu\npa\tPrint A\nic\tIncrement the cell pointer\ndc\tDecrement the cell pointer\npc\tPrint current cell\npm\tPrint the current direction\npl\tPrint current location\npf\tPrint current function stack\npd\tPrint defined functions\nq\tQuit the debugger\n");
                break;
            case 'p':
                switch (second) {
                    case 'a':
                        printf("The current value of A is: %i\n", (int) A);
                        break;
                    case 'c':
                        printf("The current cell value is: %i\n", (int) cells[CellPtr]);
                        break;
                    case 'd':
                        printf("Current functions:\n");
                        for (auto function : functions) {
                            printf("%i: (%i,%i,%i,%i)\n", function.first, function.second.x, function.second.y,
                                   function.second.z, function.second.w);
                        }
                        break;
                    case 'm':
                        printf("Current direction is (%i,%i,%i,%i)\n", direction.x, direction.y, direction.z,
                               direction.w);
                        break;
                    case 'l':
                        printf("Current location is (%i,%i,%i,%i)\n", curLocation.x, curLocation.y, curLocation.z,
                               curLocation.w);
                        break;
                    case 'f':
                        printf("Current function stack:\n");
                        std::stack<returnData> tempStack = funcStack;
                        int place = 0;
                        while (!tempStack.empty()) {
                            auto top = tempStack.top();
                            printf("%i: Pos = (%i,%i,%i,%i) Dir = (%i,%i,%i,%i)\n", place, top.location.x,
                                   top.location.y, top.location.z, top.location.w, top.direction.x, top.direction.y,
                                   top.direction.z, top.direction.w);
                            place++;
                            tempStack.pop();
                        }
                        break;
                }
                break;
            case 'i':
                CellPtr++;
                break;
            case 'd':
                CellPtr--;
                break;
            case 'q':
                running = false;
                break;
            default:
                printf("That isn't a command!\n");
        }
    }
}

#endif //RGB4D_DEBUG_CLI_H
