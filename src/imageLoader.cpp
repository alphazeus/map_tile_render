#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "imageLoader.hpp"
#include <fstream>

TextureRectangle::TextureRectangle(){

}

TextureRectangle::TextureRectangle(SDL_Renderer*& renderer, std::string imgpath){
    src_rct.x = 0;
    src_rct.y = 0;
    src_rct.w = 800;
    src_rct.h = 600;
    dst_rct.x = 0;
    dst_rct.y = 0;
    dst_rct.w = 800;
    dst_rct.h = 600;
    
    SDL_Surface* image = IMG_Load(imgpath.c_str());
    if(!image){
        std::cout << "Image not loaded..." << std::endl;
    }
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
    m_texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);

    std::string fileString;
    std::ifstream PGWFile(imgpath.substr(0, imgpath.size()-3)+"pgw");
    for(int i=0;i<6; i++){
        getline (PGWFile, fileString);
        // Output the text from the file
        std::cout << fileString<<"\n";
        if(i == 6){
            x_cord = stoi(fileString);
        }
        if(i == 7){
            y_cord = stoi(fileString);
        }
    }
    std::cout <<"File read complete!\n";
    PGWFile.close();
}

TextureRectangle::~TextureRectangle(){
    SDL_DestroyTexture(m_texture);
}

void TextureRectangle::SetSrcRectParams(int x, int y, int w, int h){
    src_rct.x = x;
    src_rct.y = y;
    src_rct.w = w;
    src_rct.h = h;
}

void TextureRectangle::SetDstRectParams(int x, int y, int w, int h){
    dst_rct.x = x;
    dst_rct.y = y;
    dst_rct.w = w;
    dst_rct.h = h;
}

void TextureRectangle::Update(){

}

void TextureRectangle::Render(SDL_Renderer*& renderer){
    SDL_RenderCopy(renderer,m_texture,NULL,&dst_rct);
}