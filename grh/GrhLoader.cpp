// C Standard Library
#include <cerrno>
#include <cstdint>
#include <cstring>

// IO
#include <fstream>
#include <iostream>

// Others
#include <string>

#include "GrhLoader.h"
#include "GrhData.h"

#define GRH_PATH "../recursos/indices/Graficos3.ind"

#define TILE_PIXEL_WIDTH 32.0f
#define TILE_PIXEL_HEIGHT 32.0f

typedef struct {
    int32_t version;
    int32_t grh_count;
} grh_header_t;

grh_data_t * GrhLoader::loadGrhData() {
    std::string file_path = GRH_PATH;
    std::ifstream file(file_path, std::ios::binary);

    if (!file.is_open()) {
        // @todo Raise exception
        std::cout << "Error al abrir " << file_path << std::endl;
        std::cout << "\t" << strerror(errno) << std::endl;
    }

    grh_header_t grh_header;
    file.read((char *)&grh_header, sizeof(grh_header_t));

    int32_t grh_count = grh_header.grh_count;
    std::cout << "grh_count = " << grh_count << std::endl;

    auto *grh_data = new grh_data_t[grh_count + 1]; // VB6 indexes are 1-based

    for (int i = 0; i < grh_count; i++) {
        uint32_t grh;
        file.read((char *)&grh, sizeof(uint32_t));

        int16_t num_frames;
        file.read((char *)&num_frames, sizeof(int16_t));
        grh_data[grh].num_frames = num_frames;
        if (num_frames <= 0) throw std::runtime_error("numframes <= 0 in grh " + std::to_string(grh));

        grh_data[grh].frames = new uint32_t[num_frames + 1]; // VB6 indexes are 1-based

        if (num_frames == 1) {
            file.read((char *)&grh_data[grh].filenum, sizeof(uint32_t));
            file.read((char *)&grh_data[grh].sx, sizeof(int16_t));
            file.read((char *)&grh_data[grh].sy, sizeof(int16_t));
            file.read((char *)&grh_data[grh].pixel_width, sizeof(int16_t));
            file.read((char *)&grh_data[grh].pixel_height, sizeof(int16_t));
            grh_data[grh].tile_width = (float)grh_data[grh].pixel_width / TILE_PIXEL_WIDTH;
            grh_data[grh].tile_height = (float)grh_data[grh].pixel_height / TILE_PIXEL_HEIGHT;
            grh_data[grh].frames[1] = grh;
        }
        else if (num_frames > 1) {
            for (int frame = 1; frame <= num_frames; frame++) {
                file.read((char *)&grh_data[grh].frames[frame], sizeof(uint32_t));
            }
            file.read((char *)&grh_data[grh].speed, sizeof(float));

            uint32_t grh_1 = grh_data[grh].frames[1];
            grh_data[grh].pixel_width = grh_data[grh_1].pixel_width;
            grh_data[grh].pixel_height = grh_data[grh_1].pixel_height;
            grh_data[grh].tile_width = grh_data[grh_1].tile_width;
            grh_data[grh].tile_height = grh_data[grh_1].tile_height;
        }
    }

    file.close();

    return grh_data;
}