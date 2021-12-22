#include <iostream>
#include "MapRenderer.h"
#include "graphics.h"
#include "texture/TextureLoader.h"

#define TILE_SRC_SIZE 32 // Tile source (world) size
#define TILE_DST_SIZE 32 // Tile destination (screen) size

bool MapRenderer::layerEnabled[4] = {true, true, true, true};
bool MapRenderer::debug = false;

void MapRenderer::render(Map &map, int32_t x, int32_t y, grh_data_t *grh_data) {
    int semiWidth = camera_width / 2 + (camera_width % 2 > 0);
    int semiHeight = camera_height / 2 + (camera_height % 2 > 0);

    x *= TILE_SRC_SIZE;
    y *= TILE_SRC_SIZE;

    // Rendering boundaries in world pixels
    int x1 = x - semiWidth, x2 = x + semiWidth;
    int y1 = y - semiHeight, y2 = y + semiHeight;

    // Rendering boundaries in array coordinates (floor of x / 32, floor of y / 32)
    int i1 = x1 / TILE_SRC_SIZE - (x1 % TILE_SRC_SIZE < 0);
    int i2 = x2 / TILE_SRC_SIZE - (x2 % TILE_SRC_SIZE < 0);
    int j1 = y1 / TILE_SRC_SIZE - (y1 % TILE_SRC_SIZE < 0);
    int j2 = y2 / TILE_SRC_SIZE - (y2 % TILE_SRC_SIZE < 0);

    // Rendering boundaries in screen coordinates
    x1 *= screen_width / camera_width;
    x2 *= screen_width / camera_width;
    y1 *= screen_height / camera_height;
    y2 *= screen_height / camera_height;
    // Rendering offsets (rendering starts off-screen)
    int dx = (x1 % TILE_DST_SIZE) + ((x1 % TILE_DST_SIZE < 0) ? TILE_DST_SIZE : 0);
    int dy = (y1 % TILE_DST_SIZE) + ((y1 % TILE_DST_SIZE < 0) ? TILE_DST_SIZE : 0);

    for (int layer = 0; layer <= 3; layer++) {
        if (!layerEnabled[layer]) continue;
        // Iterate through array
        for (int j = j1; j <= j2; j++)
        {
            for (int i = i1; i <= i2; i++)
            {
                uint32_t grh = map.getTile(i, j)->grh[layer];

                if (grh == 0) continue;
                if (grh_data[grh].num_frames != 1) continue;

                uint32_t n = grh_data[grh].filenum;
                SDL_Texture * texture = TextureLoader::get_texture(n);

                SDL_Rect srcrect, dstrect;

                srcrect.x = grh_data[grh].sx;
                srcrect.y = grh_data[grh].sy;
                srcrect.w = grh_data[grh].pixel_width;
                srcrect.h = grh_data[grh].pixel_height;

                dstrect.x = - dx + (i - i1) * TILE_DST_SIZE;
                dstrect.y = - dy + (j - j1) * TILE_DST_SIZE;
                // Transform from bottom-left coordinates, to SDL top-left coordinates.
                // dstrect.y = screen_height - TILE_DST_SIZE - dstrect.y;
                dstrect.w = srcrect.w * (TILE_DST_SIZE / TILE_SRC_SIZE);
                dstrect.h = srcrect.h * (TILE_DST_SIZE / TILE_SRC_SIZE);

                // copiado del renderizado original en VB6
                if (layer == 1 || layer == 2 || layer == 3) {
                    dstrect.x -= (dstrect.w / 2 - TILE_DST_SIZE / 2);
                    dstrect.y -= (dstrect.h - TILE_DST_SIZE);
                }

                SDL_RenderCopy(screenRender, texture, &srcrect, &dstrect);
                /*
                if (layer == 2) {
                    SDL_RenderDrawRect(screenRender, &dstrect);
                }
                */
            }
        }
    }

    if (debug) {
        SDL_Rect rect;
        for (int x = 0; x <= screen_width; x += 32) {
            for (int y = 0; y <= screen_height; y += 32) {
                rect.x = x;
                rect.y = y;
                rect.w = 32;
                rect.h = 32;
                SDL_RenderDrawRect(screenRender, &rect);
            }
        }

        rect.x = screen_width / 2 - 5;
        rect.y = screen_height / 2 - 5;
        rect.w = 5;
        rect.h = 5;
        SDL_SetRenderDrawColor(screenRender, 0xFF, 0x00, 0x00, 0xFF);
        SDL_RenderFillRect(screenRender, &rect);
    }
}