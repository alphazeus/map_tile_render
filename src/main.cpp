#include <iostream>

#include "../include/SDL2/SDL.h"
#include "imageLoader.hpp"
#include "keyboardHandler.hpp"

const int WIDTH = 800, HEIGHT = 600;


int main(int argc, char* argv[]){
    // Create a window data type
    // This pointer will point to the 
    // window that is allocated from SDL_CreateWindow
    SDL_Window* window = nullptr;

    // Initialize the video subsystem.
    // iF it returns less than 1, then an
    // error code will be received.
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        std::cout << "SDL could not be initialized: " <<
                  SDL_GetError();
    }else{
        std::cout << "SDL video system is ready to go\n";
    }
    // Request a window to be created for our platform
    // The parameters are for the title, x and y position,
    // and the width and height of the window.
    window = SDL_CreateWindow("C++ Map Render Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);

    SDL_Renderer* renderer = nullptr;
    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);

    TextureRectangle rect(renderer);

    
    // Infinite loop for our application
    bool gameIsRunning = true;
    int x_val = 0, y_val = 0, scale = 1;
    // Main application loop
    while(gameIsRunning){
        SDL_Event event;

        // (1) Handle Input
        // Start our event loop
        while(SDL_PollEvent(&event)){
            // Handle each specific event
            if(event.type == SDL_QUIT){
                gameIsRunning= false;
            }

            keyboardUpdate(event);
            if(event.type == SDL_KEYDOWN){
                if(event.key.keysym.sym == SDLK_RIGHT){
                    x_val+=20;
                }
                if(event.key.keysym.sym == SDLK_LEFT){
                    x_val-=20;
                }
                if(event.key.keysym.sym == SDLK_UP){
                    y_val-=20;
                }
                if(event.key.keysym.sym == SDLK_DOWN){
                    y_val+=20;
                }
                if(event.key.keysym.sym == SDLK_p){
                    scale = scale >= 8 ? 8 : scale + 1;
                }
                if(event.key.keysym.sym == SDLK_o){
                    scale = scale <= 1 ? 1 : scale - 1;
                }
            }

            rect.SetRectangleParams(x_val, y_val, 4000/scale, 3000/scale);


            // (2) Handle Updates
        
            // (3) Clear and Draw the Screen
            // Gives us a clear "canvas"
            SDL_SetRenderDrawColor(renderer,0,0,0,SDL_ALPHA_OPAQUE);
            SDL_RenderClear(renderer);

            rect.Render(renderer);

        }

        // Finally show what we've drawn
        SDL_RenderPresent(renderer);
    }

    // Destroying the window to retrieve memory allocated
    SDL_DestroyWindow(window);

    // Stopping SDL Video or audio system initiated
    SDL_Quit();
    return 0;
}