// IO
#include <iostream>

// SDL 2
#include <SDL2/SDL.h>

// aocpp - demo
#include "graphics.h"
#include "grh/GrhData.h"
#include "grh/GrhLoader.h"
#include "map/Map.h"
#include "map/MapLoader.h"
#include "MapRenderer.h"
#include "texture/TextureLoader.h"

int main() {
    std::cout << "Loading Graficos3.ind" << std::endl;
    grh_data_t *grh_data = GrhLoader::loadGrhData();

    Map map = MapLoader::load(1);

    // Init SDL2
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Failed to initialize SDL. SDL_Error: %s\n", SDL_GetError());
        return -1;
    }

    window = SDL_CreateWindow("SDL-Sandbox", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen_width, screen_height, SDL_WINDOW_RESIZABLE);
    if(window == nullptr)
    {
        printf("Failed to create window. SDL_Error: %s\n", SDL_GetError());
        return -1;
    }

    screenRender = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (screenRender == nullptr)
    {
        printf("Failed to create screen renderer. SDL_Error: %s\n", SDL_GetError());
        return -1;
    }
    SDL_SetRenderDrawColor(screenRender, 0x00, 0x00, 0x00, 0xFF);

    SDL_Event event;
    bool run = true;
    while (run)
    {
        while (SDL_PollEvent(&event) != 0)
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    run = false;
                    break;
                case SDL_WINDOWEVENT:
                    if (event.window.event == SDL_WINDOWEVENT_RESIZED)
                    {
                        screen_resize(event.window.data1, event.window.data2);
                    }
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_1:
                            MapRenderer::layerEnabled[0] = !MapRenderer::layerEnabled[0];
                            break;
                        case SDLK_2:
                            MapRenderer::layerEnabled[1] = !MapRenderer::layerEnabled[1];
                            break;
                        case SDLK_3:
                            MapRenderer::layerEnabled[2] = !MapRenderer::layerEnabled[2];
                            break;
                        case SDLK_4:
                            MapRenderer::layerEnabled[3] = !MapRenderer::layerEnabled[3];
                            break;
                        case SDLK_d:
                            MapRenderer::debug = !MapRenderer::debug;
                            break;
                    }
                    break;
            }
        }

        SDL_SetRenderDrawColor(screenRender, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderClear(screenRender);
        MapRenderer::render(map, 50, 50, grh_data);
        SDL_RenderPresent(screenRender);
    }

    TextureLoader::dispose();

    SDL_DestroyRenderer(screenRender);
    screenRender = nullptr;

    SDL_DestroyWindow(window);
    window = nullptr;

    SDL_Quit();

    return 0;
}
