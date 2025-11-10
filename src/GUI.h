#ifndef GUI_
#define GUI_

#include <iostream>
#include <cstdlib>

#include "Game.h"
#include "constant.h"

extern Game game;

class GUI{
    void drawLine(short);
    void RanderGame();
    void RanderMenu();
public:
    void Rander();
};

#endif
