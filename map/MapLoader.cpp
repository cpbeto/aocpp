// C Standard Library
#include <cerrno>
#include <cstdint>
#include <cstring>

// IO
#include <fstream>
#include <iostream>

// Others
#include <string>

#include "MapLoader.h"
#include "Map.h"

#define MAP_PATH "../recursos/mapas/"
#define MAP_EXTENSION ".map"

typedef struct {
    int16_t version;
    char desc[255];
    int32_t CRC;
    int32_t MagicWord;
    int16_t padding1;
    int16_t padding2;
    int16_t padding3;
    int16_t padding4;
} map_header_t;

Map MapLoader::load(int n) {
    Map map;

    std::string file_path = MAP_PATH + std::string("mapa") + std::to_string(n) + MAP_EXTENSION;
    std::ifstream file(file_path, std::ios::binary);

    if (!file.is_open()) {
        // @todo Raise exception
        std::cout << "Error al abrir " << file_path << std::endl;
        std::cout << "\t" << strerror(errno) << std::endl;
    }

    map_header_t map_header;
    file.read((char *)&map_header, sizeof(map_header_t));

    uint8_t flags;
    uint16_t grh_index;
    uint16_t trigger;

    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            file.read((char *)&flags, sizeof(uint8_t));
            map.getTile(x, y)->blocked = flags & 1;

            file.read((char *)&grh_index, sizeof(uint16_t));
            map.getTile(x, y)->grh[0] = grh_index;

            if (flags & 2) {
                file.read((char *)&grh_index, sizeof(uint16_t));
                map.getTile(x, y)->grh[1] = grh_index;
            }

            if (flags & 4) {
                file.read((char *)&grh_index, sizeof(uint16_t));
                map.getTile(x, y)->grh[2] = grh_index;
            }

            if (flags & 8) {
                file.read((char *)&grh_index, sizeof(uint16_t));
                map.getTile(x, y)->grh[3] = grh_index;
            }

            if (flags & 16) {
                file.read((char *)&trigger, sizeof(uint16_t));
                map.getTile(x, y)->trigger = trigger;
            }

            map.getTile(x, y)->npc = 0;

            map.getTile(x, y)->object = 0;
        }
    }

    file.close();

    map.setName("Ullathorpe");
    map.setMusic("Ullathorpe.ogg");

    return map;
}