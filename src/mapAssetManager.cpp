#include <iostream>
#include <vector>
#include "mapAssetManager.hpp"

mapTile::mapTile(std::string path, int xBeg, int yBeg, int xEnd, int yEnd){
    tilePath = path;
    tileCordinates[0] = xBeg;
    tileCordinates[1] = yBeg;
    tileCordinates[2] = xEnd;
    tileCordinates[3] = xEnd;
}

mapTile::~mapTile(){

}

std::string mapTile::getTilePath(){
    return tilePath;
}

int* mapTile::getTileCordinates(){
    return tileCordinates;
}

//List of the Map tiles available
std::vector<std::vector<mapTile>> createMapList(){
    std::vector<std::vector<mapTile>> mapList;
    mapTile tile1("assets/tileset/L3321L.png",0,0,5999,5999);
    mapTile tile2("assets/tileset/L3321R.png",6000,0,11999,5999);
    mapTile tile3("assets/tileset/L3321R.png",12000,0,17999,5999);
    mapTile tile4("assets/tileset/L3322L.png",0,6000,5999,11999);
    mapTile tile5("assets/tileset/L3322R.png",6000,6000,11999,11999);
    mapTile tile6("assets/tileset/L3322R.png",12000,6000,17999,11999);
    mapTile tile7("assets/tileset/L3322L.png",0,12000,5999,17999);
    mapTile tile8("assets/tileset/L3322R.png",6000,12000,11999,17999);
    mapTile tile9("assets/tileset/L3322R.png",12000,12000,17999,17999);
    mapList.push_back({tile1, tile2, tile3});
    mapList.push_back({tile4, tile5, tile6});
    mapList.push_back({tile7, tile8, tile9});
    std::cout << "Map Loading Complete!\n";
    return mapList;
}