#ifndef AOC_DEMO_TEXTURELOADER_H
#define AOC_DEMO_TEXTURELOADER_H

#include <cstdint>
#include <unordered_map>
#include <SDL2/SDL.h>

class TextureLoader {
private:
    static std::unordered_map<uint32_t, SDL_Texture *> textures;
public:
    static SDL_Texture *get_texture(uint32_t n);
    static void dispose();
};

#endif //AOC_DEMO_TEXTURELOADER_H
