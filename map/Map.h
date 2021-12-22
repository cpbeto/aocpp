//
// Created by tomas on 18/9/20.
//

#ifndef AOC_DEMO_MAP_H
#define AOC_DEMO_MAP_H

#include <cstdint>
#include <string>

#define MAP_WIDTH 100
#define MAP_HEIGHT 100

typedef struct {
    bool blocked;
    uint16_t grh[4];
    uint16_t trigger;
    uint16_t npc;
    uint16_t object;
} tile_t;

class Map {
private:
    std::string name;
    std::string music;
    tile_t tiles[MAP_WIDTH][MAP_HEIGHT];

public:
    tile_t *getTile(int x, int y);
    void setName(std::string name);
    void setMusic(std::string music);
};

#endif //AOC_DEMO_MAP_H
