#ifndef AOC_DEMO_GRHDATA_H
#define AOC_DEMO_GRHDATA_H

#include <cstdint>

typedef struct {
    int16_t sx;
    int16_t sy;
    uint32_t filenum;
    int16_t pixel_width;
    int16_t pixel_height;
    float tile_width;
    float tile_height;
    int16_t num_frames;
    uint32_t *frames;
    float speed;
} grh_data_t;


class GrhData {

};


#endif //AOC_DEMO_GRHDATA_H
