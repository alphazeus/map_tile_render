#include <iostream>
#include <vector>
#include "../include/SDL2/SDL.h"
#include "imageLoader.hpp"
#include "keyboardHandler.hpp"
#include "mapAssetManager.hpp"
#include "pinMarker.hpp"

const int WIDTH = 800, HEIGHT = 600;

int xBegCam = 0, yBegCam = 0, xEndCam = 1000, yEndCam = 1000;

// TextureRectangle* generateNewTiles(SDL_Renderer* renderer,std::vector<std::vector<mapTile>> mapList, int* Limits){

//     static TextureRectangle tilesGenerated[6];

//     TextureRectangle rect1(renderer,mapList[0][0].getTilePath());
//     TextureRectangle rect2(renderer,mapList[0][1].getTilePath());
//     TextureRectangle rect4(renderer,mapList[1][0].getTilePath());
//     TextureRectangle rect5(renderer,mapList[1][1].getTilePath());
//     TextureRectangle rect7(renderer,mapList[2][0].getTilePath());
//     TextureRectangle rect8(renderer,mapList[2][1].getTilePath());

//     tilesGenerated[0] = rect1;
//     tilesGenerated[1] = rect2;
//     tilesGenerated[2] = rect4;
//     tilesGenerated[3] = rect5;
//     tilesGenerated[4] = rect7;
//     tilesGenerated[5] = rect8;

//     return tilesGenerated;
// }

bool checkForTileGeneration(int* Limits){
    int static prevLimit[4] = {-1,-1,-1,-1};
    bool needUpdate = false;
    for( int i = 0; i < 4; i++){
        if( prevLimit[i] != Limits[i]){
            needUpdate = true;
        }
        prevLimit[i] = Limits[i];
    }
    return needUpdate;
}

int* findRenderLimits(std::vector<std::vector<mapTile>> mapList, int* Limits, int xBegCam, int yBegCam, int xEndCam, int yEndCam){
    
    if(xBegCam >= xEndCam || yBegCam >= yEndCam){
        std::cout << "Camera Coordinate Error";
        return NULL;
    }
    
    for ( int i = 0; i < mapList.size(); i++){
        for ( int j = 0; j < mapList[i].size(); j++){
            if(mapList[i][j].getTileCordinates()[0] <= xBegCam && mapList[i][j].getTileCordinates()[2] >= xBegCam){
                Limits[0] = j;
            }
            if(mapList[i][j].getTileCordinates()[0] <= xEndCam && mapList[i][j].getTileCordinates()[2] >= xBegCam){
                Limits[2] = j;
            }
            if(mapList[i][j].getTileCordinates()[1] <= yBegCam && mapList[i][j].getTileCordinates()[3] >= yBegCam){
                Limits[1] = i;
            }
            if(mapList[i][j].getTileCordinates()[1] <= yEndCam && mapList[i][j].getTileCordinates()[3] >= yBegCam){
                Limits[3] = i;
            }
        }
    }

    return Limits;

}


