//
// Created by avalibit on 02/06/2021.
//

#ifndef PPEN_PCH_H
#define PPEN_PCH_H

#include <cstdlib>
#include <cstdint>
#include <vector>
#include <array>
#include <string>
#include <fstream>
#include <cinttypes>
#include <random>
#include <map>
#include <filesystem>
#include <sstream>

struct Colour {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;

    bool operator==(Colour other) const {
        return other.r == r && other.g == g && other.b == b && other.a == a;
    }

    Colour(uint8_t _r, uint8_t _g, uint8_t _b, uint8_t _a) {
        r = _r;
        g = _g;
        b = _b;
        a = _a;
    }

    Colour() {
        r = 0;
        g = 0;
        b = 0;
        a = 0;
    }
};

struct Direction {
    int8_t x;
    int8_t y;
    int8_t z;
    int8_t w;

    void set(int8_t _x, int8_t _y, int8_t _z, int8_t _w) {
        setx(_x);
        sety(_y);
        setz(_z);
        setw(_w);
    }

    void setx(int8_t _x) {
        if (_x > 1 || _x < -1) {
            _x = 0;
        }
        x = _x;
    }

    void sety(int8_t _y) {
        if (_y > 1 || _y < -1) {
            _y = 0;
        }
        y = _y;
    }

    void setz(int8_t _z) {
        if (_z > 1 || _z < -1) {
            _z = 0;
        }
        z = _z;
    }

    void setw(int8_t _w) {
        if (_w > 1 || _w < -1) {
            _w = 0;
        }
        w = _w;
    }


};

struct Coord {
    uint8_t x;
    uint8_t y;
    uint8_t z;
    uint32_t w;
    
    Coord(uint8_t _x, uint8_t _y, uint8_t _z, uint32_t _w) {
        set(_x,_y,_z,_w);
    }
    
    void set(uint8_t _x, uint8_t _y, uint8_t _z, uint32_t _w) {
        setx(_x);
        sety(_y);
        setz(_z);
        setw(_w);
    }

    void setx(uint8_t _x) {
        x = _x & 0xf;
    }

    void sety(uint8_t _y) {
        y = _y & 0xf;
    }

    void setz(uint8_t _z) {
        z = _z & 0xf;
    }

    void setw(uint32_t _w) {
        w = _w;
    }

    void update(Direction direction) {
        uint8_t _x = x + direction.x;
        uint8_t _y = y + direction.y;
        uint8_t _z = z + direction.z;
        uint32_t _w = w + direction.w;
        set(_x,_y,_z,_w);
    }
};

int getIndex(Coord coord) {
    return coord.x + (coord.y * 16) + (coord.z*16*16);
}

typedef std::array<std::array<std::array<Colour,16>,16>,16> plane;

#endif //PPEN_PCH_H
