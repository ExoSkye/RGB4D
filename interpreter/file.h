//
// Created by avalibit on 02/06/2021.
//

#ifndef PPEN_FILE_H
#define PPEN_FILE_H

#include "pch.h"

void readFromFile(std::vector<Colour*>& space, std::string& filename) {
    std::fstream file;
    file.exceptions(std::ifstream::badbit);
    try {
        file.open(filename, std::ios::in);
    }
    catch (std::ifstream::failure& e) {
        printf("ERROR: Couldn't open file\nReason: %s",e.what());
        exit(1);
    }
    if (file.is_open()) {
        std::string line;
        while (std::getline(file,line)) {
            if (line[0] == 'W') {
                char **a = nullptr; // NOTE: DO NOT DEREFERENCE ME!
                long int num_w = strtol(&line.c_str()[1],a,10);
                for (int i = 0; i < num_w; i++) {
                    space.push_back((Colour*)calloc(16*16*16,sizeof(Colour)));
                }
            }
            if (line[0] == 'I') {
                char** end = nullptr;
                uint8_t r, g, b, a, x, y, z, w;
                sscanf(&line.c_str()[1]," %3" SCNu8 " %3" SCNu8 " %3" SCNu8 " %3" SCNu8 " %3" SCNu8 " %3" SCNu8 " %3" SCNu8 " %3" SCNu8 ,&r, &g, &b,&a, &x, &y,&z, &w);
                Coord pos{x,y,z,w};
                Colour colour{r,g,b,a};
                space[pos.w][getIndex(pos)] = colour;
            }
        }
    }
    file.close();
}

#endif //PPEN_FILE_H
