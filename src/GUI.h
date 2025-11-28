#ifndef GUI_
#define GUI_

#include <iostream>
#include <string>
#include <cstdlib>
#include <thread>
#include <chrono>

#include "Game.h"
#include "constant.h"

extern Game game;

class GUI{
    void drawLine(short);
    void RanderGame(const GInfo &);
    void RanderMenu(const GInfo &);
    void RanderWin(int);
public:
    void Rander();
};

#endif
