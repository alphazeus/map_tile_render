#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "pinMarker.hpp"

pinClass::pinClass(SDL_Renderer*& renderer){

    dst_rct.x = - 37;
    dst_rct.y = - 102;
    dst_rct.w = 75;
    dst_rct.h = 102;

    SDL_Surface* image = IMG_Load("assets/marker.png");
    if(!image){
        std::cout << "Image not loaded..." << std::endl;
    }
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
    m_texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);
}

pinClass::~pinClass(){
    SDL_DestroyTexture(m_texture);
}

void pinClass::Update(int x_mark, int y_mark, int xBegCam, int yBegCam, int xEndCam, int yEndCam){
    dst_rct.x = - xBegCam + x_mark - 37;
    dst_rct.y = - yBegCam + y_mark - 102;
    dst_rct.w = 75;
    dst_rct.h = 102;
}

void pinClass::Render(SDL_Renderer*& renderer){
    SDL_RenderCopy(renderer,m_texture,NULL,&dst_rct);
}