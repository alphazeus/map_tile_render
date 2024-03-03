#include <iostream>
#include <SDL2/SDL.h>
#include "keyboardHandler.hpp"

void keyboardUpdate(SDL_Event &event){
    if(event.type == SDL_KEYDOWN){
        if(event.key.keysym.sym == SDLK_p){
            std::cout << "P is pressed!";
        }
        if(event.key.keysym.sym == SDLK_o){
            std::cout << "O is pressed!";
        }
    }
}