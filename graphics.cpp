#include "graphics.h"

int screen_width = SCREEN_DEFAULT_WIDTH;
int screen_height = SCREEN_DEFAULT_HEIGHT;
int camera_width = screen_width;
int camera_height = screen_height;

SDL_Window *window;
SDL_Renderer *screenRender;

void screen_resize(int width, int height)
{
    screen_width = width;
    screen_height = height;
    camera_width = screen_width;
    camera_height = screen_height;
}