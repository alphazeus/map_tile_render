#include <iostream>
#include <vector>

class mapTile{
    public:
        mapTile(std::string, int, int, int, int);
        ~mapTile();
        std::string getTilePath();      
        int* getTileCordinates();
    private:
        std::string tilePath;
        int tileCordinates[4];
        int x_cord;
        int y_cord;
};

std::vector<mapTile> createMapList();