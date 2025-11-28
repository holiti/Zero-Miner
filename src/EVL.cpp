#include "EVL.h"

EVL::EVL(){
    tcgetattr(STDIN_FILENO, &oldt);
    
    termios newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    newt.c_cc[VTIME] = 0;
    newt.c_cc[VMIN] = 1;

    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
}

char EVL::getChar(){
    char ch = 0;
    read(STDIN_FILENO, &ch, 1);
    tcflush(STDIN_FILENO, TCIFLUSH);
    return ch;
}

void EVL::process(){
    char ch = getChar();

    if(game.stateGame() == gameState::play){
        if(ch == 'q')
            game.setState(gameState::stop);
        else if(ch == 's')
            game.move(0);
        else if(ch == 'd')
            game.move(1);
        else if(ch == 'w')
            game.move(2);
        else if(ch == 'a')
            game.move(3);

    }else{
        if(ch <= '3' && '1' <= ch)
            game.startGame(ch - '1');
        else if(ch == '4')
            exit(0);
    }
}

EVL::~EVL(){
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}

