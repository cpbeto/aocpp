#ifndef AOC_DEMO_MAPRENDERER_H
#define AOC_DEMO_MAPRENDERER_H

#include "grh/GrhData.h"
#include "map/Map.h"

class MapRenderer {
public:
    static bool layerEnabled[4];
    static bool debug;
    static void render(Map &map, int32_t x, int32_t y, grh_data_t *grh_data);
};

#endif //AOC_DEMO_MAPRENDERER_H
