#include "Map.h"

tile_t *Map::getTile(int x, int y) {
    return &tiles[x][y];
}

void Map::setName(std::string name) {
    this->name = name;
}

void Map::setMusic(std::string music) {
    this->music = music;
}