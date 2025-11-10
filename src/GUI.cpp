#include "GUI.h"

void GUI::Rander(){
    system("clear");
    if(game.stateGame() == gameState::play)
        this->RanderGame();
    else
        this->RanderMenu();
    std::cout.flush();
}

void GUI::drawLine(short n){
    std::cout << ' ';
    for(int x = 0;x < n;++x)
        std::cout << '-';
    std::cout << std::endl;
}

void GUI::RanderMenu(){
    drawLine(MWIDTH - 2);
    
    std::cout << "|Level: ";
    for(int x = 10000, lvl = game.level();x > 0;x /= 10)
        if(lvl >= x)
            std::cout << lvl / x % 10;
        else
            std::cout << ' ';
    std::cout << " |\n";

    drawLine(MWIDTH - 2);

    std::cout << "|1. continue  |\n|2. start new |\n|3. exit      |\n""";
    drawLine(MWIDTH - 2); 
}

void GUI::RanderGame(){
}
