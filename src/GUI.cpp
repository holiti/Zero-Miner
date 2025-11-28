#include "GUI.h"

void GUI::Rander(){
    system("clear");

    const GInfo& cur = game.getInfo();
    if(game.stateGame() == gameState::play)
        this->RanderGame(cur);
    else
        this->RanderMenu(cur);
    std::cout.flush();
}

void GUI::drawLine(short n){
    std::cout << ' ';
    for(int x = 0;x < n;++x)
        std::cout << '-';
    std::cout << std::endl;
}

void GUI::RanderMenu(const GInfo &info){
    drawLine(MWIDTH);
    
    std::cout << "|Level:    ";
    for(int x = 10000, lvl = info.level;x > 0;x /= 10)
        if(lvl >= x)
            std::cout << lvl / x % 10;
        else
            std::cout << ' ';
    std::cout << " |\n";

    drawLine(MWIDTH);

    std::cout << "|1. continue     |\n|2. restart level|\n|3. full restart |\n|4. exit         |\n""";
    drawLine(MWIDTH - 2); 
}

void GUI::RanderGame(const GInfo &info){
    using namespace std;

    string stn = to_string(info.stone); 
    string ore = to_string(info.ore) + "/" + to_string(info.ore_max);

    for(int x = stn.size();x < GWIDTH + 2 - ore.size();++x)
        stn.push_back(' ');

    cout << stn + ore << endl;

    drawLine(GWIDTH);

    for(int x = 0;x < GHEIGHT;++x){
        cout << '|';
        for(int y = 0;y < GWIDTH;++y){
            switch(game.whatIs(x,y)){
                case 0:
                    cout << "\e[36m" << CHARSTONE << "\e[0m";
                break;
                case 1:
                    cout << CHARFREE;
                break;
                case 2:
                    cout << "\e[33m" <<  CHARORE << "\e[0m";
                break;
                case 3:
                    cout << CHAR;
                break;
            }
        }
        cout << "|\n";
    }

    drawLine(GWIDTH);
    cout << "q - quite\n";
}
