#ifndef EVL_
#define EVL_

#include <termios.h>
#include <unistd.h>
#include "Game.h"

extern Game game;

class EVL{
    termios oldt;

    char getChar();
public:
    EVL();

    void process(); 

    ~EVL();
};

#endif
