//
// Created by avalibit on 02/06/2021.
//

#ifndef PPEN_COMMANDS_H
#define PPEN_COMMANDS_H

#include "pch.h"

std::map<int,std::function<void(uint16_t&, uint8_t&, std::array<uint16_t,256>&, Direction&, bool&, std::map<int,Coord>&, bool&, Coord&, Coord&, Direction&)>> commands {
#define INST_START(match) {Colour::getHex(match),
    #define INST_PRG(...)  [](uint16_t& A, uint8_t& CellPtr, std::array<uint16_t,256>& cells, Direction& direction, bool& running, std::map<int,Coord>& functions, bool& def_function, Coord& curLocation, Coord& retLocation, Direction& retDirection) {__VA_ARGS__;}
    #define INST_END() },
    #include "commands.inl"
    #undef INST_START
    #undef INST_PRG
    #undef INST_END
};

void initMap() {

}

void runInst(Colour instruction, uint16_t& A, uint8_t& CellPtr, std::array<uint16_t,256>& cells, Direction& direction, bool& running, std::map<int,Coord>& functions, bool& def_function, Coord& curLocation, Coord& retLocation, Direction& retDirection) {
    if (!def_function) {
        if (instruction.a < 255) {
            // End program
            running = false;
        } else {
            commands[Colour::getHex(instruction)](A, CellPtr, cells, direction, running, functions, def_function, curLocation,
                                  retLocation, retDirection);
        }
    }
    else if (instruction == Colour(255,0,0,255)) {
        def_function = false;
    }
}
#endif //PPEN_COMMANDS_H
