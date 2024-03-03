#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "imageLoader.hpp"



TextureRectangle::TextureRectangle(SDL_Renderer*& renderer){
    src_rct.x = 0;
    src_rct.y = 0;
    src_rct.w = 800;
    src_rct.h = 600;
    dst_rct.x = 0;
    dst_rct.y = 0;
    dst_rct.w = 800;
    dst_rct.h = 600;
    // Setup and initialize the SDL2_Image library
    // with our supported formats
    int flags = IMG_INIT_PNG;
    int initStatus = IMG_Init(flags);
    if((initStatus & flags) != flags){
        std::cout << "SDL2_Image format not available" << std::endl;
    }
    SDL_Surface* image = IMG_Load("assets/tileset/L3321L.png");
    if(!image){
        std::cout << "Image not loaded..." << std::endl;
    }
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
    m_texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);
}

TextureRectangle::~TextureRectangle(){
    SDL_DestroyTexture(m_texture);
    IMG_Quit();
}

void TextureRectangle::SetRectangleParams(int x, int y, int w, int h){
    src_rct.x = x;
    src_rct.y = y;
    src_rct.w = w;
    src_rct.h = h;
}

void TextureRectangle::Update(){

}

void TextureRectangle::Render(SDL_Renderer*& renderer){
    SDL_RenderCopy(renderer,m_texture,&src_rct,&dst_rct);
}