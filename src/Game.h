#ifndef GAME
#define GAME

#include <unordered_map> 
#include <fstream>
#include <random>
#include <queue>
#include <array>
#include "constant.h"

//Map PLACE
class Map{
    std::unordered_map<int, std::unordered_map<int,bool>> ceil;

    //MData data about one ceil of map
    struct MData;
    struct Cordinate;

    static std::random_device rd;
    static std::mt19937 gen;

    static int dx[],dy[];

    void randCord(int&, int&, std::uniform_int_distribution<>&) const;
    bool isFree(int, int);          //1 if ceil in map 'ceil'
public:
    Map();                          //read this object

    void generate(int,int);         //generate new map
    short whatIs(int,int);          //answer
                            
    void mine(int,int);             //mine ceil

    ~Map();                         //write this object
};




//GIngo PLACE info about game 
struct GInfo{
    int 
        ch_x,ch_y,                  //pers_cord
        lb_x, lb_y,                 //bound of visual cord
        level,                      //number of level
        stone, ore,                 //amount of stone and ore
        ore_max;                    //max of ore

    GInfo();

    void read();
    void write();
};


//Game PLACE
enum gameState {play, stop};

class Game{
    GInfo info;
    Map map;
    gameState gameS;

    static const inline int 
        dx[] = {1,0,-1,0}, 
        dy[] = {0,1,0,-1};

public:
    Game();

    void move(short);                   //move pers short = [0,3]
    short whatIs(int,int);              //answer
                                        //
    gameState stateGame() const;        //return cur state
    void setState(gameState);           //set game state

    const GInfo& getInfo() const;       //return info about game

    void startGame(bool);               //false - without restart; 
                                        //true - with restart
    void stopGame();

    ~Game();
};

#endif