int main(int argc, char* argv[]){

    SDL_Window* window = nullptr;
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        std::cout << "SDL could not be initialized: " <<
                  SDL_GetError();
    }else{
        std::cout << "SDL video system is ready to go\n";
    }

    // SDL2 Image format
    int flags = IMG_INIT_PNG;
    int initStatus = IMG_Init(flags);
    if((initStatus & flags) != flags){
        std::cout << "SDL2_Image format not available" << std::endl;
    }

    // Request a window to be created for our platform
    window = SDL_CreateWindow("C++ Map Render Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);

    SDL_Renderer* renderer = nullptr;
    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);

    int LimitArr[4] = {0,0,0,0};
    
    std::vector<std::vector<mapTile>> mapList = createMapList();
    pinClass marker(renderer);
    TextureRectangle tilesGenerated[3][3];
    // generateNewTiles(renderer, mapList, LimitArr);

    TextureRectangle rect1(renderer,mapList[0][0].getTilePath());
    TextureRectangle rect2(renderer,mapList[0][1].getTilePath());
    TextureRectangle rect4(renderer,mapList[1][0].getTilePath());
    TextureRectangle rect5(renderer,mapList[1][1].getTilePath());
    TextureRectangle rect7(renderer,mapList[2][0].getTilePath());
    TextureRectangle rect8(renderer,mapList[2][1].getTilePath());

    tilesGenerated[0][0] = rect1;
    tilesGenerated[0][1] = rect2;
    tilesGenerated[1][0] = rect4;
    tilesGenerated[1][1] = rect5;
    tilesGenerated[2][0] = rect7;
    tilesGenerated[2][1] = rect8;

    //variables for the environment (temporary)
    bool gameIsRunning = true;
    int scale = 1;
    int marker_x = 0,marker_y = 0;
    // Main application loop
    while(gameIsRunning){
        SDL_Event event;

        // Handle Input
        while(SDL_PollEvent(&event)){
            // Handle each specific event
            if(event.type == SDL_QUIT){
                gameIsRunning= false;
            }

            keyboardUpdate(event);
            if(event.type == SDL_KEYDOWN){
                if(event.key.keysym.sym == SDLK_RIGHT){
                    xBegCam += 20;
                }
                if(event.key.keysym.sym == SDLK_LEFT){
                    xBegCam = xBegCam <= 0 ? 0 : xBegCam -= 20;
                }
                if(event.key.keysym.sym == SDLK_UP){
                    yBegCam = yBegCam <= 0 ? 0 : yBegCam -= 20;
                }
                if(event.key.keysym.sym == SDLK_DOWN){
                    yBegCam += 20;
                }
                if(event.key.keysym.sym == SDLK_p){
                    scale = scale >= 12 ? 12 : scale + 1;
                }
                if(event.key.keysym.sym == SDLK_o){
                    scale = scale <= 1 ? 1 : scale - 1;
                }
                //temporary to set the cordinate marker to arbitrary position
                if(event.key.keysym.sym == SDLK_m){
                    marker_x +=100;
                    marker_y += 40;
                }
            }

            int* Limits = findRenderLimits(mapList, LimitArr, xBegCam, yBegCam, xBegCam+800*scale, yBegCam+1000*scale);
            
            std::cout <<" Needs new tile ?" << checkForTileGeneration(Limits)<<"\n";

            if(checkForTileGeneration(Limits)){
                for(int i=Limits[1];i<=Limits[3];i++){
                    for(int j=Limits[0]; j<=Limits[2];j++){
                        TextureRectangle rect(renderer,mapList[i][j].getTilePath());
                        tilesGenerated[i][j] = rect;
                    }
                }
            }
        
            //  Clear and Draw the Screen
            // Gives us a clear "canvas"
            SDL_SetRenderDrawColor(renderer,0,0,0,SDL_ALPHA_OPAQUE);
            SDL_RenderClear(renderer);

            for(int i=Limits[1];i<=Limits[3];i++){
                for(int j=Limits[0]; j<=Limits[2];j++){
                    std::cout << " Printing (" <<Limits[0]<<","<<Limits[1]<<") to ("<<Limits[2]<<","<<Limits[3]<<")\n";
                    tilesGenerated[i][j].SetDstRectParams(-xBegCam+(j*(6000/scale)), -yBegCam+(i*(6000/scale)), 6000/scale, 6000/scale);
                    tilesGenerated[i][j].Render(renderer);
                }
            }

            marker.Update(marker_x, marker_y, xBegCam, yBegCam, xBegCam+800*scale, yBegCam+600*scale);
            marker.Render(renderer);
                    
        }

        // Render everything to screen
        SDL_RenderPresent(renderer);
    }

    // Destroying the window to retrieve memory allocated
    SDL_DestroyWindow(window);
    IMG_Quit();
    // Stopping SDL Video or audio system initiated
    SDL_Quit();
    return 0;
}