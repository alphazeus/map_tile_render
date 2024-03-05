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
std::vector<mapTile> createMapList(){
    std::vector<mapTile> mapList;
    mapTile tile1("assets/tileset/L3321L.png",0,0,5999,5999);
    mapTile tile2("assets/tileset/L3321R.png",6000,0,11999,5999);
    mapTile tile3("assets/tileset/L3321R.png",12000,0,17999,5999);
    mapList.push_back(tile1);
    mapList.push_back(tile2);
    mapList.push_back(tile3);
    return mapList;
}