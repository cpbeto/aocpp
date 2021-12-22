// Containers
#include <unordered_map>
// Others
#include <string>
// Project
#include "TextureLoader.h"
#include "../graphics.h"

std::unordered_map<uint32_t, SDL_Texture *> TextureLoader::textures;

SDL_Texture *TextureLoader::get_texture(uint32_t n) {
    SDL_Texture *texture = nullptr;

    if (textures.contains(n)) {
        texture = textures[n];
    }
    else {
        // Try loading the texture
        std::string path = "../recursos/graficos/" + std::to_string(n) + ".BMP";
        SDL_Surface * tempSurface = SDL_LoadBMP(path.c_str());
        if (tempSurface == nullptr)
        {
            printf("Failed to load image %s. SDL_Error: %s\n", path.c_str(), SDL_GetError());
        }
        else
        {
            // Transparencia
            SDL_SetColorKey(tempSurface, SDL_TRUE, SDL_MapRGB(tempSurface->format, 0x00, 0x00, 0x00));

            texture = SDL_CreateTextureFromSurface(screenRender, tempSurface);
            if (texture == nullptr)
            {
                printf("Failed to create texture from %s. SDL_Error: %s\n", path.c_str(), SDL_GetError());
            }

            SDL_FreeSurface(tempSurface);
            tempSurface = nullptr;
        }

        if (texture != nullptr) {
            textures[n] = texture;
        }
    }

    return texture;
}

void TextureLoader::dispose() {
    for (std::pair<uint32_t, SDL_Texture *> entry : textures) {
        uint32_t n = entry.first;
        SDL_Texture *texture = entry.second;
        SDL_DestroyTexture(texture);
    }
    textures.clear();
}
