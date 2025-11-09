#include "Game.h"

//Map::MData read/write data about Map
struct Map::MData{
    int x,y;
    bool val;

    MData();
    MData(int,int,bool);
    void write(std::ofstream&);
    void read(std::ifstream&);
};

Map::MData::MData(){
}

Map::MData::MData(int x1, int y1, bool val1){
    x = x1;
    y = y1;
    val = val1;
}

void Map::MData::write(std::ofstream &file){
    file.write(reinterpret_cast<char*>(this), sizeof(Map::MData)); 
    if(!file)
        throw std::runtime_error("Error write map into file");
}

void Map::MData::read(std::ifstream &file){
    file.read(reinterpret_cast<char*>(this), sizeof(Map::MData));
    if(!file && !file.eof())
        throw std::runtime_error("Error read map from file");
}



//Map PLACE
Map::Map(){
    //Reading File
    std::ifstream file(DATAMAP, std::ios::binary);

    if(!file)
        throw std::runtime_error("canont read data");

    Map::MData data;
    while(!file.eof()){
        data.read(file);
        ceil[data.x][data.y] = data.val; 
    }

    file.close();
}

void Map::generate(int row, int column){
}

short Map::whatIs(int x,int y){
    if(ceil.find(x) == ceil.end() || ceil[x].find(y) == ceil[x].end())
        return 0;

    return ceil[x][y] + 1; 
}

void Map::mine(int x,int y){
    ceil[x][y] = false;
}


Map::~Map(){
    //Writng file
    std::ofstream file(DATAMAP, std::ios::binary);

    for(auto& [x,c]: ceil)
        for(auto [y,val]:c){
            Map::MData data(x,y,val);
            data.write(file);
        }

    file.close();
}


//GInfo PLACE


//Game PLACE
