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
GInfo::GInfo(){
    ch_x = ch_y = 0;
    lb_x = lb_y = 0;
    level = 0;
    stone = ore = 0;
    ore_max = 0;
}

void GInfo::read(){
    std::ifstream file(DATAGAME, std::ios::binary);
    if(!file)
        throw std::runtime_error("Error open file with Game info"); 

    file.read(reinterpret_cast<char*>(this), sizeof(GInfo));

    if(!file)
        throw std::runtime_error("Error read Game info");

    file.close();
}

void GInfo::write(){
    std::ofstream file(DATAGAME, std::ios::binary);
    //WITHOUT EXEPTION 
    
    file.write(reinterpret_cast<char*>(this), sizeof(GInfo));

    //WITHOUT EXEPTION
    file.close();
}

//Game PLACE
Game::Game(){
    gameS = gameState::stop; 
    info.read();
}

void Game::move(short n){
    info.ch_x += dx[n];
    info.ch_y += dy[n];
    info.lb_x += dx[n];
    info.lb_y += dy[n];
}

short Game::whatIs(int x,int y){
    x += info.lb_x;
    y += info.lb_y;

    if(x == info.ch_x && y == info.ch_y)
        return 3;

    return this->map.whatIs(x,y);
}

gameState Game::stateGame() const{
    return gameS; 
}

void Game::setState(gameState n){
    gameS = n;
}

const GInfo& Game::getInfo() const{
    return info;
}

void Game::startGame(bool f){
    if(f){

    }
    gameS = gameState::play;
}

void Game::stopGame(){
    gameS = gameState::stop;
}

Game::~Game(){
    info.write();
}
