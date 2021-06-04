//
// Created by avalibit on 02/06/2021.
//

#ifndef PPEN_FILE_H
#define PPEN_FILE_H

#include "pch.h"

void readFromFile(std::vector<plane>& space, std::string& filename) {
    if (!std::filesystem::exists(std::filesystem::path(filename))) {
        printf("ERROR: Couldn't open file\nReason: File not found");
        exit(1);
    }
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
                char **a = nullptr;
                long int num_w = strtol(&line.c_str()[1],a,10);
                for (int i = 0; i < num_w; i++) {;
                    space.emplace_back(plane{});
                }
            }
            if (line[0] == 'I') {
                char** end = nullptr;
                uint8_t r, g, b, a, x, y, z, w;
                sscanf(&line.c_str()[1]," %3" SCNu8 " %3" SCNu8 " %3" SCNu8 " %3" SCNu8 " %3" SCNu8 " %3" SCNu8 " %3" SCNu8 " %3" SCNu8 ,&r, &g, &b,&a, &x, &y,&z, &w);
                Coord pos{x,y,z,w};
                Colour colour{r,g,b,a};
                space[pos.w][pos.x][pos.y][pos.z] = colour;
            }
        }
    }
    file.close();
}

bool saveToFile(std::vector<plane>& space, std::string& filename) {
    std::fstream file(filename,std::ios::out);
    file.exceptions(std::ifstream::badbit | std::ifstream::failbit);
    file << "W" << space.size() << "\n";

    try {
        int widx = 0;
        for (auto w : space) {
            int xidx = 0;
            for (auto x : w) {
                int yidx = 0;
                for (auto y : x) {
                    int zidx = 0;
                    for (auto z : y) {
                        if (z.a == 255) {
                            file << "I " << (int)z.r << " " << (int)z.g << " " << (int)z.b << " " << (int)z.a << " " << xidx << " " << yidx << " " << zidx << " " << widx << "\n";
                        }
                        zidx++;
                    }
                    yidx++;
                }
                xidx++;
            }
            widx++;
        }
    }
    catch(std::ifstream::failure& e) {
        printf("ERROR: Couldn't write to file\nReason: %s",e.what());
        file.close();
        return false;
    };
    file.close();
    return true;
}

#endif //PPEN_FILE_H
