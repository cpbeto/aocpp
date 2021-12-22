#ifndef AOC_DEMO_GRAPHICS_H
#define AOC_DEMO_GRAPHICS_H

#include <SDL2/SDL.h>

#define SCREEN_DEFAULT_WIDTH 854
#define SCREEN_DEFAULT_HEIGHT 480

extern int screen_width;
extern int screen_height;
extern int camera_width;
extern int camera_height;

extern SDL_Window *window;
extern SDL_Renderer *screenRender;

void screen_resize(int width, int height);

#endif //AOC_DEMO_GRAPHICS_H
