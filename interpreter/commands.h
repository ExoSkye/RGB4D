//
// Created by avalibit on 02/06/2021.
//

#ifndef PPEN_COMMANDS_H
#define PPEN_COMMANDS_H

#include "pch.h"

void runInst(Colour instruction, uint16_t& A, uint8_t& CellPtr, std::array<uint16_t,256>& cells, Direction& direction, bool& running, std::map<int,Coord>& functions, bool& def_function, Coord& curLocation, Coord& retLocation, Direction& retDirection) {
#ifdef _MSC_VER
#pragma warning( disable: 2397 )
#endif
    if (!def_function) {
        if (instruction.a < 255) {
            // End program
            running = false;
        }
#define INST_START(match) else if (instruction == match) {
#define INST_PRG(...)  __VA_ARGS__;
#define INST_END() }
#include "commands.inl"
#undef INST_START
#undef INST_PRG
#undef INST_END
    }
    else if (instruction == Colour(255,0,0,255)) {
        def_function = false;
    }
#ifdef _MSC_VER
#pragma warning( default:2397 )
#endif
}
#endif //PPEN_COMMANDS_H
