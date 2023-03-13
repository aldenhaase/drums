#include"SDL2/SDL.h"
#include"SDL2/SDL_image.h"
#include"process.h"

#ifndef DISP_H
#define DISP_H
class disp{
SDL_Window* screen;
SDL_Renderer* renderer;
SDL_RWops* buffer_stream;
SDL_Surface* image;
SDL_Texture* sdlTexture;
char buff[972800]{0};
int stride = 1600;
  public:
    disp();
    ~disp();
    int sendFrame(cam& camera, int flag);
};

#endif

