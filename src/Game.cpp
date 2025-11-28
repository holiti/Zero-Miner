#include "Game.h"

//Map::MData read/write data about Map
struct Map::MData{
    int x,y;
    bool val;
MData(); MData(int,int,bool);
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

//Cordinate
struct Map::Cordinate{
    int x,y;
    Cordinate(){
        y = x = 0;
    }
    Cordinate(int a,int b){
        x = a;
        y = b;
    }

    bool isCorrect(int size){
        //return 1 if cordinate in range
        return 0 <= x && 0 <= y && x < size && y < size;
    }
};

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

std::random_device Map::rd;
std::mt19937 Map::gen(rd());
int Map::dx[] = {-1,-1,-1,0,1,1,1,0};
int Map::dy[] = {-1,0,1,1,1,0,-1,-1};

void Map::randCord(int &x, int &y, std::uniform_int_distribution<>& dst) const{
    x = dst(gen);
    y = dst(gen);
}

bool Map::isFree(int x,int y){
    return ceil.find(x) != ceil.end() && ceil[x].find(y) != ceil[x].end();
}

void Map::generate(int size,int ore){
    ceil.clear();
    int level = ore / ORE_DIFF;
    std::uniform_int_distribution<> dst(0,size - 1);

    std::queue<Cordinate> q;

    int miners = level * MINERS;
    if(miners < 5)
        miners = 5;

    for(int x = 0;x < miners;++x){
        Cordinate cur;
        randCord(cur.x, cur.y, dst);
        ceil[cur.x][cur.y] = 0;
        q.push(cur);
    }

    int maxFree = level * FREE;
    std::uniform_int_distribution<> d8(0,7);
    while(!q.empty() && maxFree){
        auto [x,y] = q.front();
        q.pop();

        int i = d8(gen); 
        Cordinate cur(x + dx[i],y + dy[i]);
        int cnt = 0;
        while(cnt < 8 && isFree(cur.x,cur.y)){
            i = (i + 1) % 8;
            ++cnt;
            cur.x = x + dx[i];
            cur.y = y + dy[i];
        }
        
        if(cnt < 8){
            q.push(cur);
            ceil[cur.x][cur.y] = 0;
        }
        
        --maxFree;
    }
    

    int round = 1;
    while(round < ROUND){
        for(auto& [x,e]: ceil){
            for(auto [y,val]: e){
                for(int i = 0;i < 8;++i){
                    Cordinate cur(x + dx[i],y + dy[i]);
                        int cnt = 0;
                        for(int i1 = 0;i1 < 8;++i1)
                            cnt += isFree(cur.x + dx[i1], cur.y + dy[i1]);
                        if(cnt >= LIVE)
                            ceil[cur.x][cur.y] = 0;
                        else if(cnt < DIE){
                            ceil[cur.x].erase(cur.y);
                            if(ceil[cur.x].empty())
                                ceil.erase(cur.x);
                        }
                }
            }
        }
        ++round;
    }
    


    for(int x = 0;x < ore;++x){
        Cordinate cur;
        do{
            randCord(cur.x, cur.y, dst);
        }while(ceil[cur.x][cur.y] != 0);
        ceil[cur.x][cur.y] = 1;
    }
}

short Map::whatIs(int x,int y){
    if(!isFree(x,y))
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
    level_complete = 0;
}

void Game::genMap(){
    info.stone = info.ore = 0;

    int dst = info.level * DIST_DIFF;
    info.ch_x = GHEIGHT / 2;
    info.ch_y = GWIDTH / 2;
    info.lb_x = info.lb_y = 0;

    info.ore_max = info.level * ORE_DIFF;

    map.generate(dst, info.ore_max);
}

void Game::move(short n){
    info.ch_x += dx[n];
    info.ch_y += dy[n];
    info.lb_x += dx[n];
    info.lb_y += dy[n];

    short ans = map.whatIs(info.ch_x,info.ch_y);
    map.mine(info.ch_x, info.ch_y);
    if(ans == 0){
        info.stone += 1;
    }else if(ans == 2){
        info.ore += 1;
        if(info.ore == info.ore_max){
            gameS = gameState::win;
            info.level += 1;
            level_complete = 1;
        }
    }
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

void Game::startGame(short f){
    if(f || level_complete){
        if(f == 2)
            info.level = 1;
        genMap();

        level_complete = 0;
    }
    gameS = gameState::play;
}

void Game::stopGame(){
    gameS = gameState::stop;
}

Game::~Game(){
    info.write();
}
