#include"disp.h"
#include<iostream>


disp::disp(){
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_JPG);
    screen = SDL_CreateWindow("My Game Window",
                               SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED,
                               640, 480,
                               SDL_WINDOW_FULLSCREEN);       
    renderer = SDL_CreateRenderer(screen, -1,0);
/*
    buffer_stream = SDL_RWFromMem(camera.getstart(), camera.getlength());
        if(buffer_stream == NULL){
            std::cout<<"buffer_stream is broken"<<std::endl;

        }else{
            std::cout<<"good"<<std::endl;
        }

     image = IMG_Load_RW(buffer_stream, 0);
        if(image == NULL){
            std::cout<<"image is broken"<<std::endl;

        }else{
            std::cout<<"good"<<std::endl;
        }
        */
/*
     sdlTexture = SDL_CreateTextureFromSurface(renderer, image);
        if(sdlTexture == NULL){
            std::cout<<"texture is broken"<<std::endl;

        }else{
            std::cout<<"good"<<std::endl;
        }
*/

        sdlTexture = SDL_CreateTexture(renderer,
                                        SDL_PIXELFORMAT_YV12,
                                        SDL_TEXTUREACCESS_STREAMING,
                                        640,
                                        480);
   
}


int disp::sendFrame(cam& camera, int flag){

//  std::cout<<"x dim " << b.x<<std::endl;
    char * q;
    if(flag){
    q = (char*)camera.getstart(0);
    }else{
    q = (char*)camera.getstart(1);
    }
/*  
  if(b.x > 10 && b.y > 10){
          for(int y= -10; y < 10; y ++){
            for(int x= -10; x < 10; x++){
            q[(b.x + x) + ((b.y + y) * 800)] = 60;
            }
        }
  }
*/
        SDL_UpdateTexture(sdlTexture, NULL, q, camera.getstride());
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, sdlTexture, NULL, NULL);
        SDL_RenderPresent(renderer);
   //     sleep(8);
/*
 if(b.x > 10 && b.y > 10){
          for(int y= -10; y < 10; y ++){
            for(int x= -10; x < 10; x++){
            buff[(b.x + x) + ((b.y + y) * 800)] = 0;
            }
        }
  }
  */
if(flag){
 camera.q1(0);
 //camera.q1(1);
}else{
    camera.q1(1);
  //  camera.q1(2);
 //   camera.q1(3);
//
}
return 0;
}
disp::~disp(){

        SDL_DestroyTexture(sdlTexture);
        SDL_FreeSurface(image);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(screen);
 

}
